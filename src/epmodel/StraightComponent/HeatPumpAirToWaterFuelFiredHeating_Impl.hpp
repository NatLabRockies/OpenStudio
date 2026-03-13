/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPAIRTOWATERFUELFIREDHEATING_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatPumpAirToWaterFuelFiredHeating_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~HeatPumpAirToWaterFuelFiredHeating_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::string fuelType() const;
      bool setFuelType(const std::string& fuelType);

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      bool isEndUseSubcategoryDefaulted() const;
      void resetEndUseSubcategory();

      boost::optional<double> nominalHeatingCapacity() const;
      bool setNominalHeatingCapacity(double nominalHeatingCapacity);
      void resetNominalHeatingCapacity();
      bool isNominalHeatingCapacityAutosized() const;
      boost::optional<double> autosizedNominalHeatingCapacity();
      void autosizeNominalHeatingCapacity();

      double nominalCOP() const;
      bool setNominalCOP(double nominalCOP);

      boost::optional<double> designFlowRate() const;
      bool setDesignFlowRate(double designFlowRate);
      void resetDesignFlowRate();
      bool isDesignFlowRateAutosized() const;
      boost::optional<double> autosizedDesignFlowRate();
      void autosizeDesignFlowRate();

      double designSupplyTemperature() const;
      bool setDesignSupplyTemperature(double designSupplyTemperature);

      boost::optional<double> designTemperatureLift() const;
      bool setDesignTemperatureLift(double designTemperatureLift);
      bool isDesignTemperatureLiftAutosized() const;
      boost::optional<double> autosizedDesignTemperatureLift();
      void autosizeDesignTemperatureLift();

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);

      std::string flowMode() const;
      bool setFlowMode(const std::string& flowMode);

      std::string outdoorAirTemperatureCurveInputVariable() const;
      bool setOutdoorAirTemperatureCurveInputVariable(const std::string& outdoorAirTemperatureCurveInputVariable);

      std::string waterTemperatureCurveInputVariable() const;
      bool setWaterTemperatureCurveInputVariable(const std::string& waterTemperatureCurveInputVariable);

      double minimumPartLoadRatio() const;
      bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

      double maximumPartLoadRatio() const;
      bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

      std::string defrostControlType() const;
      bool setDefrostControlType(const std::string& defrostControlType);

      double defrostOperationTimeFraction() const;
      bool setDefrostOperationTimeFraction(double defrostOperationTimeFraction);

      double resistiveDefrostHeaterCapacity() const;
      bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);

      double maximumOutdoorDrybulbTemperatureforDefrostOperation() const;
      bool setMaximumOutdoorDrybulbTemperatureforDefrostOperation(double maximumOutdoorDrybulbTemperatureforDefrostOperation);

      double nominalAuxiliaryElectricPower() const;
      bool setNominalAuxiliaryElectricPower(double nominalAuxiliaryElectricPower);

      double standbyElectricPower() const;
      bool setStandbyElectricPower(double standbyElectricPower);

      double minimumUnloadingRatio() const;
      bool setMinimumUnloadingRatio(double minimumUnloadingRatio);

      std::vector<std::string> fuelTypeValues() const;
      std::vector<std::string> flowModeValues() const;
      std::vector<std::string> outdoorAirTemperatureCurveInputVariableValues() const;
      std::vector<std::string> waterTemperatureCurveInputVariableValues() const;
      std::vector<std::string> defrostControlTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
