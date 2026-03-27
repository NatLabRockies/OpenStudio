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
    // - Status: Scalar Parity. The canonical gas-coil scalar surface is largely present, while schedule, curve, and node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingGas.
    // - Implemented Parity: `fuelType`, burner efficiency, parasitic loads, and nominal-capacity helpers preserve the canonical naming and autosize behavior.
    // - Documented Delta: Availability schedule, curves, temperature-setpoint node, and other relationship helpers from canonical `openstudio::model::CoilHeatingGas` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Heating:Fuel` fields.
    // - Evidence: `src/model/CoilHeatingGas.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingGas.cpp`, and `src/epmodel/test/CoilHeatingGas_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, curve, and relationship helpers without changing the preserved scalar signatures.
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
