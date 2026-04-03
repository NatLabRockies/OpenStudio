/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationComponentSetpoint.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationComponentSetpoint_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/PlantEquipmentOperation_ComponentSetpoint_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  PlantEquipmentOperationComponentSetpoint::PlantEquipmentOperationComponentSetpoint(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationComponentSetpoint::iddObjectType(), model) {
    auto operationTypeValues = PlantEquipmentOperationComponentSetpoint::component1OperationTypeValues();
    std::string defaultOperationType = "Heating";
    if (!operationTypeValues.empty()) {
      defaultOperationType = operationTypeValues.front();
    }

    if (numExtensibleGroups() == 0u) {
      auto group = pushExtensibleGroup();
      OS_ASSERT(!group.empty());
    }

    OS_ASSERT(setComponent1FlowRate(0.0));
    OS_ASSERT(setComponent1OperationType(defaultOperationType));
  }

  PlantEquipmentOperationComponentSetpoint::PlantEquipmentOperationComponentSetpoint(
    std::shared_ptr<detail::PlantEquipmentOperationComponentSetpoint_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationComponentSetpoint::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_ComponentSetpoint;
  }

  boost::optional<double> PlantEquipmentOperationComponentSetpoint::component1FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->component1FlowRate();
  }

  bool PlantEquipmentOperationComponentSetpoint::isComponent1FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->isComponent1FlowRateAutosized();
  }

  bool PlantEquipmentOperationComponentSetpoint::setComponent1FlowRate(double component1FlowRate) {
    return getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->setComponent1FlowRate(component1FlowRate);
  }

  void PlantEquipmentOperationComponentSetpoint::autosizeComponent1FlowRate() {
    getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->autosizeComponent1FlowRate();
  }

  boost::optional<double> PlantEquipmentOperationComponentSetpoint::autosizedComponent1FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->autosizedComponent1FlowRate();
  }

  std::string PlantEquipmentOperationComponentSetpoint::component1OperationType() const {
    return getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->component1OperationType();
  }

  bool PlantEquipmentOperationComponentSetpoint::setComponent1OperationType(const std::string& component1OperationType) {
    return getImpl<detail::PlantEquipmentOperationComponentSetpoint_Impl>()->setComponent1OperationType(component1OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationComponentSetpoint::component1OperationTypeValues() {
    static const std::vector<std::string> values{"Heating", "Cooling", "Dual"};
    return values;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      using ExtensibleFields = openstudio::PlantEquipmentOperation_ComponentSetpointExtensibleFields;
    }

    boost::optional<openstudio::IdfExtensibleGroup> PlantEquipmentOperationComponentSetpoint_Impl::componentGroup() const {
      auto object = getObject<openstudio::epmodel::PlantEquipmentOperationComponentSetpoint>();
      const auto groups = object.extensibleGroups();
      if (groups.empty()) {
        return {};
      }
      return groups.front();
    }

    boost::optional<double> PlantEquipmentOperationComponentSetpoint_Impl::component1FlowRate() const {
      if (auto group = componentGroup()) {
        return group->getDouble(ExtensibleFields::ComponentFlowRate, true);
      }
      return {};
    }

    bool PlantEquipmentOperationComponentSetpoint_Impl::isComponent1FlowRateAutosized() const {
      if (auto group = componentGroup()) {
        if (auto value = group->getString(ExtensibleFields::ComponentFlowRate, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
      }
      return false;
    }

    bool PlantEquipmentOperationComponentSetpoint_Impl::setComponent1FlowRate(double component1FlowRate) {
      if (auto group = componentGroup()) {
        const bool result = group->setDouble(ExtensibleFields::ComponentFlowRate, component1FlowRate);
        OS_ASSERT(result);
        return result;
      }
      return false;
    }

    void PlantEquipmentOperationComponentSetpoint_Impl::autosizeComponent1FlowRate() {
      if (auto group = componentGroup()) {
        OS_ASSERT(group->setString(ExtensibleFields::ComponentFlowRate, "autosize"));
      }
    }

    boost::optional<double> PlantEquipmentOperationComponentSetpoint_Impl::autosizedComponent1FlowRate() const {
      return {};
    }

    std::string PlantEquipmentOperationComponentSetpoint_Impl::component1OperationType() const {
      if (auto group = componentGroup()) {
        if (auto value = group->getString(ExtensibleFields::OperationType, true)) {
          OS_ASSERT(!value->empty());
          return *value;
        }
      }
      OS_ASSERT(false);
      return {};
    }

    bool PlantEquipmentOperationComponentSetpoint_Impl::setComponent1OperationType(const std::string& component1OperationType) {
      if (auto group = componentGroup()) {
        return group->setString(ExtensibleFields::OperationType, component1OperationType);
      }
      return false;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
