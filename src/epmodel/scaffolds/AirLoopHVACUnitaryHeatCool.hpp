/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACUnitaryHeatCool_Impl;
  }

  class EPMODEL_API AirLoopHVACUnitaryHeatCool : public ModelObject
  {
   public:
    explicit AirLoopHVACUnitaryHeatCool(const Model& model);

    virtual ~AirLoopHVACUnitaryHeatCool() override = default;
    AirLoopHVACUnitaryHeatCool(const AirLoopHVACUnitaryHeatCool& other) = default;
    AirLoopHVACUnitaryHeatCool(AirLoopHVACUnitaryHeatCool&& other) = default;
    AirLoopHVACUnitaryHeatCool& operator=(const AirLoopHVACUnitaryHeatCool&) = default;
    AirLoopHVACUnitaryHeatCool& operator=(AirLoopHVACUnitaryHeatCool&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanObjectTypeValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> heatingCoilObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> reheatCoilObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to AirLoopHVAC:UnitaryHeatCool numeric/choice fields.
    // - Field Mapping: Availability schedule, unitary system inlet/outlet nodes, fan operating mode schedule, controlling zone, and *Name linkage fields remain excluded as relationship fields.
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
    using ImplType = detail::AirLoopHVACUnitaryHeatCool_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitaryHeatCool(std::shared_ptr<detail::AirLoopHVACUnitaryHeatCool_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
