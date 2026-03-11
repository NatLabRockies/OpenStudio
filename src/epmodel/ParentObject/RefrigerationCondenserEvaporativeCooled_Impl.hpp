/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSEREVAPORATIVECOOLED_IMPL_HPP
#define EPMODEL_REFRIGERATIONCONDENSEREVAPORATIVECOOLED_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <string>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RefrigerationCondenserEvaporativeCooled_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~RefrigerationCondenserEvaporativeCooled_Impl() override = default;

      double ratedEffectiveTotalHeatRejectionRate() const;
      bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);

      double ratedSubcoolingTemperatureDifference() const;
      bool isRatedSubcoolingTemperatureDifferenceDefaulted() const;
      bool setRatedSubcoolingTemperatureDifference(double ratedSubcoolingTemperatureDifference);
      void resetRatedSubcoolingTemperatureDifference();

      std::string fanSpeedControlType() const;
      bool isFanSpeedControlTypeDefaulted() const;
      bool setFanSpeedControlType(const std::string& fanSpeedControlType);
      void resetFanSpeedControlType();

      double ratedFanPower() const;
      bool setRatedFanPower(double ratedFanPower);

      double minimumFanAirFlowRatio() const;
      bool isMinimumFanAirFlowRatioDefaulted() const;
      bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
      void resetMinimumFanAirFlowRatio();

      double approachTemperatureConstantTerm() const;
      bool isApproachTemperatureConstantTermDefaulted() const;
      bool setApproachTemperatureConstantTerm(double approachTemperatureConstantTerm);
      void resetApproachTemperatureConstantTerm();

      double approachTemperatureCoefficient2() const;
      bool isApproachTemperatureCoefficient2Defaulted() const;
      bool setApproachTemperatureCoefficient2(double approachTemperatureCoefficient2);
      void resetApproachTemperatureCoefficient2();

      double approachTemperatureCoefficient3() const;
      bool isApproachTemperatureCoefficient3Defaulted() const;
      bool setApproachTemperatureCoefficient3(double approachTemperatureCoefficient3);
      void resetApproachTemperatureCoefficient3();

      double approachTemperatureCoefficient4() const;
      bool isApproachTemperatureCoefficient4Defaulted() const;
      bool setApproachTemperatureCoefficient4(double approachTemperatureCoefficient4);
      void resetApproachTemperatureCoefficient4();

      double minimumCapacityFactor() const;
      bool isMinimumCapacityFactorDefaulted() const;
      bool setMinimumCapacityFactor(double minimumCapacityFactor);
      void resetMinimumCapacityFactor();

      double maximumCapacityFactor() const;
      bool isMaximumCapacityFactorDefaulted() const;
      bool setMaximumCapacityFactor(double maximumCapacityFactor);
      void resetMaximumCapacityFactor();

      boost::optional<double> ratedAirFlowRate() const;
      bool isRatedAirFlowRateDefaulted() const;
      bool isRatedAirFlowRateAutocalculated() const;
      bool setRatedAirFlowRate(double ratedAirFlowRate);
      void resetRatedAirFlowRate();
      void autocalculateRatedAirFlowRate();

      double basinHeaterCapacity() const;
      bool isBasinHeaterCapacityDefaulted() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);
      void resetBasinHeaterCapacity();

      double basinHeaterSetpointTemperature() const;
      bool isBasinHeaterSetpointTemperatureDefaulted() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
      void resetBasinHeaterSetpointTemperature();

      boost::optional<double> ratedWaterPumpPower() const;
      bool isRatedWaterPumpPowerDefaulted() const;
      bool isRatedWaterPumpPowerAutocalculated() const;
      bool setRatedWaterPumpPower(double ratedWaterPumpPower);
      void resetRatedWaterPumpPower();
      void autocalculateRatedWaterPumpPower();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      double condenserRefrigerantOperatingChargeInventory() const;
      bool isCondenserRefrigerantOperatingChargeInventoryDefaulted() const;
      bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
      void resetCondenserRefrigerantOperatingChargeInventory();

      double condensateReceiverRefrigerantInventory() const;
      bool isCondensateReceiverRefrigerantInventoryDefaulted() const;
      bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
      void resetCondensateReceiverRefrigerantInventory();

      double condensatePipingRefrigerantInventory() const;
      bool isCondensatePipingRefrigerantInventoryDefaulted() const;
      bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
      void resetCondensatePipingRefrigerantInventory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
