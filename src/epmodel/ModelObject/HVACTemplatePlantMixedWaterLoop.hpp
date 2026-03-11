/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTMIXEDWATERLOOP_HPP
#define EPMODEL_HVACTEMPLATEPLANTMIXEDWATERLOOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplatePlantMixedWaterLoop_Impl;
}

class EPMODEL_API HVACTemplatePlantMixedWaterLoop : public ModelObject
{
 public:
  explicit HVACTemplatePlantMixedWaterLoop(const Model& model);

  virtual ~HVACTemplatePlantMixedWaterLoop() override = default;
  HVACTemplatePlantMixedWaterLoop(const HVACTemplatePlantMixedWaterLoop& other) = default;
  HVACTemplatePlantMixedWaterLoop(HVACTemplatePlantMixedWaterLoop&& other) = default;
  HVACTemplatePlantMixedWaterLoop& operator=(const HVACTemplatePlantMixedWaterLoop&) = default;
  HVACTemplatePlantMixedWaterLoop& operator=(HVACTemplatePlantMixedWaterLoop&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> pumpControlTypeValues();
  static std::vector<std::string> operationSchemeTypeValues();
  static std::vector<std::string> waterPumpConfigurationValues();
  static std::vector<std::string> waterPumpTypeValues();
  static std::vector<std::string> fluidTypeValues();
  static std::vector<std::string> loadDistributionSchemeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:MixedWaterLoop non-name, non-link scalar fields.
  // - Field Mapping: Pump/schedule/scheme name object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
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

 protected:
  using ImplType = detail::HVACTemplatePlantMixedWaterLoop_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplatePlantMixedWaterLoop(std::shared_ptr<detail::HVACTemplatePlantMixedWaterLoop_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
