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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The bounded availability-schedule and optional part-load-fraction-curve relationships are present, but the canonical
    //   stage-data family remains model-owned.
    // - Canonical Counterpart: openstudio::model::CoilHeatingGasMultiStage.
    // - Implemented Parity: `availabilitySchedule` and the optional `partLoadFractionCorrelationCurve` preserve the bounded canonical relationship slice
    //   for this campaign; `parasiticGasLoad`, `offCycleParasiticGasLoad`, and `numberOfStages` preserve the current scalar field mirror.
    // - Documented Delta: Stage-data ownership and extensible stage-list APIs from canonical `openstudio::model::CoilHeatingGasMultiStage` are not
    //   exposed yet, and standalone `addToNode(...)` remains intentionally rejected to match the canonical wrapper.
    // - Field/Storage Mapping: The preserved relationship and scalar APIs map directly to EnergyPlus `Coil:Heating:Gas:MultiStage` storage.
    // - Evidence: `src/model/CoilHeatingGasMultiStage.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingGasMultiStage.cpp`, and `src/epmodel/test/CoilHeatingGasMultiStage_GTest.cpp`.
    // - Remaining Parity Work: Add the canonical stage-data family and owning extensible-list behavior without changing the preserved scalar signatures.
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
