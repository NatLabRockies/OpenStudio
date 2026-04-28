/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGGAS_HPP
#define EPMODEL_COILHEATINGGAS_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilHeatingGas_Impl;
  }

  class EPMODEL_API CoilHeatingGas : public StraightComponent
  {
   public:
    explicit CoilHeatingGas(const Model& model);

    virtual ~CoilHeatingGas() override = default;
    CoilHeatingGas(const CoilHeatingGas& other) = default;
    CoilHeatingGas(CoilHeatingGas&& other) = default;
    CoilHeatingGas& operator=(const CoilHeatingGas&) = default;
    CoilHeatingGas& operator=(CoilHeatingGas&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical gas-coil scalar surface plus the required availability-schedule and optional part-load-fraction-curve
    //   relationships are present, while broader AFN helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingGas.
    // - Implemented Parity: `fuelType`, burner efficiency, parasitic loads, and nominal-capacity helpers preserve the canonical naming and autosize
    //   behavior; `availabilitySchedule`, the optional `partLoadFractionCorrelationCurve`, and child traversal preserve the bounded relationship slice.
    // - Documented Delta: Other curve, node-link, and AFN helpers from canonical `openstudio::model::CoilHeatingGas` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars and relationships map directly to EnergyPlus `Coil:Heating:Fuel` fields.
    // - Evidence: `src/model/CoilHeatingGas.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingGas.cpp`, and `src/epmodel/test/CoilHeatingGas_GTest.cpp`.
    // - Remaining Parity Work: Add the remaining relationship and AFN helpers without changing the preserved scalar signatures.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<Curve> partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);
    void resetPartLoadFractionCorrelationCurve();

    static std::vector<std::string> validFuelTypeValues();

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);
    void resetFuelType();

    double gasBurnerEfficiency() const;
    bool setGasBurnerEfficiency(double value);

    double parasiticElectricLoad() const;
    bool setParasiticElectricLoad(double value);

    double onCycleParasiticElectricLoad() const;
    bool setOnCycleParasiticElectricLoad(double value);

    double parasiticGasLoad() const;
    bool setParasiticGasLoad(double value);

    double offCycleParasiticGasLoad() const;
    bool setOffCycleParasiticGasLoad(double value);

    boost::optional<double> nominalCapacity() const;
    boost::optional<double> autosizedNominalCapacity() const;
    bool isNominalCapacityAutosized() const;
    bool setNominalCapacity(double nominalCapacity);
    void resetNominalCapacity();
    void autosizeNominalCapacity();

   protected:
    using ImplType = detail::CoilHeatingGas_Impl;

    friend class Model;

    explicit CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
