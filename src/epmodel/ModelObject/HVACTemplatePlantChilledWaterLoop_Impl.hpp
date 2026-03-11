/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTCHILLEDWATERLOOP_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTCHILLEDWATERLOOP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplatePlantChilledWaterLoop_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplatePlantChilledWaterLoop_Impl() override = default;

  std::string pumpControlType() const;
  std::string chillerPlantOperationSchemeType() const;
  double chilledWaterDesignSetpoint() const;
  std::string chilledWaterPumpConfiguration() const;
  double primaryChilledWaterPumpRatedHead() const;
  double secondaryChilledWaterPumpRatedHead() const;
  std::string condenserPlantOperationSchemeType() const;
  boost::optional<std::string> condenserWaterTemperatureControlType() const;
  double condenserWaterDesignSetpoint() const;
  double condenserWaterPumpRatedHead() const;
  std::string chilledWaterSetpointResetType() const;
  double chilledWaterSetpointatOutdoorDryBulbLow() const;
  double chilledWaterResetOutdoorDryBulbLow() const;
  double chilledWaterSetpointatOutdoorDryBulbHigh() const;
  double chilledWaterResetOutdoorDryBulbHigh() const;
  std::string chilledWaterPrimaryPumpType() const;
  std::string chilledWaterSecondaryPumpType() const;
  std::string condenserWaterPumpType() const;
  bool chilledWaterSupplySideBypassPipe() const;
  bool chilledWaterDemandSideBypassPipe() const;
  bool condenserWaterSupplySideBypassPipe() const;
  bool condenserWaterDemandSideBypassPipe() const;
  std::string fluidType() const;
  double loopDesignDeltaTemperature() const;
  boost::optional<double> minimumOutdoorDryBulbTemperature() const;
  std::string chilledWaterLoadDistributionScheme() const;
  std::string condenserWaterLoadDistributionScheme() const;

  bool isPumpControlTypeDefaulted() const;
  bool isChillerPlantOperationSchemeTypeDefaulted() const;
  bool isChilledWaterDesignSetpointDefaulted() const;
  bool isChilledWaterPumpConfigurationDefaulted() const;
  bool isPrimaryChilledWaterPumpRatedHeadDefaulted() const;
  bool isSecondaryChilledWaterPumpRatedHeadDefaulted() const;
  bool isCondenserPlantOperationSchemeTypeDefaulted() const;
  bool isCondenserWaterDesignSetpointDefaulted() const;
  bool isCondenserWaterPumpRatedHeadDefaulted() const;
  bool isChilledWaterSetpointResetTypeDefaulted() const;
  bool isChilledWaterSetpointatOutdoorDryBulbLowDefaulted() const;
  bool isChilledWaterResetOutdoorDryBulbLowDefaulted() const;
  bool isChilledWaterSetpointatOutdoorDryBulbHighDefaulted() const;
  bool isChilledWaterResetOutdoorDryBulbHighDefaulted() const;
  bool isChilledWaterPrimaryPumpTypeDefaulted() const;
  bool isChilledWaterSecondaryPumpTypeDefaulted() const;
  bool isCondenserWaterPumpTypeDefaulted() const;
  bool isChilledWaterSupplySideBypassPipeDefaulted() const;
  bool isChilledWaterDemandSideBypassPipeDefaulted() const;
  bool isCondenserWaterSupplySideBypassPipeDefaulted() const;
  bool isCondenserWaterDemandSideBypassPipeDefaulted() const;
  bool isFluidTypeDefaulted() const;
  bool isLoopDesignDeltaTemperatureDefaulted() const;
  bool isChilledWaterLoadDistributionSchemeDefaulted() const;
  bool isCondenserWaterLoadDistributionSchemeDefaulted() const;

  bool setPumpControlType(const std::string& pumpControlType);
  bool setChillerPlantOperationSchemeType(const std::string& chillerPlantOperationSchemeType);
  bool setChilledWaterDesignSetpoint(double chilledWaterDesignSetpoint);
  bool setChilledWaterPumpConfiguration(const std::string& chilledWaterPumpConfiguration);
  bool setPrimaryChilledWaterPumpRatedHead(double primaryChilledWaterPumpRatedHead);
  bool setSecondaryChilledWaterPumpRatedHead(double secondaryChilledWaterPumpRatedHead);
  bool setCondenserPlantOperationSchemeType(const std::string& condenserPlantOperationSchemeType);
  bool setCondenserWaterTemperatureControlType(const std::string& condenserWaterTemperatureControlType);
  bool setCondenserWaterDesignSetpoint(double condenserWaterDesignSetpoint);
  bool setCondenserWaterPumpRatedHead(double condenserWaterPumpRatedHead);
  bool setChilledWaterSetpointResetType(const std::string& chilledWaterSetpointResetType);
  bool setChilledWaterSetpointatOutdoorDryBulbLow(double chilledWaterSetpointatOutdoorDryBulbLow);
  bool setChilledWaterResetOutdoorDryBulbLow(double chilledWaterResetOutdoorDryBulbLow);
  bool setChilledWaterSetpointatOutdoorDryBulbHigh(double chilledWaterSetpointatOutdoorDryBulbHigh);
  bool setChilledWaterResetOutdoorDryBulbHigh(double chilledWaterResetOutdoorDryBulbHigh);
  bool setChilledWaterPrimaryPumpType(const std::string& chilledWaterPrimaryPumpType);
  bool setChilledWaterSecondaryPumpType(const std::string& chilledWaterSecondaryPumpType);
  bool setCondenserWaterPumpType(const std::string& condenserWaterPumpType);
  bool setChilledWaterSupplySideBypassPipe(bool chilledWaterSupplySideBypassPipe);
  bool setChilledWaterDemandSideBypassPipe(bool chilledWaterDemandSideBypassPipe);
  bool setCondenserWaterSupplySideBypassPipe(bool condenserWaterSupplySideBypassPipe);
  bool setCondenserWaterDemandSideBypassPipe(bool condenserWaterDemandSideBypassPipe);
  bool setFluidType(const std::string& fluidType);
  bool setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature);
  bool setMinimumOutdoorDryBulbTemperature(double minimumOutdoorDryBulbTemperature);
  bool setChilledWaterLoadDistributionScheme(const std::string& chilledWaterLoadDistributionScheme);
  bool setCondenserWaterLoadDistributionScheme(const std::string& condenserWaterLoadDistributionScheme);

  void resetPumpControlType();
  void resetChillerPlantOperationSchemeType();
  void resetChilledWaterDesignSetpoint();
  void resetChilledWaterPumpConfiguration();
  void resetPrimaryChilledWaterPumpRatedHead();
  void resetSecondaryChilledWaterPumpRatedHead();
  void resetCondenserPlantOperationSchemeType();
  void resetCondenserWaterTemperatureControlType();
  void resetCondenserWaterDesignSetpoint();
  void resetCondenserWaterPumpRatedHead();
  void resetChilledWaterSetpointResetType();
  void resetChilledWaterSetpointatOutdoorDryBulbLow();
  void resetChilledWaterResetOutdoorDryBulbLow();
  void resetChilledWaterSetpointatOutdoorDryBulbHigh();
  void resetChilledWaterResetOutdoorDryBulbHigh();
  void resetChilledWaterPrimaryPumpType();
  void resetChilledWaterSecondaryPumpType();
  void resetCondenserWaterPumpType();
  void resetChilledWaterSupplySideBypassPipe();
  void resetChilledWaterDemandSideBypassPipe();
  void resetCondenserWaterSupplySideBypassPipe();
  void resetCondenserWaterDemandSideBypassPipe();
  void resetFluidType();
  void resetLoopDesignDeltaTemperature();
  void resetMinimumOutdoorDryBulbTemperature();
  void resetChilledWaterLoadDistributionScheme();
  void resetCondenserWaterLoadDistributionScheme();

  std::vector<std::string> pumpControlTypeValues() const;
  std::vector<std::string> chillerPlantOperationSchemeTypeValues() const;
  std::vector<std::string> chilledWaterPumpConfigurationValues() const;
  std::vector<std::string> condenserPlantOperationSchemeTypeValues() const;
  std::vector<std::string> condenserWaterTemperatureControlTypeValues() const;
  std::vector<std::string> chilledWaterSetpointResetTypeValues() const;
  std::vector<std::string> chilledWaterPrimaryPumpTypeValues() const;
  std::vector<std::string> chilledWaterSecondaryPumpTypeValues() const;
  std::vector<std::string> condenserWaterPumpTypeValues() const;
  std::vector<std::string> fluidTypeValues() const;
  std::vector<std::string> chilledWaterLoadDistributionSchemeValues() const;
  std::vector<std::string> condenserWaterLoadDistributionSchemeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
