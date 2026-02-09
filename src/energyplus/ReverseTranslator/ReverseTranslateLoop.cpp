/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/HVACComponent.hpp"
#include "../../model/HVACComponent_Impl.hpp"
#include "../../model/StraightComponent.hpp"
#include "../../model/StraightComponent_Impl.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem_Impl.hpp"

#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

#include <utilities/idd/Branch_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  // This is annoying. In case of the main branch before the splitter, the node where you connect in the supply inlet node, and works the opposite
  // ways as if you were going to connect to the supply Outlet Node
  // We could pass a std::function_ref<Node<const Loop& loop>> functor that would grab loop.supplySplitterInletNode() instead of passing a
  // connectionNode that is supposed to be non-moving
  void ReverseTranslator::populateBranch(const WorkspaceObject& branchObject, model::Node& connectionNode, bool reverseOrder, bool isSupplyBranch) {
    // bool reverseOrderInfer = connectionNode.loop()->supplyInletNode() == connectionNode;
    auto egs = branchObject.extensibleGroups();
    if (reverseOrder) {
      std::reverse(egs.begin(), egs.end());
    }

    for (size_t i = 0; i < egs.size(); i++) {
      const auto eg = egs[i].cast<WorkspaceExtensibleGroup>();

      std::string componentName = eg.getString(BranchExtensibleFields::ComponentName).value_or("");
      std::string componentType = eg.getString(BranchExtensibleFields::ComponentObjectType).value_or("");
      if (componentName.empty() || componentType.empty()) {
        LOG(Error, branchObject.briefDescription() << ": Missing Component Name or Component Object Type in branch extensible group at index " << i
                                                   << ", skipping.");
        continue;
      }

      // TODO: try catch
      IddObjectType iddType(componentType);
      boost::optional<WorkspaceObject> wo_ = m_workspace.getObjectByTypeAndName(iddType, componentName);
      if (!wo_) {
        LOG(Error, branchObject.briefDescription() << ": Missing object listed at index " << i);
      }
      const WorkspaceObject wo = std::move(*wo_);

      boost::optional<std::string> componentInletNodeName = eg.getString(BranchExtensibleFields::ComponentInletNodeName);
      boost::optional<std::string> componentOutletNodeName = eg.getString(BranchExtensibleFields::ComponentOutletNodeName);

      OptionalModelObject targetModelObject = translateAndMapWorkspaceObject(wo);
      if (!targetModelObject) {
        LOG(Error, "Error importing object: " << wo.briefDescription());
        continue;
      }

      OptionalHVACComponent hvacComponent = targetModelObject->optionalCast<HVACComponent>();
      if (!hvacComponent) {
        LOG(Error, "Object listed at index " << i << " is not an HVACComponent, it is a " << targetModelObject->iddObjectType().valueName()
                                             << ", skipping.");
        continue;
      }

      // TODO: handle all cases that require special handling (eg: tertiary node connections, etc). The order will matter!
      if (hvacComponent->addToNode(connectionNode)) {
        if (boost::optional<StraightComponent> straightComponent = hvacComponent->optionalCast<StraightComponent>()) {
          Node outletNode = straightComponent->outletModelObject()->cast<Node>();
          Node inletNode = straightComponent->inletModelObject()->cast<Node>();
          if (componentInletNodeName) {
            inletNode.setName(componentInletNodeName.get());
          }
          if (componentOutletNodeName) {
            outletNode.setName(componentOutletNodeName.get());
          }
        } else if (boost::optional<AirLoopHVACOutdoorAirSystem> oaSystem = hvacComponent->optionalCast<AirLoopHVACOutdoorAirSystem>()) {
          Node outletNode = oaSystem->mixedAirModelObject()->cast<Node>();
          Node inletNode = oaSystem->returnAirModelObject()->cast<Node>();
          if (componentInletNodeName) {
            inletNode.setName(componentInletNodeName.get());
          }
          if (componentOutletNodeName) {
            outletNode.setName(componentOutletNodeName.get());
          }
        }
      }
    }
  }

}  // namespace energyplus

}  // namespace openstudio
