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

  /** \brief Represents a fuel-fired heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatinggas-000,Coil:Heating:Fuel}.
   *
   * \par Important behavior
   * The one-argument constructor uses an always-on availability schedule; fuel-coil fields remain directly editable.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingGas</code>; this is the Model
   * name for EnergyPlus's <code>Coil:Heating:Fuel</code> object. <b>Added:</b> EPModel exposes <code>addToNode()</code>
   * and parasitic electric/gas load fields. <b>Not yet available:</b> AirflowNetwork helpers.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilHeatingGas : public StraightComponent
  {
   public:
    explicit CoilHeatingGas(const Model& model, Schedule& schedule);
    explicit CoilHeatingGas(const Model& model);

    virtual ~CoilHeatingGas() override = default;
    CoilHeatingGas(const CoilHeatingGas& other) = default;
    CoilHeatingGas(CoilHeatingGas&& other) = default;
    CoilHeatingGas& operator=(const CoilHeatingGas&) = default;
    CoilHeatingGas& operator=(CoilHeatingGas&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;

    /** \deprecated */
    Schedule availableSchedule() const;

    bool setAvailabilitySchedule(Schedule& schedule);

    /** \deprecated */
    bool setAvailableSchedule(Schedule& schedule);

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
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
