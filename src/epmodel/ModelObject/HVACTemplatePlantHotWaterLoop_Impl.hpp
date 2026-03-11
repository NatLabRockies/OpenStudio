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
  std::string hotWaterPlantOperationSchemeType() const;
  double hotWaterDesignSetpoint() const;
  std::string hotWaterPumpConfiguration() const;
  double hotWaterPumpRatedHead() const;
  std::string hotWaterSetpointResetType() const;
  double hotWaterSetpointatOutdoorDryBulbLow() const;
  double hotWaterResetOutdoorDryBulbLow() const;
  double hotWaterSetpointatOutdoorDryBulbHigh() const;
  double hotWaterResetOutdoorDryBulbHigh() const;
  std::string hotWaterPumpType() const;
  bool supplySideBypassPipe() const;
  bool demandSideBypassPipe() const;
  std::string fluidType() const;
  double loopDesignDeltaTemperature() const;
  boost::optional<double> maximumOutdoorDryBulbTemperature() const;
  std::string loadDistributionScheme() const;

  bool isPumpControlTypeDefaulted() const;
  bool isHotWaterPlantOperationSchemeTypeDefaulted() const;
  bool isHotWaterDesignSetpointDefaulted() const;
  bool isHotWaterPumpConfigurationDefaulted() const;
  bool isHotWaterPumpRatedHeadDefaulted() const;
  bool isHotWaterSetpointResetTypeDefaulted() const;
  bool isHotWaterSetpointatOutdoorDryBulbLowDefaulted() const;
  bool isHotWaterResetOutdoorDryBulbLowDefaulted() const;
  bool isHotWaterSetpointatOutdoorDryBulbHighDefaulted() const;
  bool isHotWaterResetOutdoorDryBulbHighDefaulted() const;
  bool isHotWaterPumpTypeDefaulted() const;
  bool isSupplySideBypassPipeDefaulted() const;
  bool isDemandSideBypassPipeDefaulted() const;
  bool isFluidTypeDefaulted() const;
  bool isLoopDesignDeltaTemperatureDefaulted() const;
  bool isLoadDistributionSchemeDefaulted() const;

  bool setPumpControlType(const std::string& pumpControlType);
  bool setHotWaterPlantOperationSchemeType(const std::string& hotWaterPlantOperationSchemeType);
  bool setHotWaterDesignSetpoint(double hotWaterDesignSetpoint);
  bool setHotWaterPumpConfiguration(const std::string& hotWaterPumpConfiguration);
  bool setHotWaterPumpRatedHead(double hotWaterPumpRatedHead);
  bool setHotWaterSetpointResetType(const std::string& hotWaterSetpointResetType);
  bool setHotWaterSetpointatOutdoorDryBulbLow(double hotWaterSetpointatOutdoorDryBulbLow);
  bool setHotWaterResetOutdoorDryBulbLow(double hotWaterResetOutdoorDryBulbLow);
  bool setHotWaterSetpointatOutdoorDryBulbHigh(double hotWaterSetpointatOutdoorDryBulbHigh);
  bool setHotWaterResetOutdoorDryBulbHigh(double hotWaterResetOutdoorDryBulbHigh);
  bool setHotWaterPumpType(const std::string& hotWaterPumpType);
  bool setSupplySideBypassPipe(bool supplySideBypassPipe);
  bool setDemandSideBypassPipe(bool demandSideBypassPipe);
  bool setFluidType(const std::string& fluidType);
  bool setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature);
  bool setMaximumOutdoorDryBulbTemperature(double maximumOutdoorDryBulbTemperature);
  bool setLoadDistributionScheme(const std::string& loadDistributionScheme);

  void resetPumpControlType();
  void resetHotWaterPlantOperationSchemeType();
  void resetHotWaterDesignSetpoint();
  void resetHotWaterPumpConfiguration();
  void resetHotWaterPumpRatedHead();
  void resetHotWaterSetpointResetType();
  void resetHotWaterSetpointatOutdoorDryBulbLow();
  void resetHotWaterResetOutdoorDryBulbLow();
  void resetHotWaterSetpointatOutdoorDryBulbHigh();
  void resetHotWaterResetOutdoorDryBulbHigh();
  void resetHotWaterPumpType();
  void resetSupplySideBypassPipe();
  void resetDemandSideBypassPipe();
  void resetFluidType();
  void resetLoopDesignDeltaTemperature();
  void resetMaximumOutdoorDryBulbTemperature();
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
