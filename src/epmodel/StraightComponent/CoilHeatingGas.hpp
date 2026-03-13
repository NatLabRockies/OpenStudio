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
    // - API: Preserve openstudio::model::CoilHeatingGas scalar accessor names/signatures.
    // - Field Mapping: gasBurnerEfficiency maps to E+ Coil:Heating:Fuel Burner Efficiency.
    // - Field Mapping: onCycleParasiticElectricLoad/parasiticElectricLoad map to E+ On Cycle Parasitic Electric Load.
    // - Field Mapping: offCycleParasiticGasLoad/parasiticGasLoad map to E+ Off Cycle Parasitic Fuel Load.
    // - Field Mapping: nominalCapacity maps to E+ Nominal Capacity.
    // - Field Mapping: relationship-like fields (availability schedule, node links, temperature setpoint, and part-load curve) are excluded.
    // - ForwardTranslator evidence: ForwardTranslateCoilHeatingGas.cpp writes FuelType, BurnerEfficiency,
    //   NominalCapacity, OnCycleParasiticElectricLoad, and OffCycleParasiticFuelLoad directly.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
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
