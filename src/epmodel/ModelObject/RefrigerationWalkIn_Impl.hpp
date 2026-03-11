/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONWALKIN_IMPL_HPP
#define EPMODEL_REFRIGERATIONWALKIN_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationWalkIn_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationWalkIn_Impl() override = default;

      double ratedCoilCoolingCapacity() const;
      bool setRatedCoilCoolingCapacity(double ratedCoilCoolingCapacity);

      double operatingTemperature() const;
      bool setOperatingTemperature(double operatingTemperature);

      double ratedCoolingSourceTemperature() const;
      bool setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature);

      double ratedTotalHeatingPower() const;
      bool setRatedTotalHeatingPower(double ratedTotalHeatingPower);

      double ratedCoolingCoilFanPower() const;
      bool setRatedCoolingCoilFanPower(double ratedCoolingCoilFanPower);
      bool isRatedCoolingCoilFanPowerDefaulted() const;
      void resetRatedCoolingCoilFanPower();

      double ratedCirculationFanPower() const;
      bool setRatedCirculationFanPower(double ratedCirculationFanPower);
      bool isRatedCirculationFanPowerDefaulted() const;
      void resetRatedCirculationFanPower();

      double ratedTotalLightingPower() const;
      bool setRatedTotalLightingPower(double ratedTotalLightingPower);

      std::string defrostType() const;
      bool setDefrostType(const std::string& defrostType);
      bool isDefrostTypeDefaulted() const;
      void resetDefrostType();

      std::string defrostControlType() const;
      bool setDefrostControlType(const std::string& defrostControlType);
      bool isDefrostControlTypeDefaulted() const;
      void resetDefrostControlType();

      boost::optional<double> defrostPower() const;
      bool setDefrostPower(double defrostPower);
      void resetDefrostPower();

      boost::optional<double> temperatureTerminationDefrostFractiontoIce() const;
      bool setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce);
      void resetTemperatureTerminationDefrostFractiontoIce();

      double averageRefrigerantChargeInventory() const;
      bool setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory);
      bool isAverageRefrigerantChargeInventoryDefaulted() const;
      void resetAverageRefrigerantChargeInventory();

      double insulatedFloorSurfaceArea() const;
      bool setInsulatedFloorSurfaceArea(double insulatedFloorSurfaceArea);

      double insulatedFloorUValue() const;
      bool setInsulatedFloorUValue(double insulatedFloorUValue);
      bool isInsulatedFloorUValueDefaulted() const;
      void resetInsulatedFloorUValue();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONWALKIN_IMPL_HPP
