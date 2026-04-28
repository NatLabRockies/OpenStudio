/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGELECTRICMULTISTAGE_HPP
#define EPMODEL_COILHEATINGELECTRICMULTISTAGE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;

namespace detail {
class CoilHeatingElectricMultiStage_Impl;
}

class EPMODEL_API CoilHeatingElectricMultiStage : public StraightComponent
{
 public:
  explicit CoilHeatingElectricMultiStage(const Model& model);

  virtual ~CoilHeatingElectricMultiStage() override = default;
  CoilHeatingElectricMultiStage(const CoilHeatingElectricMultiStage& other) = default;
  CoilHeatingElectricMultiStage(CoilHeatingElectricMultiStage&& other) = default;
  CoilHeatingElectricMultiStage& operator=(const CoilHeatingElectricMultiStage&) = default;
  CoilHeatingElectricMultiStage& operator=(CoilHeatingElectricMultiStage&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Partial Parity. The bounded availability-schedule surface is present, but the canonical stage-data family remains model-owned.
  // - Canonical Counterpart: openstudio::model::CoilHeatingElectricMultiStage.
  // - Implemented Parity: `availabilitySchedule` preserves the bounded canonical relationship slice for this campaign; the current implementation keeps
  //   `numberOfStages` as a scalar field mirror because epmodel still lacks the canonical stage-data family and owning extensible-list behavior.
  // - Documented Delta: Stage-data ownership and extensible stage-list APIs from canonical `openstudio::model::CoilHeatingElectricMultiStage` are not
  //   exposed yet, and standalone `addToNode(...)` remains intentionally rejected to match the canonical wrapper.
  // - Field/Storage Mapping: The preserved relationship and scalar APIs map directly to EnergyPlus `Coil:Heating:Electric:MultiStage` fields.
  // - Evidence: `src/model/CoilHeatingElectricMultiStage.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingElectricMultiStage.cpp`, and `src/epmodel/test/CoilHeatingElectricMultiStage_GTest.cpp`.
  // - Remaining Parity Work: Add the canonical stage-data family and owning extensible-list behavior without changing the preserved scalar signatures.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  unsigned numberOfStages() const;

 protected:
  using ImplType = detail::CoilHeatingElectricMultiStage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingElectricMultiStage(std::shared_ptr<detail::CoilHeatingElectricMultiStage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
