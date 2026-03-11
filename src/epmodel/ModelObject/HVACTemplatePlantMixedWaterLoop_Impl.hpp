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
  std::string operationSchemeType() const;
  double highTemperatureDesignSetpoint() const;
  double lowTemperatureDesignSetpoint() const;
  std::string waterPumpConfiguration() const;
  double waterPumpRatedHead() const;
  std::string waterPumpType() const;
  bool supplySideBypassPipe() const;
  bool demandSideBypassPipe() const;
  std::string fluidType() const;
  double loopDesignDeltaTemperature() const;
  std::string loadDistributionScheme() const;

  bool isPumpControlTypeDefaulted() const;
  bool isOperationSchemeTypeDefaulted() const;
  bool isHighTemperatureDesignSetpointDefaulted() const;
  bool isLowTemperatureDesignSetpointDefaulted() const;
  bool isWaterPumpConfigurationDefaulted() const;
  bool isWaterPumpRatedHeadDefaulted() const;
  bool isWaterPumpTypeDefaulted() const;
  bool isSupplySideBypassPipeDefaulted() const;
  bool isDemandSideBypassPipeDefaulted() const;
  bool isFluidTypeDefaulted() const;
  bool isLoopDesignDeltaTemperatureDefaulted() const;
  bool isLoadDistributionSchemeDefaulted() const;

  bool setPumpControlType(const std::string& pumpControlType);
  bool setOperationSchemeType(const std::string& operationSchemeType);
  bool setHighTemperatureDesignSetpoint(double highTemperatureDesignSetpoint);
  bool setLowTemperatureDesignSetpoint(double lowTemperatureDesignSetpoint);
  bool setWaterPumpConfiguration(const std::string& waterPumpConfiguration);
  bool setWaterPumpRatedHead(double waterPumpRatedHead);
  bool setWaterPumpType(const std::string& waterPumpType);
  bool setSupplySideBypassPipe(bool supplySideBypassPipe);
  bool setDemandSideBypassPipe(bool demandSideBypassPipe);
  bool setFluidType(const std::string& fluidType);
  bool setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature);
  bool setLoadDistributionScheme(const std::string& loadDistributionScheme);

  void resetPumpControlType();
  void resetOperationSchemeType();
  void resetHighTemperatureDesignSetpoint();
  void resetLowTemperatureDesignSetpoint();
  void resetWaterPumpConfiguration();
  void resetWaterPumpRatedHead();
  void resetWaterPumpType();
  void resetSupplySideBypassPipe();
  void resetDemandSideBypassPipe();
  void resetFluidType();
  void resetLoopDesignDeltaTemperature();
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
