/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTLIST_IMPL_HPP
#define EPMODEL_ZONEHVACEQUIPMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {
  class ModelObject;
  class Schedule;
  class ThermalZone;
  namespace detail {

    class EPMODEL_API ZoneHVACEquipmentList_Impl : public ModelObject_Impl
    {
     public:
      enum class AddEquipmentFailureStage
      {
        None,
        AfterTargetPrepared,
        AfterExtensibleRowAdded,
      };

      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACEquipmentList_Impl() override = default;

      std::string loadDistributionScheme() const;
      bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
      bool isLoadDistributionSchemeDefaulted() const;
      void resetLoadDistributionScheme();
      std::vector<openstudio::epmodel::ModelObject> equipment() const;
      std::vector<openstudio::epmodel::ModelObject> equipmentInHeatingOrder() const;
      std::vector<openstudio::epmodel::ModelObject> equipmentInCoolingOrder() const;
      openstudio::epmodel::ThermalZone thermalZone() const;
      bool addEquipment(const openstudio::epmodel::ModelObject& component);
      bool addEquipment(const openstudio::epmodel::ModelObject& component, AddEquipmentFailureStage failureStage);
      bool removeEquipment(const openstudio::epmodel::ModelObject& component);
      bool setCoolingPriority(const openstudio::epmodel::ModelObject& component, unsigned priority);
      bool setHeatingPriority(const openstudio::epmodel::ModelObject& component, unsigned priority);
      unsigned heatingPriority(const openstudio::epmodel::ModelObject& component) const;
      unsigned coolingPriority(const openstudio::epmodel::ModelObject& component) const;
      boost::optional<double> sequentialCoolingFraction(const openstudio::epmodel::ModelObject& component) const;
      boost::optional<openstudio::epmodel::Schedule> sequentialCoolingFractionSchedule(const openstudio::epmodel::ModelObject& component) const;
      boost::optional<double> sequentialHeatingFraction(const openstudio::epmodel::ModelObject& component) const;
      boost::optional<openstudio::epmodel::Schedule> sequentialHeatingFractionSchedule(const openstudio::epmodel::ModelObject& component) const;
      bool setSequentialCoolingFraction(const openstudio::epmodel::ModelObject& component, double fraction);
      bool setSequentialCoolingFractionSchedule(const openstudio::epmodel::ModelObject& component, openstudio::epmodel::Schedule& schedule);
      bool setSequentialHeatingFraction(const openstudio::epmodel::ModelObject& component, double fraction);
      bool setSequentialHeatingFractionSchedule(const openstudio::epmodel::ModelObject& component, openstudio::epmodel::Schedule& schedule);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
