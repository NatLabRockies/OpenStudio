/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ComponentCostLineItem.hpp"
#include "ComponentCostLineItem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ComponentCost_LineItem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  ComponentCostLineItem::ComponentCostLineItem(const Model& model) : ModelObject(ComponentCostLineItem::iddObjectType(), model) {}

  ComponentCostLineItem::ComponentCostLineItem(std::shared_ptr<detail::ComponentCostLineItem_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ComponentCostLineItem::iddObjectType() {
    return IddObjectType::ComponentCost_LineItem;
  }

  std::vector<std::string> ComponentCostLineItem::lineItemTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ComponentCost_LineItemFields::LineItemType);
  }

  boost::optional<std::string> ComponentCostLineItem::type() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->type();
  }

  bool ComponentCostLineItem::setType(const std::string& type) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setType(type);
  }

  void ComponentCostLineItem::resetType() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetType();
  }

  std::string ComponentCostLineItem::lineItemType() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->lineItemType();
  }

  bool ComponentCostLineItem::setLineItemType(const std::string& lineItemType) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setLineItemType(lineItemType);
  }

  std::string ComponentCostLineItem::itemName() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->itemName();
  }

  bool ComponentCostLineItem::setItemName(const std::string& itemName) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setItemName(itemName);
  }

  boost::optional<std::string> ComponentCostLineItem::objectEndUseKey() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->objectEndUseKey();
  }

  bool ComponentCostLineItem::setObjectEndUseKey(const std::string& objectEndUseKey) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setObjectEndUseKey(objectEndUseKey);
  }

  void ComponentCostLineItem::resetObjectEndUseKey() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetObjectEndUseKey();
  }

  boost::optional<double> ComponentCostLineItem::costperEach() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperEach();
  }

  bool ComponentCostLineItem::setCostperEach(double costperEach) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperEach(costperEach);
  }

  void ComponentCostLineItem::resetCostperEach() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperEach();
  }

  boost::optional<double> ComponentCostLineItem::costperArea() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperArea();
  }

  bool ComponentCostLineItem::setCostperArea(double costperArea) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperArea(costperArea);
  }

  void ComponentCostLineItem::resetCostperArea() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperArea();
  }

  boost::optional<double> ComponentCostLineItem::costperUnitofOutputCapacity() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperUnitofOutputCapacity();
  }

  bool ComponentCostLineItem::setCostperUnitofOutputCapacity(double costperUnitofOutputCapacity) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperUnitofOutputCapacity(costperUnitofOutputCapacity);
  }

  void ComponentCostLineItem::resetCostperUnitofOutputCapacity() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperUnitofOutputCapacity();
  }

  boost::optional<double> ComponentCostLineItem::costperUnitofOutputCapacityperCOP() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperUnitofOutputCapacityperCOP();
  }

  bool ComponentCostLineItem::setCostperUnitofOutputCapacityperCOP(double costperUnitofOutputCapacityperCOP) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperUnitofOutputCapacityperCOP(costperUnitofOutputCapacityperCOP);
  }

  void ComponentCostLineItem::resetCostperUnitofOutputCapacityperCOP() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperUnitofOutputCapacityperCOP();
  }

  boost::optional<double> ComponentCostLineItem::costperVolume() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperVolume();
  }

  bool ComponentCostLineItem::setCostperVolume(double costperVolume) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperVolume(costperVolume);
  }

  void ComponentCostLineItem::resetCostperVolume() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperVolume();
  }

  boost::optional<double> ComponentCostLineItem::costperVolumeRate() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperVolumeRate();
  }

  bool ComponentCostLineItem::setCostperVolumeRate(double costperVolumeRate) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperVolumeRate(costperVolumeRate);
  }

  void ComponentCostLineItem::resetCostperVolumeRate() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperVolumeRate();
  }

  boost::optional<double> ComponentCostLineItem::costperEnergyperTemperatureDifference() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->costperEnergyperTemperatureDifference();
  }

  bool ComponentCostLineItem::setCostperEnergyperTemperatureDifference(double costperEnergyperTemperatureDifference) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setCostperEnergyperTemperatureDifference(costperEnergyperTemperatureDifference);
  }

  void ComponentCostLineItem::resetCostperEnergyperTemperatureDifference() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetCostperEnergyperTemperatureDifference();
  }

  boost::optional<double> ComponentCostLineItem::quantity() const {
    return getImpl<detail::ComponentCostLineItem_Impl>()->quantity();
  }

  bool ComponentCostLineItem::setQuantity(double quantity) {
    return getImpl<detail::ComponentCostLineItem_Impl>()->setQuantity(quantity);
  }

  void ComponentCostLineItem::resetQuantity() {
    getImpl<detail::ComponentCostLineItem_Impl>()->resetQuantity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> ComponentCostLineItem_Impl::lineItemTypeValues() const {
      return openstudio::epmodel::ComponentCostLineItem::lineItemTypeValues();
    }

    boost::optional<std::string> ComponentCostLineItem_Impl::type() const {
      return getString(openstudio::ComponentCost_LineItemFields::Type, true);
    }

    bool ComponentCostLineItem_Impl::setType(const std::string& type) {
      return setString(openstudio::ComponentCost_LineItemFields::Type, type);
    }

    void ComponentCostLineItem_Impl::resetType() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::Type, ""));
    }

    std::string ComponentCostLineItem_Impl::lineItemType() const {
      const auto value = getString(openstudio::ComponentCost_LineItemFields::LineItemType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ComponentCostLineItem_Impl::setLineItemType(const std::string& lineItemType) {
      return setString(openstudio::ComponentCost_LineItemFields::LineItemType, lineItemType);
    }

    std::string ComponentCostLineItem_Impl::itemName() const {
      const auto value = getString(openstudio::ComponentCost_LineItemFields::ItemName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ComponentCostLineItem_Impl::setItemName(const std::string& itemName) {
      return setString(openstudio::ComponentCost_LineItemFields::ItemName, itemName);
    }

    boost::optional<std::string> ComponentCostLineItem_Impl::objectEndUseKey() const {
      return getString(openstudio::ComponentCost_LineItemFields::ObjectEndUseKey, true);
    }

    bool ComponentCostLineItem_Impl::setObjectEndUseKey(const std::string& objectEndUseKey) {
      return setString(openstudio::ComponentCost_LineItemFields::ObjectEndUseKey, objectEndUseKey);
    }

    void ComponentCostLineItem_Impl::resetObjectEndUseKey() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::ObjectEndUseKey, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperEach() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperEach, true);
    }

    bool ComponentCostLineItem_Impl::setCostperEach(double costperEach) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::CostperEach, costperEach);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperEach() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperEach, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperArea() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperArea, true);
    }

    bool ComponentCostLineItem_Impl::setCostperArea(double costperArea) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::CostperArea, costperArea);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperArea() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperArea, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperUnitofOutputCapacity() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperUnitofOutputCapacity, true);
    }

    bool ComponentCostLineItem_Impl::setCostperUnitofOutputCapacity(double costperUnitofOutputCapacity) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::CostperUnitofOutputCapacity, costperUnitofOutputCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperUnitofOutputCapacity() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperUnitofOutputCapacity, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperUnitofOutputCapacityperCOP() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperUnitofOutputCapacityperCOP, true);
    }

    bool ComponentCostLineItem_Impl::setCostperUnitofOutputCapacityperCOP(double costperUnitofOutputCapacityperCOP) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::CostperUnitofOutputCapacityperCOP, costperUnitofOutputCapacityperCOP);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperUnitofOutputCapacityperCOP() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperUnitofOutputCapacityperCOP, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperVolume() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperVolume, true);
    }

    bool ComponentCostLineItem_Impl::setCostperVolume(double costperVolume) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::CostperVolume, costperVolume);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperVolume() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperVolume, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperVolumeRate() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperVolumeRate, true);
    }

    bool ComponentCostLineItem_Impl::setCostperVolumeRate(double costperVolumeRate) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::CostperVolumeRate, costperVolumeRate);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperVolumeRate() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperVolumeRate, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::costperEnergyperTemperatureDifference() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::CostperEnergyperTemperatureDifference, true);
    }

    bool ComponentCostLineItem_Impl::setCostperEnergyperTemperatureDifference(double costperEnergyperTemperatureDifference) {
      const bool result =
        setDouble(openstudio::ComponentCost_LineItemFields::CostperEnergyperTemperatureDifference, costperEnergyperTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetCostperEnergyperTemperatureDifference() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::CostperEnergyperTemperatureDifference, ""));
    }

    boost::optional<double> ComponentCostLineItem_Impl::quantity() const {
      return getDouble(openstudio::ComponentCost_LineItemFields::Quantity, true);
    }

    bool ComponentCostLineItem_Impl::setQuantity(double quantity) {
      const bool result = setDouble(openstudio::ComponentCost_LineItemFields::Quantity, quantity);
      OS_ASSERT(result);
      return result;
    }

    void ComponentCostLineItem_Impl::resetQuantity() {
      OS_ASSERT(setString(openstudio::ComponentCost_LineItemFields::Quantity, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
