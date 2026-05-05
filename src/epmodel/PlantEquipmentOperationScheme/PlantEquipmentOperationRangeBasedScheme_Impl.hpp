/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONRANGEBASEDSCHEME_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONRANGEBASEDSCHEME_IMPL_HPP

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationScheme_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class HVACComponent;

  namespace detail {

    class EPMODEL_API PlantEquipmentOperationRangeBasedScheme_Impl : public PlantEquipmentOperationScheme_Impl
    {
     public:
      PlantEquipmentOperationRangeBasedScheme_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationRangeBasedScheme_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      PlantEquipmentOperationRangeBasedScheme_Impl(const PlantEquipmentOperationRangeBasedScheme_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~PlantEquipmentOperationRangeBasedScheme_Impl() override = default;

      double maximumUpperLimit() const;
      double minimumLowerLimit() const;
      bool addLoadRange(double upperLimit, const std::vector<openstudio::epmodel::HVACComponent>& equipment);
      std::vector<openstudio::epmodel::HVACComponent> removeLoadRange(double upperLimit);
      std::vector<double> loadRangeUpperLimits() const;
      std::vector<openstudio::epmodel::HVACComponent> equipment(double upperLimit) const;
      bool addEquipment(double upperLimit, const openstudio::epmodel::HVACComponent& equipment);
      bool addEquipment(const openstudio::epmodel::HVACComponent& equipment);
      bool replaceEquipment(double upperLimit, const std::vector<openstudio::epmodel::HVACComponent>& equipment);
      bool replaceEquipment(const std::vector<openstudio::epmodel::HVACComponent>& equipment);
      bool removeEquipment(double upperLimit, const openstudio::epmodel::HVACComponent& equipment);
      bool removeEquipment(const openstudio::epmodel::HVACComponent& equipment);
      void clearLoadRanges();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
