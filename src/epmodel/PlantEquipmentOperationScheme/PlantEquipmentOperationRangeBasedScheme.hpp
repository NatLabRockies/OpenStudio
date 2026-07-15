/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONRANGEBASEDSCHEME_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONRANGEBASEDSCHEME_HPP

#include "EPModelAPI.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;

  namespace detail {
    class PlantEquipmentOperationRangeBasedScheme_Impl;
  }

  class EPMODEL_API PlantEquipmentOperationRangeBasedScheme : public PlantEquipmentOperationScheme
  {
   public:
    PlantEquipmentOperationRangeBasedScheme(IddObjectType type, const Model& model);

    virtual ~PlantEquipmentOperationRangeBasedScheme() override = default;
    PlantEquipmentOperationRangeBasedScheme(const PlantEquipmentOperationRangeBasedScheme& other) = default;
    PlantEquipmentOperationRangeBasedScheme(PlantEquipmentOperationRangeBasedScheme&& other) = default;
    PlantEquipmentOperationRangeBasedScheme& operator=(const PlantEquipmentOperationRangeBasedScheme&) = default;
    PlantEquipmentOperationRangeBasedScheme& operator=(PlantEquipmentOperationRangeBasedScheme&&) = default;

    // Schema Alignment Notes:
    // - Canonical Counterpart: openstudio::model::PlantEquipmentOperationRangeBasedScheme.
    // - API: Mirrors the canonical load-range/equipment API. epmodel stores each range's equipment in an EnergyPlus PlantEquipmentList.
    double maximumUpperLimit() const;
    double minimumLowerLimit() const;
    bool addLoadRange(double upperLimit, const std::vector<HVACComponent>& equipment);
    std::vector<HVACComponent> removeLoadRange(double upperLimit);
    std::vector<double> loadRangeUpperLimits() const;
    std::vector<HVACComponent> equipment(double upperLimit) const;
    bool addEquipment(double upperLimit, const HVACComponent& equipment);
    bool addEquipment(const HVACComponent& equipment);
    bool replaceEquipment(double upperLimit, const std::vector<HVACComponent>& equipment);
    bool replaceEquipment(const std::vector<HVACComponent>& equipment);
    bool removeEquipment(double upperLimit, const HVACComponent& equipment);
    bool removeEquipment(const HVACComponent& equipment);
    void clearLoadRanges();

   protected:
    using ImplType = detail::PlantEquipmentOperationRangeBasedScheme_Impl;

    explicit PlantEquipmentOperationRangeBasedScheme(std::shared_ptr<detail::PlantEquipmentOperationRangeBasedScheme_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
