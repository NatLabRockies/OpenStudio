/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingFourPipeBeam.hpp"
#include "StraightComponent/CoilCoolingFourPipeBeam_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/Branch_Impl.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Cooling_FourPipeBeam_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilCoolingFourPipeBeam::CoilCoolingFourPipeBeam(const Model& model) : StraightComponent(CoilCoolingFourPipeBeam::iddObjectType(), model) {}

  CoilCoolingFourPipeBeam::CoilCoolingFourPipeBeam(std::shared_ptr<detail::CoilCoolingFourPipeBeam_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingFourPipeBeam::iddObjectType() {
    return IddObjectType::OS_Coil_Cooling_FourPipeBeam;
  }

  namespace detail {

    unsigned CoilCoolingFourPipeBeam_Impl::inletPort() const {
      return openstudio::OS_Coil_Cooling_FourPipeBeamFields::ChilledWaterInletNodeName;
    }

    unsigned CoilCoolingFourPipeBeam_Impl::outletPort() const {
      return openstudio::OS_Coil_Cooling_FourPipeBeamFields::ChilledWaterOutletNodeName;
    }

    boost::optional<openstudio::epmodel::PlantLoop> CoilCoolingFourPipeBeam_Impl::plantLoop() const {
      const auto inlet = inletModelObject() ? inletModelObject()->optionalCast<openstudio::epmodel::Node>() : boost::none;
      const auto outlet = outletModelObject() ? outletModelObject()->optionalCast<openstudio::epmodel::Node>() : boost::none;
      if (!inlet && !outlet) {
        return boost::none;
      }

      for (const auto& plant : model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>()) {
        auto plantImpl = plant.getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
        if ((inlet && plantImpl->branchForNode(*inlet)) || (outlet && plantImpl->branchForNode(*outlet))) {
          return plant;
        }
      }

      return boost::none;
    }

    bool CoilCoolingFourPipeBeam_Impl::addToNode(Node& node) {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      for (const auto& plant : model().getConcreteModelObjects<openstudio::epmodel::PlantLoop>()) {
        auto plantImpl = plant.getImpl<openstudio::epmodel::detail::PlantLoop_Impl>();
        for (const auto& branch : plantImpl->demandEquipmentBranches()) {
          const auto branchNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(branch.nameString() + " Node");
          if (branchNode != node) {
            continue;
          }

          auto branchImpl = branch.getImpl<openstudio::epmodel::detail::Branch_Impl>();
          branchImpl->clearComponents();
          const auto inletNodeName = node.nameString();
          const auto outletNodeName = node.nameString() + " - " + thisObject.nameString() + " Outlet";
          if (!branchImpl->appendComponent(thisObject, inletNodeName, outletNodeName)) {
            return false;
          }

          auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(inletNodeName);
          auto outletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(outletNodeName);
          return setPointer(inletPort(), inletNode.handle(), false) && setPointer(outletPort(), outletNode.handle(), false);
        }
      }

      if (node.plantLoop()) {
        return StraightComponent_Impl::addToNode(node);
      }

      return false;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
