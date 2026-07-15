/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDXMULTISPEED_HPP
#define EPMODEL_COILHEATINGDXMULTISPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilHeatingDXMultiSpeed_Impl;
  }

  class EPMODEL_API CoilHeatingDXMultiSpeed : public StraightComponent
  {
   public:
    explicit CoilHeatingDXMultiSpeed(const Model& model);

    virtual ~CoilHeatingDXMultiSpeed() override = default;
    CoilHeatingDXMultiSpeed(const CoilHeatingDXMultiSpeed& other) = default;
    CoilHeatingDXMultiSpeed(CoilHeatingDXMultiSpeed&& other) = default;
    CoilHeatingDXMultiSpeed& operator=(const CoilHeatingDXMultiSpeed&) = default;
    CoilHeatingDXMultiSpeed& operator=(CoilHeatingDXMultiSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> defrostControlValues();
    static std::vector<std::string> fuelTypeValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical scalar heating DX surface plus the current epmodel optional schedule / curve relationship slice and
    //   supply-side air-loop insertion path are present, while stage-data and broader node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingDXMultiSpeed.
    // - Implemented Parity: The speed-level heating-capacity, airflow, defrost, crankcase-heater, and fuel-type helpers preserve the canonical naming
    //   and autosize behavior; `availabilitySchedule`, `defrostEnergyInputRatioFunctionofTemperatureCurve`, and
    //   `crankcaseHeaterCapacityFunctionofTemperatureCurve` preserve the bounded relationship slice; `addToNode` preserves the current epmodel
    //   supply-side air-loop insertion path.
    // - Documented Delta: Stage data and broader node-link helpers from canonical `openstudio::model::CoilHeatingDXMultiSpeed` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars and the bounded relationship slice map directly to EnergyPlus `Coil:Heating:DX:MultiSpeed` fields.
    // - Evidence: `src/model/CoilHeatingDXMultiSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDXMultiSpeed.cpp`, and `src/epmodel/test/CoilHeatingDXMultiSpeed_GTest.cpp`.
    // - Remaining Parity Work: Add stage-data and broader topology helpers without changing the preserved scalar signatures.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;
    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve);
    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;
    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve);
    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    boost::optional<double> outdoorDryBulbTemperaturetoTurnOnCompressor() const;
    bool setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor);
    void resetOutdoorDryBulbTemperaturetoTurnOnCompressor();

    double crankcaseHeaterCapacity() const;
    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);

    double maximumOutdoorDryBulbTemperatureforDefrostOperation() const;
    bool setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation);

    std::string defrostStrategy() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);

    std::string defrostControl() const;
    bool setDefrostControl(const std::string& defrostControl);

    double defrostTimePeriodFraction() const;
    bool setDefrostTimePeriodFraction(double defrostTimePeriodFraction);

    boost::optional<double> resistiveDefrostHeaterCapacity() const;
    bool isResistiveDefrostHeaterCapacityAutosized() const;
    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);
    void autosizeResistiveDefrostHeaterCapacity();

    bool applyPartLoadFractiontoSpeedsGreaterthan1() const;
    bool setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1);

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);

    int regionnumberforCalculatingHSPF() const;
    bool setRegionnumberforCalculatingHSPF(int regionnumberforCalculatingHSPF);

   protected:
    using ImplType = detail::CoilHeatingDXMultiSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDXMultiSpeed(std::shared_ptr<detail::CoilHeatingDXMultiSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
