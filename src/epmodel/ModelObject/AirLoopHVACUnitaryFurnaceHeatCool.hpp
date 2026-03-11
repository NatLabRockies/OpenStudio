/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYFURNACEHEATCOOL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYFURNACEHEATCOOL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACUnitaryFurnaceHeatCool_Impl;
}

class EPMODEL_API AirLoopHVACUnitaryFurnaceHeatCool : public ModelObject
{
 public:
  explicit AirLoopHVACUnitaryFurnaceHeatCool(const Model& model);

  virtual ~AirLoopHVACUnitaryFurnaceHeatCool() override = default;
  AirLoopHVACUnitaryFurnaceHeatCool(const AirLoopHVACUnitaryFurnaceHeatCool& other) = default;
  AirLoopHVACUnitaryFurnaceHeatCool(AirLoopHVACUnitaryFurnaceHeatCool&& other) = default;
  AirLoopHVACUnitaryFurnaceHeatCool& operator=(const AirLoopHVACUnitaryFurnaceHeatCool&) = default;
  AirLoopHVACUnitaryFurnaceHeatCool& operator=(AirLoopHVACUnitaryFurnaceHeatCool&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> supplyFanObjectTypeValues();
  static std::vector<std::string> fanPlacementValues();
  static std::vector<std::string> heatingCoilObjectTypeValues();
  static std::vector<std::string> coolingCoilObjectTypeValues();
  static std::vector<std::string> dehumidificationControlTypeValues();
  static std::vector<std::string> reheatCoilObjectTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to AirLoopHVAC:Unitary:Furnace:HeatCool numeric/choice fields.
  // - Field Mapping: Availability schedule, inlet/outlet nodes, controlling zone, and *Name linkage fields remain excluded as relationship fields.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  boost::optional<double> maximumSupplyAirTemperature() const;
  bool isMaximumSupplyAirTemperatureDefaulted() const;
  bool isMaximumSupplyAirTemperatureAutosized() const;
  bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
  void resetMaximumSupplyAirTemperature();
  void autosizeMaximumSupplyAirTemperature();

  boost::optional<double> coolingSupplyAirFlowRate() const;
  bool isCoolingSupplyAirFlowRateAutosized() const;
  bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
  void autosizeCoolingSupplyAirFlowRate();

  boost::optional<double> heatingSupplyAirFlowRate() const;
  bool isHeatingSupplyAirFlowRateAutosized() const;
  bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
  void autosizeHeatingSupplyAirFlowRate();

  boost::optional<double> noLoadSupplyAirFlowRate() const;
  bool isNoLoadSupplyAirFlowRateAutosized() const;
  bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
  void resetNoLoadSupplyAirFlowRate();
  void autosizeNoLoadSupplyAirFlowRate();

  std::string supplyFanObjectType() const;
  bool setSupplyFanObjectType(const std::string& supplyFanObjectType);

  std::string fanPlacement() const;
  bool setFanPlacement(const std::string& fanPlacement);
  bool isFanPlacementDefaulted() const;
  void resetFanPlacement();

  std::string heatingCoilObjectType() const;
  bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

  std::string coolingCoilObjectType() const;
  bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

  std::string dehumidificationControlType() const;
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  bool isDehumidificationControlTypeDefaulted() const;
  void resetDehumidificationControlType();

  boost::optional<std::string> reheatCoilObjectType() const;
  bool setReheatCoilObjectType(const std::string& reheatCoilObjectType);
  void resetReheatCoilObjectType();

 protected:
  using ImplType = detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACUnitaryFurnaceHeatCool(std::shared_ptr<detail::AirLoopHVACUnitaryFurnaceHeatCool_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
