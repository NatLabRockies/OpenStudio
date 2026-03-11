/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGSYSTEM_HPP
#define EPMODEL_SIZINGSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class AirLoopHVAC;

namespace detail {
class SizingSystem_Impl;
}

class EPMODEL_API SizingSystem : public ModelObject
{
 public:
  explicit SizingSystem(const Model& model, const AirLoopHVAC& airLoopHVAC);

  virtual ~SizingSystem() override = default;
  SizingSystem(const SizingSystem& other) = default;
  SizingSystem(SizingSystem&& other) = default;
  SizingSystem& operator=(const SizingSystem&) = default;
  SizingSystem& operator=(SizingSystem&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validTypeofLoadtoSizeOnValues();
  static std::vector<std::string> validSizingOptionValues();
  static std::vector<std::string> validCoolingDesignAirFlowMethodValues();
  static std::vector<std::string> validHeatingDesignAirFlowMethodValues();
  static std::vector<std::string> validSystemOutdoorAirMethodValues();
  static std::vector<std::string> heatingCoilSizingMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model SizingSystem scalar accessor names/signatures.
  // - Field Mapping: sizingOption maps to E+ Sizing:System field Type of Zone Sum to Use.
  // - Field Mapping: cooling/heatingDesignAirFlowMethod and cooling/heatingDesignAirFlowRate
  //   map to E+ Cooling/Heating Supply Air Flow Rate Method/Rate fields.
  // - Field Mapping: AirLoopName is a relationship field and is intentionally excluded from
  //   scalar accessor coverage.
  // - ForwardTranslator Evidence: ForwardTranslateSizingSystem confirms these drift mappings.
  // - TODO(parity): Add relationship accessor parity for AirLoopName in a non-scalar pass.
  std::string typeofLoadtoSizeOn() const;
  bool isTypeofLoadtoSizeOnDefaulted() const;

  boost::optional<double> designOutdoorAirFlowRate() const;
  bool isDesignOutdoorAirFlowRateDefaulted() const;
  bool isDesignOutdoorAirFlowRateAutosized() const;

  boost::optional<double> centralHeatingMaximumSystemAirFlowRatio() const;
  bool isCentralHeatingMaximumSystemAirFlowRatioDefaulted() const;
  bool isCentralHeatingMaximumSystemAirFlowRatioAutosized() const;

  double preheatDesignTemperature() const;
  double preheatDesignHumidityRatio() const;
  double precoolDesignTemperature() const;
  double precoolDesignHumidityRatio() const;
  double centralCoolingDesignSupplyAirTemperature() const;
  double centralHeatingDesignSupplyAirTemperature() const;

  std::string sizingOption() const;
  bool isSizingOptionDefaulted() const;

  bool allOutdoorAirinCooling() const;
  bool isAllOutdoorAirinCoolingDefaulted() const;

  bool allOutdoorAirinHeating() const;
  bool isAllOutdoorAirinHeatingDefaulted() const;

  double centralCoolingDesignSupplyAirHumidityRatio() const;
  bool isCentralCoolingDesignSupplyAirHumidityRatioDefaulted() const;

  double centralHeatingDesignSupplyAirHumidityRatio() const;
  bool isCentralHeatingDesignSupplyAirHumidityRatioDefaulted() const;

  std::string coolingDesignAirFlowMethod() const;
  bool isCoolingDesignAirFlowMethodDefaulted() const;

  double coolingDesignAirFlowRate() const;
  bool isCoolingDesignAirFlowRateDefaulted() const;

  std::string heatingDesignAirFlowMethod() const;
  bool isHeatingDesignAirFlowMethodDefaulted() const;

  double heatingDesignAirFlowRate() const;
  bool isHeatingDesignAirFlowRateDefaulted() const;

  std::string systemOutdoorAirMethod() const;
  bool isSystemOutdoorAirMethodDefaulted() const;

  double zoneMaximumOutdoorAirFraction() const;
  double coolingSupplyAirFlowRatePerFloorArea() const;
  double coolingFractionofAutosizedCoolingSupplyAirFlowRate() const;
  double coolingSupplyAirFlowRatePerUnitCoolingCapacity() const;
  double heatingSupplyAirFlowRatePerFloorArea() const;
  double heatingFractionofAutosizedHeatingSupplyAirFlowRate() const;
  double heatingFractionofAutosizedCoolingSupplyAirFlowRate() const;
  double heatingSupplyAirFlowRatePerUnitHeatingCapacity() const;

  std::string coolingDesignCapacityMethod() const;
  boost::optional<double> coolingDesignCapacity() const;
  bool isCoolingDesignCapacityAutosized() const;
  double coolingDesignCapacityPerFloorArea() const;
  double fractionofAutosizedCoolingDesignCapacity() const;

  std::string heatingDesignCapacityMethod() const;
  boost::optional<double> heatingDesignCapacity() const;
  bool isHeatingDesignCapacityAutosized() const;
  double heatingDesignCapacityPerFloorArea() const;
  double fractionofAutosizedHeatingDesignCapacity() const;

  std::string centralCoolingCapacityControlMethod() const;

  boost::optional<double> occupantDiversity() const;
  bool isOccupantDiversityAutosized() const;

  std::string heatingCoilSizingMethod() const;
  double maximumHeatingCapacityToCoolingCapacitySizingRatio() const;

  bool setTypeofLoadtoSizeOn(const std::string& typeofLoadtoSizeOn);
  void resetTypeofLoadtoSizeOn();

  bool setDesignOutdoorAirFlowRate(double designOutdoorAirFlowRate);
  void resetDesignOutdoorAirFlowRate();
  void autosizeDesignOutdoorAirFlowRate();

  bool setCentralHeatingMaximumSystemAirFlowRatio(double centralHeatingMaximumSystemAirFlowRatio);
  void resetCentralHeatingMaximumSystemAirFlowRatio();
  void autosizeCentralHeatingMaximumSystemAirFlowRatio();

  bool setPreheatDesignTemperature(double preheatDesignTemperature);
  bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);
  bool setPrecoolDesignTemperature(double precoolDesignTemperature);
  bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);
  bool setCentralCoolingDesignSupplyAirTemperature(double centralCoolingDesignSupplyAirTemperature);
  bool setCentralHeatingDesignSupplyAirTemperature(double centralHeatingDesignSupplyAirTemperature);

  bool setSizingOption(const std::string& sizingOption);
  void resetSizingOption();

  bool setAllOutdoorAirinCooling(bool allOutdoorAirinCooling);
  void resetAllOutdoorAirinCooling();

  bool setAllOutdoorAirinHeating(bool allOutdoorAirinHeating);
  void resetAllOutdoorAirinHeating();

  bool setCentralCoolingDesignSupplyAirHumidityRatio(double centralCoolingDesignSupplyAirHumidityRatio);
  void resetCentralCoolingDesignSupplyAirHumidityRatio();

  bool setCentralHeatingDesignSupplyAirHumidityRatio(double centralHeatingDesignSupplyAirHumidityRatio);
  void resetCentralHeatingDesignSupplyAirHumidityRatio();

  bool setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod);
  void resetCoolingDesignAirFlowMethod();

  bool setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate);
  void resetCoolingDesignAirFlowRate();

  bool setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod);
  void resetHeatingDesignAirFlowMethod();

  bool setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate);
  void resetHeatingDesignAirFlowRate();

  bool setSystemOutdoorAirMethod(const std::string& systemOutdoorAirMethod);
  void resetSystemOutdoorAirMethod();

  bool setZoneMaximumOutdoorAirFraction(double zoneMaximumOutdoorAirFraction);
  bool setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea);
  bool setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate);
  bool setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity);
  bool setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea);
  bool setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(double heatingFractionofAutosizedHeatingSupplyAirFlowRate);
  bool setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(double heatingFractionofAutosizedCoolingSupplyAirFlowRate);
  bool setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity);

  bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
  bool setCoolingDesignCapacity(double coolingDesignCapacity);
  void autosizeCoolingDesignCapacity();
  bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
  bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

  bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
  bool setHeatingDesignCapacity(double heatingDesignCapacity);
  void autosizeHeatingDesignCapacity();
  bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
  bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

  bool setCentralCoolingCapacityControlMethod(const std::string& centralCoolingCapacityControlMethod);

  bool setOccupantDiversity(double occupantDiversity);
  void autosizeOccupantDiversity();

  bool setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod);
  bool setMaximumHeatingCapacityToCoolingCapacitySizingRatio(double maximumHeatingCapacityToCoolingCapacitySizingRatio);

 protected:
  using ImplType = detail::SizingSystem_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SizingSystem(std::shared_ptr<detail::SizingSystem_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
