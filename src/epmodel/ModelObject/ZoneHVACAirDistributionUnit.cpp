/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACAirDistributionUnit.hpp"
#include "ZoneHVACAirDistributionUnit_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACAirDistributionUnit::ZoneHVACAirDistributionUnit(const Model& model) : ModelObject(ZoneHVACAirDistributionUnit::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACAirDistributionUnit_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  ZoneHVACAirDistributionUnit::ZoneHVACAirDistributionUnit(std::shared_ptr<detail::ZoneHVACAirDistributionUnit_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACAirDistributionUnit::iddObjectType() {
    return IddObjectType::ZoneHVAC_AirDistributionUnit;
  }

  boost::optional<ModelObject> ZoneHVACAirDistributionUnit::airTerminal() const {
    return getModelObjectTarget<ModelObject>(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName);
  }

  namespace detail {

    bool ZoneHVACAirDistributionUnit_Impl::setAirTerminal(const openstudio::epmodel::ModelObject& airTerminal) {
      auto adu = getObject<openstudio::epmodel::ZoneHVACAirDistributionUnit>();
      if (airTerminal.model() != adu.model()) {
        return false;
      }

      auto terminalObject = airTerminal;
      if (!terminalObject.name() || terminalObject.name()->empty()) {
        terminalObject.createName();
        if (!terminalObject.name() || terminalObject.name()->empty()) {
          return false;
        }
      }

      if (!adu.setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, airTerminal.iddObject().name())) {
        return false;
      }
      return adu.setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, terminalObject.handle());
    }

  }  // namespace detail

  boost::optional<Node> ZoneHVACAirDistributionUnit::outletNode() const {
    return getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->resolvedNodeTarget(
      openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName);
  }

  namespace detail {

    bool ZoneHVACAirDistributionUnit_Impl::setOutletNode(const openstudio::epmodel::Node& node) {
      auto adu = getObject<openstudio::epmodel::ZoneHVACAirDistributionUnit>();
      if (node.model() != adu.model()) {
        return false;
      }
      return adu.setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, node.handle());
    }

    std::vector<IdfObject> ZoneHVACAirDistributionUnit_Impl::remove() {
      // Both relationships are required by the IDD, so public pointer resets
      // reject an intermediate blank value. Clear them without validity
      // checking before removal to keep the target objects' reverse-pointer
      // bookkeeping free of references to the deleted ADU.
      setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, Handle(), false);
      setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, Handle(), false);
      return ModelObject_Impl::remove();
    }

    void ZoneHVACAirDistributionUnit_Impl::doCanonicalize(LoadContext& context) {
      auto adu = getObject<openstudio::epmodel::ZoneHVACAirDistributionUnit>();

      if (auto terminalName = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName)) {
        if (!terminalName->empty()) {
          if (auto terminalType = adu.getString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType)) {
            if (!terminalType->empty()) {
              try {
                auto iddType = openstudio::IddObjectType(terminalType->c_str());
                if (auto target = model().getObjectByTypeAndName(iddType, *terminalName)) {
                  if (!adu.setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, target->handle())) {
                    OS_ASSERT(false);
                  }
                }
              } catch (const std::exception&) {
                detail::addLoadWarning(context, "ZoneHVAC:AirDistributionUnit '" + adu.nameString() + "' has invalid AirTerminalObjectType '"
                                                  + *terminalType + "'.");
              }
            }
          }
        }
      }

      (void)resolvedNodeTarget(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
