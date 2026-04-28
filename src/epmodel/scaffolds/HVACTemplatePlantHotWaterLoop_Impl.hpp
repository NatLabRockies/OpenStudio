/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTHOTWATERLOOP_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTHOTWATERLOOP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplatePlantHotWaterLoop_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplatePlantHotWaterLoop_Impl() override = default;

      std::string pumpControlType() const;
      bool isPumpControlTypeDefaulted() const;
      bool setPumpControlType(const std::string& pumpControlType);
      void resetPumpControlType();

      std::string hotWaterPlantOperationSchemeType() const;
      bool isHotWaterPlantOperationSchemeTypeDefaulted() const;
      bool setHotWaterPlantOperationSchemeType(const std::string& hotWaterPlantOperationSchemeType);
      void resetHotWaterPlantOperationSchemeType();

      double hotWaterDesignSetpoint() const;
      bool isHotWaterDesignSetpointDefaulted() const;
      bool setHotWaterDesignSetpoint(double hotWaterDesignSetpoint);
      void resetHotWaterDesignSetpoint();

      std::string hotWaterPumpConfiguration() const;
      bool isHotWaterPumpConfigurationDefaulted() const;
      bool setHotWaterPumpConfiguration(const std::string& hotWaterPumpConfiguration);
      void resetHotWaterPumpConfiguration();

      double hotWaterPumpRatedHead() const;
      bool isHotWaterPumpRatedHeadDefaulted() const;
      bool setHotWaterPumpRatedHead(double hotWaterPumpRatedHead);
      void resetHotWaterPumpRatedHead();

      std::string hotWaterSetpointResetType() const;
      bool isHotWaterSetpointResetTypeDefaulted() const;
      bool setHotWaterSetpointResetType(const std::string& hotWaterSetpointResetType);
      void resetHotWaterSetpointResetType();

      double hotWaterSetpointatOutdoorDryBulbLow() const;
      bool isHotWaterSetpointatOutdoorDryBulbLowDefaulted() const;
      bool setHotWaterSetpointatOutdoorDryBulbLow(double hotWaterSetpointatOutdoorDryBulbLow);
      void resetHotWaterSetpointatOutdoorDryBulbLow();

      double hotWaterResetOutdoorDryBulbLow() const;
      bool isHotWaterResetOutdoorDryBulbLowDefaulted() const;
      bool setHotWaterResetOutdoorDryBulbLow(double hotWaterResetOutdoorDryBulbLow);
      void resetHotWaterResetOutdoorDryBulbLow();

      double hotWaterSetpointatOutdoorDryBulbHigh() const;
      bool isHotWaterSetpointatOutdoorDryBulbHighDefaulted() const;
      bool setHotWaterSetpointatOutdoorDryBulbHigh(double hotWaterSetpointatOutdoorDryBulbHigh);
      void resetHotWaterSetpointatOutdoorDryBulbHigh();

      double hotWaterResetOutdoorDryBulbHigh() const;
      bool isHotWaterResetOutdoorDryBulbHighDefaulted() const;
      bool setHotWaterResetOutdoorDryBulbHigh(double hotWaterResetOutdoorDryBulbHigh);
      void resetHotWaterResetOutdoorDryBulbHigh();

      std::string hotWaterPumpType() const;
      bool isHotWaterPumpTypeDefaulted() const;
      bool setHotWaterPumpType(const std::string& hotWaterPumpType);
      void resetHotWaterPumpType();

      bool supplySideBypassPipe() const;
      bool isSupplySideBypassPipeDefaulted() const;
      bool setSupplySideBypassPipe(bool supplySideBypassPipe);
      void resetSupplySideBypassPipe();

      bool demandSideBypassPipe() const;
      bool isDemandSideBypassPipeDefaulted() const;
      bool setDemandSideBypassPipe(bool demandSideBypassPipe);
      void resetDemandSideBypassPipe();

      std::string fluidType() const;
      bool isFluidTypeDefaulted() const;
      bool setFluidType(const std::string& fluidType);
      void resetFluidType();

      double loopDesignDeltaTemperature() const;
      bool isLoopDesignDeltaTemperatureDefaulted() const;
      bool setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature);
      void resetLoopDesignDeltaTemperature();

      boost::optional<double> maximumOutdoorDryBulbTemperature() const;
      bool isMaximumOutdoorDryBulbTemperatureDefaulted() const;
      bool setMaximumOutdoorDryBulbTemperature(double maximumOutdoorDryBulbTemperature);
      void resetMaximumOutdoorDryBulbTemperature();

      std::string loadDistributionScheme() const;
      bool isLoadDistributionSchemeDefaulted() const;
      bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
      void resetLoadDistributionScheme();

      std::vector<std::string> pumpControlTypeValues() const;
      std::vector<std::string> hotWaterPlantOperationSchemeTypeValues() const;
      std::vector<std::string> hotWaterPumpConfigurationValues() const;
      std::vector<std::string> hotWaterSetpointResetTypeValues() const;
      std::vector<std::string> hotWaterPumpTypeValues() const;
      std::vector<std::string> fluidTypeValues() const;
      std::vector<std::string> loadDistributionSchemeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
