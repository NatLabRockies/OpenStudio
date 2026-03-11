/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTHOTWATERLOOP_HPP
#define EPMODEL_HVACTEMPLATEPLANTHOTWATERLOOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplatePlantHotWaterLoop_Impl;
}

class EPMODEL_API HVACTemplatePlantHotWaterLoop : public ModelObject
{
 public:
  explicit HVACTemplatePlantHotWaterLoop(const Model& model);

  virtual ~HVACTemplatePlantHotWaterLoop() override = default;
  HVACTemplatePlantHotWaterLoop(const HVACTemplatePlantHotWaterLoop& other) = default;
  HVACTemplatePlantHotWaterLoop(HVACTemplatePlantHotWaterLoop&& other) = default;
  HVACTemplatePlantHotWaterLoop& operator=(const HVACTemplatePlantHotWaterLoop&) = default;
  HVACTemplatePlantHotWaterLoop& operator=(HVACTemplatePlantHotWaterLoop&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> pumpControlTypeValues();
  static std::vector<std::string> hotWaterPlantOperationSchemeTypeValues();
  static std::vector<std::string> hotWaterPumpConfigurationValues();
  static std::vector<std::string> hotWaterSetpointResetTypeValues();
  static std::vector<std::string> hotWaterPumpTypeValues();
  static std::vector<std::string> fluidTypeValues();
  static std::vector<std::string> loadDistributionSchemeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:HotWaterLoop non-name, non-link scalar fields.
  // - Field Mapping: Pump/schedule/scheme name object-list fields are relationship-like and excluded from scalar accessors.
  // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
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

 protected:
  using ImplType = detail::HVACTemplatePlantHotWaterLoop_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplatePlantHotWaterLoop(std::shared_ptr<detail::HVACTemplatePlantHotWaterLoop_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
