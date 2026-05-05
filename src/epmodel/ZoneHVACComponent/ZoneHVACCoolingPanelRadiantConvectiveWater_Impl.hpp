/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_IMPL_HPP
#define EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class ModelObject;
  class Schedule;
  class Surface;
  class ThermalZone;
  class ZoneHVACCoolingPanelRadiantConvectiveWater;

  namespace detail {

    class CoilCoolingWaterPanelRadiant_Impl;

    std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACCoolingPanelRadiantConvectiveWater& parent);

    class EPMODEL_API ZoneHVACCoolingPanelRadiantConvectiveWater_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACCoolingPanelRadiantConvectiveWater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToThermalZone(ThermalZone& thermalZone) override;
      void removeFromThermalZone() override;
      std::vector<ModelObject> children() const override;
      void doCanonicalize(LoadContext& context) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      double fractionRadiant() const;
      bool setFractionRadiant(double fractionRadiant);

      double fractionofRadiantEnergyIncidentonPeople() const;
      bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

      HVACComponent coolingCoil() const;
      bool setCoolingCoil(HVACComponent& coolingCoil);

      double ratedInletWaterTemperature() const;
      bool isRatedInletWaterTemperatureDefaulted() const;
      bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);
      void resetRatedInletWaterTemperature();

      double ratedInletSpaceTemperature() const;
      bool isRatedInletSpaceTemperatureDefaulted() const;
      bool setRatedInletSpaceTemperature(double ratedInletSpaceTemperature);
      void resetRatedInletSpaceTemperature();

      double ratedWaterMassFlowRate() const;
      bool isRatedWaterMassFlowRateDefaulted() const;
      bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
      void resetRatedWaterMassFlowRate();

      std::string coolingDesignCapacityMethod() const;
      bool isCoolingDesignCapacityMethodDefaulted() const;
      bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
      void resetCoolingDesignCapacityMethod();

      boost::optional<double> coolingDesignCapacity() const;
      bool isCoolingDesignCapacityAutosized() const;
      bool setCoolingDesignCapacity(double coolingDesignCapacity);
      void autosizeCoolingDesignCapacity();

      boost::optional<double> coolingDesignCapacityPerFloorArea() const;
      bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
      void resetCoolingDesignCapacityPerFloorArea();

      boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;
      bool setFractionOfAutosizedCoolingDesignCapacity(double fractionOfAutosizedCoolingDesignCapacity);
      void resetFractionOfAutosizedCoolingDesignCapacity();

      boost::optional<double> maximumChilledWaterFlowRate() const;
      bool isMaximumChilledWaterFlowRateAutosized() const;
      bool setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate);
      void autosizeMaximumChilledWaterFlowRate();

      std::string controlType() const;
      bool isControlTypeDefaulted() const;
      bool setControlType(const std::string& controlType);
      void resetControlType();

      double coolingControlThrottlingRange() const;
      bool isCoolingControlThrottlingRangeDefaulted() const;
      bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
      void resetCoolingControlThrottlingRange();

      std::string condensationControlType() const;
      bool isCondensationControlTypeDefaulted() const;
      bool setCondensationControlType(const std::string& condensationControlType);
      void resetCondensationControlType();

      double condensationControlDewpointOffset() const;
      bool isCondensationControlDewpointOffsetDefaulted() const;
      bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
      void resetCondensationControlDewpointOffset();

     private:
      friend class openstudio::epmodel::ZoneHVACCoolingPanelRadiantConvectiveWater;
      friend class CoilCoolingWaterPanelRadiant_Impl;

      boost::optional<Schedule> optionalAvailabilitySchedule() const;
      std::vector<Surface> zoneSurfaces() const;
      void rewriteSurfaceFractions();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
