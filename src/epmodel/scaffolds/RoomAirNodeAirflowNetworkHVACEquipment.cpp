/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirNodeAirflowNetworkHVACEquipment.hpp"
#include "RoomAirNodeAirflowNetworkHVACEquipment_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/RoomAir_Node_AirflowNetwork_HVACEquipment_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  RoomAirNodeAirflowNetworkHVACEquipment::RoomAirNodeAirflowNetworkHVACEquipment(const Model& model)
    : ModelObject(RoomAirNodeAirflowNetworkHVACEquipment::iddObjectType(), model) {
    if (numExtensibleGroups() == 0u) {
      auto group = pushExtensibleGroup();
      OS_ASSERT(!group.empty());
    }
  }

  RoomAirNodeAirflowNetworkHVACEquipment::RoomAirNodeAirflowNetworkHVACEquipment(
    std::shared_ptr<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirNodeAirflowNetworkHVACEquipment::iddObjectType() {
    return IddObjectType::RoomAir_Node_AirflowNetwork_HVACEquipment;
  }

  boost::optional<double> RoomAirNodeAirflowNetworkHVACEquipment::fractionOfOutputOrSupplyAirFromHVACEquipment1() const {
    return getImpl<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl>()->fractionOfOutputOrSupplyAirFromHVACEquipment1();
  }

  bool
    RoomAirNodeAirflowNetworkHVACEquipment::setFractionOfOutputOrSupplyAirFromHVACEquipment1(double fractionOfOutputOrSupplyAirFromHVACEquipment1) {
    return getImpl<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl>()->setFractionOfOutputOrSupplyAirFromHVACEquipment1(
      fractionOfOutputOrSupplyAirFromHVACEquipment1);
  }

  void RoomAirNodeAirflowNetworkHVACEquipment::resetFractionOfOutputOrSupplyAirFromHVACEquipment1() {
    getImpl<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl>()->resetFractionOfOutputOrSupplyAirFromHVACEquipment1();
  }

  boost::optional<double> RoomAirNodeAirflowNetworkHVACEquipment::fractionOfInputOrReturnAirToHVACEquipment1() const {
    return getImpl<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl>()->fractionOfInputOrReturnAirToHVACEquipment1();
  }

  bool RoomAirNodeAirflowNetworkHVACEquipment::setFractionOfInputOrReturnAirToHVACEquipment1(double fractionOfInputOrReturnAirToHVACEquipment1) {
    return getImpl<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl>()->setFractionOfInputOrReturnAirToHVACEquipment1(
      fractionOfInputOrReturnAirToHVACEquipment1);
  }

  void RoomAirNodeAirflowNetworkHVACEquipment::resetFractionOfInputOrReturnAirToHVACEquipment1() {
    getImpl<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl>()->resetFractionOfInputOrReturnAirToHVACEquipment1();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      using ExtensibleFields = openstudio::RoomAir_Node_AirflowNetwork_HVACEquipmentExtensibleFields;
    }

    boost::optional<openstudio::IdfExtensibleGroup> RoomAirNodeAirflowNetworkHVACEquipment_Impl::equipmentGroup() const {
      auto object = getObject<openstudio::epmodel::RoomAirNodeAirflowNetworkHVACEquipment>();
      const auto groups = object.extensibleGroups();
      if (groups.empty()) {
        return {};
      }
      return groups.front();
    }

    openstudio::IdfExtensibleGroup RoomAirNodeAirflowNetworkHVACEquipment_Impl::ensureEquipmentGroup() const {
      auto object = getObject<openstudio::epmodel::RoomAirNodeAirflowNetworkHVACEquipment>();
      auto groups = object.extensibleGroups();
      if (!groups.empty()) {
        return groups.front();
      }
      auto group = object.pushExtensibleGroup();
      OS_ASSERT(!group.empty());
      return group;
    }

    boost::optional<double> RoomAirNodeAirflowNetworkHVACEquipment_Impl::fractionOfOutputOrSupplyAirFromHVACEquipment1() const {
      if (auto group = equipmentGroup()) {
        return group->getDouble(ExtensibleFields::FractionofOutputorSupplyAirfromHVACEquipment, true);
      }
      return {};
    }

    bool RoomAirNodeAirflowNetworkHVACEquipment_Impl::setFractionOfOutputOrSupplyAirFromHVACEquipment1(
      double fractionOfOutputOrSupplyAirFromHVACEquipment1) {
      auto group = ensureEquipmentGroup();
      ensureRelationshipFields(group);
      return group.setDouble(ExtensibleFields::FractionofOutputorSupplyAirfromHVACEquipment, fractionOfOutputOrSupplyAirFromHVACEquipment1);
    }

    void RoomAirNodeAirflowNetworkHVACEquipment_Impl::resetFractionOfOutputOrSupplyAirFromHVACEquipment1() {
      if (auto group = equipmentGroup()) {
        OS_ASSERT(group->setString(ExtensibleFields::FractionofOutputorSupplyAirfromHVACEquipment, ""));
      }
    }

    boost::optional<double> RoomAirNodeAirflowNetworkHVACEquipment_Impl::fractionOfInputOrReturnAirToHVACEquipment1() const {
      if (auto group = equipmentGroup()) {
        return group->getDouble(ExtensibleFields::FractionofInputorReturnAirtoHVACEquipment, true);
      }
      return {};
    }

    bool
      RoomAirNodeAirflowNetworkHVACEquipment_Impl::setFractionOfInputOrReturnAirToHVACEquipment1(double fractionOfInputOrReturnAirToHVACEquipment1) {
      auto group = ensureEquipmentGroup();
      ensureRelationshipFields(group);
      return group.setDouble(ExtensibleFields::FractionofInputorReturnAirtoHVACEquipment, fractionOfInputOrReturnAirToHVACEquipment1);
    }

    void RoomAirNodeAirflowNetworkHVACEquipment_Impl::resetFractionOfInputOrReturnAirToHVACEquipment1() {
      if (auto group = equipmentGroup()) {
        OS_ASSERT(group->setString(ExtensibleFields::FractionofInputorReturnAirtoHVACEquipment, ""));
      }
    }

    void RoomAirNodeAirflowNetworkHVACEquipment_Impl::ensureRelationshipFields(openstudio::IdfExtensibleGroup& group) const {
      const char* defaultType = "ZoneHVAC:PackagedTerminalAirConditioner";
      const char* defaultName = "RoomAirHVACEquipment";

      if (auto objectType = group.getString(ExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectType, true)) {
        if (objectType->empty()) {
          group.setString(ExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectType, defaultType);
        }
      } else {
        group.setString(ExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectType, defaultType);
      }

      if (auto objectName = group.getString(ExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectName, true)) {
        if (objectName->empty()) {
          group.setString(ExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectName, defaultName);
        }
      } else {
        group.setString(ExtensibleFields::ZoneHVACorAirTerminalEquipmentObjectName, defaultName);
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
