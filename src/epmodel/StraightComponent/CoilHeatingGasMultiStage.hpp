/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGGASMULTISTAGE_HPP
#define EPMODEL_COILHEATINGGASMULTISTAGE_HPP

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
    class CoilHeatingGasMultiStage_Impl;
  }

  /** \brief Represents a multistage gas heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatinggasmultistage,Coil:Heating:Gas:MultiStage}.
   *
   * \par Important behavior
   * The persisted scalar, schedule, and currently supported stage-control relationships use the EnergyPlus coil topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingGasMultiStage</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code> and parasitic gas-load controls. <b>Not yet available:</b> Model stage-data ownership and extensible stage-list methods.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
  class EPMODEL_API CoilHeatingGasMultiStage : public StraightComponent
  {
   public:
    explicit CoilHeatingGasMultiStage(const Model& model);

    virtual ~CoilHeatingGasMultiStage() override = default;
    CoilHeatingGasMultiStage(const CoilHeatingGasMultiStage& other) = default;
    CoilHeatingGasMultiStage(CoilHeatingGasMultiStage&& other) = default;
    CoilHeatingGasMultiStage& operator=(const CoilHeatingGasMultiStage&) = default;
    CoilHeatingGasMultiStage& operator=(CoilHeatingGasMultiStage&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<Curve> partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);
    void resetPartLoadFractionCorrelationCurve();

    boost::optional<double> parasiticGasLoad() const;
    bool setParasiticGasLoad(double parasiticGasLoad);
    void resetParasiticGasLoad();

    boost::optional<double> offCycleParasiticGasLoad() const;
    bool setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad);
    void resetOffCycleParasiticGasLoad();

    unsigned numberOfStages() const;

   protected:
    using ImplType = detail::CoilHeatingGasMultiStage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingGasMultiStage(std::shared_ptr<detail::CoilHeatingGasMultiStage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
