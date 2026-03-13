/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTMIXEDWATERLOOP_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTMIXEDWATERLOOP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplatePlantMixedWaterLoop_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplatePlantMixedWaterLoop_Impl() override = default;

  std::string pumpControlType() const;
  bool isPumpControlTypeDefaulted() const;
  bool setPumpControlType(const std::string& pumpControlType);
  void resetPumpControlType();

  std::string operationSchemeType() const;
  bool isOperationSchemeTypeDefaulted() const;
  bool setOperationSchemeType(const std::string& operationSchemeType);
  void resetOperationSchemeType();

  double highTemperatureDesignSetpoint() const;
  bool isHighTemperatureDesignSetpointDefaulted() const;
  bool setHighTemperatureDesignSetpoint(double highTemperatureDesignSetpoint);
  void resetHighTemperatureDesignSetpoint();

  double lowTemperatureDesignSetpoint() const;
  bool isLowTemperatureDesignSetpointDefaulted() const;
  bool setLowTemperatureDesignSetpoint(double lowTemperatureDesignSetpoint);
  void resetLowTemperatureDesignSetpoint();

  std::string waterPumpConfiguration() const;
  bool isWaterPumpConfigurationDefaulted() const;
  bool setWaterPumpConfiguration(const std::string& waterPumpConfiguration);
  void resetWaterPumpConfiguration();

  double waterPumpRatedHead() const;
  bool isWaterPumpRatedHeadDefaulted() const;
  bool setWaterPumpRatedHead(double waterPumpRatedHead);
  void resetWaterPumpRatedHead();

  std::string waterPumpType() const;
  bool isWaterPumpTypeDefaulted() const;
  bool setWaterPumpType(const std::string& waterPumpType);
  void resetWaterPumpType();

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

  std::string loadDistributionScheme() const;
  bool isLoadDistributionSchemeDefaulted() const;
  bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
  void resetLoadDistributionScheme();

  std::vector<std::string> pumpControlTypeValues() const;
  std::vector<std::string> operationSchemeTypeValues() const;
  std::vector<std::string> waterPumpConfigurationValues() const;
  std::vector<std::string> waterPumpTypeValues() const;
  std::vector<std::string> fluidTypeValues() const;
  std::vector<std::string> loadDistributionSchemeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
