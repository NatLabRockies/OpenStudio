/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXSINGLESPEED_HPP
#define EPMODEL_COILHEATINGDXSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class CoilHeatingDXSingleSpeed_Impl;
  }

  class EPMODEL_API CoilHeatingDXSingleSpeed : public StraightComponent
  {
   public:
    explicit CoilHeatingDXSingleSpeed(const Model& model);

    virtual ~CoilHeatingDXSingleSpeed() override = default;
    CoilHeatingDXSingleSpeed(const CoilHeatingDXSingleSpeed& other) = default;
    CoilHeatingDXSingleSpeed(CoilHeatingDXSingleSpeed&& other) = default;
    CoilHeatingDXSingleSpeed& operator=(const CoilHeatingDXSingleSpeed&) = default;
    CoilHeatingDXSingleSpeed& operator=(CoilHeatingDXSingleSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validDefrostStrategyValues();
    static std::vector<std::string> validDefrostControlValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical scalar heating DX surface is largely present, while schedule, curve, and node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingDXSingleSpeed.
    // - Implemented Parity: The heating-capacity, COP, fan-power, defrost, and crankcase-heater helpers preserve the canonical naming, including the 2017/2023 fan-power split.
    // - Documented Delta: Availability schedule, curves, and node-link helpers from canonical `openstudio::model::CoilHeatingDXSingleSpeed` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Heating:DX:SingleSpeed` fields.
    // - Evidence: `src/model/CoilHeatingDXSingleSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXSingleSpeed.cpp`, and `src/epmodel/test/CoilHeatingDXSingleSpeed_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and relationship helpers without changing the preserved scalar signatures.

    boost::optional<double> ratedTotalHeatingCapacity() const;
    bool isRatedTotalHeatingCapacityAutosized() const;
    bool setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity);
    void autosizeRatedTotalHeatingCapacity();

    double ratedCOP() const;
    bool setRatedCOP(double ratedCOP);

    boost::optional<double> ratedAirFlowRate() const;
    bool isRatedAirFlowRateAutosized() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    void autosizeRatedAirFlowRate();

    double ratedSupplyFanPowerPerVolumeFlowRate() const;
    double ratedSupplyFanPowerPerVolumeFlowRate2017() const;
    double ratedSupplyFanPowerPerVolumeFlowRate2023() const;
    bool setRatedSupplyFanPowerPerVolumeFlowRate(double ratedSupplyFanPowerPerVolumeFlowRate);
    bool setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017);
    bool setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023);

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);
    void resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();

    double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);
    void resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();

    double crankcaseHeaterCapacity() const;
    bool isCrankcaseHeaterCapacityDefaulted() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);
    void resetCrankcaseHeaterCapacity();

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();

    std::string defrostStrategy() const;
    bool isDefrostStrategyDefaulted() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);
    void resetDefrostStrategy();

    std::string defrostControl() const;
    bool isDefrostControlDefaulted() const;
    bool setDefrostControl(const std::string& defrostControl);
    void resetDefrostControl();

    double defrostTimePeriodFraction() const;
    bool isDefrostTimePeriodFractionDefaulted() const;
    bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);
    void resetDefrostTimePeriodFraction();

    boost::optional<double> resistiveDefrostHeaterCapacity() const;
    bool isResistiveDefrostHeaterCapacityDefaulted() const;
    bool isResistiveDefrostHeaterCapacityAutosized() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    void resetResistiveDefrostHeaterCapacity();
    void autosizeResistiveDefrostHeaterCapacity();

   protected:
    using ImplType = detail::CoilHeatingDXSingleSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXSingleSpeed(std::shared_ptr<detail::CoilHeatingDXSingleSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
