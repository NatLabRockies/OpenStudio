/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMPONENTCOSTLINEITEM_HPP
#define EPMODEL_COMPONENTCOSTLINEITEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ComponentCostLineItem_Impl;
  }

  class EPMODEL_API ComponentCostLineItem : public ModelObject
  {
   public:
    explicit ComponentCostLineItem(const Model& model);

    virtual ~ComponentCostLineItem() override = default;
    ComponentCostLineItem(const ComponentCostLineItem& other) = default;
    ComponentCostLineItem(ComponentCostLineItem&& other) = default;
    ComponentCostLineItem& operator=(const ComponentCostLineItem&) = default;
    ComponentCostLineItem& operator=(ComponentCostLineItem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> lineItemTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar accessors map directly to EnergyPlus ComponentCost:LineItem scalar fields.
    // - Field Mapping: Name remains available through base ModelObject naming API.
    // - TODO(parity): Add relationship helpers only if future schema revisions introduce object-list/reference links.
    boost::optional<std::string> type() const;
    bool setType(const std::string& type);
    void resetType();

    std::string lineItemType() const;
    bool setLineItemType(const std::string& lineItemType);

    std::string itemName() const;
    bool setItemName(const std::string& itemName);

    boost::optional<std::string> objectEndUseKey() const;
    bool setObjectEndUseKey(const std::string& objectEndUseKey);
    void resetObjectEndUseKey();

    boost::optional<double> costperEach() const;
    bool setCostperEach(double costperEach);
    void resetCostperEach();

    boost::optional<double> costperArea() const;
    bool setCostperArea(double costperArea);
    void resetCostperArea();

    boost::optional<double> costperUnitofOutputCapacity() const;
    bool setCostperUnitofOutputCapacity(double costperUnitofOutputCapacity);
    void resetCostperUnitofOutputCapacity();

    boost::optional<double> costperUnitofOutputCapacityperCOP() const;
    bool setCostperUnitofOutputCapacityperCOP(double costperUnitofOutputCapacityperCOP);
    void resetCostperUnitofOutputCapacityperCOP();

    boost::optional<double> costperVolume() const;
    bool setCostperVolume(double costperVolume);
    void resetCostperVolume();

    boost::optional<double> costperVolumeRate() const;
    bool setCostperVolumeRate(double costperVolumeRate);
    void resetCostperVolumeRate();

    boost::optional<double> costperEnergyperTemperatureDifference() const;
    bool setCostperEnergyperTemperatureDifference(double costperEnergyperTemperatureDifference);
    void resetCostperEnergyperTemperatureDifference();

    boost::optional<double> quantity() const;
    bool setQuantity(double quantity);
    void resetQuantity();

   protected:
    using ImplType = detail::ComponentCostLineItem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ComponentCostLineItem(std::shared_ptr<detail::ComponentCostLineItem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
