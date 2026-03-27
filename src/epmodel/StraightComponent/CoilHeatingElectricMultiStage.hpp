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
  // - Status: Partial Parity. The stage-count surface is present, but the stage-data and relationship helpers remain model-owned.
  // - Canonical Counterpart: openstudio::model::CoilHeatingElectricMultiStage.
  // - Implemented Parity: `numberOfStages` preserves the canonical stage-count API.
  // - Documented Delta: Availability schedule, node links, and extensible stage-data APIs from canonical `openstudio::model::CoilHeatingElectricMultiStage` are not exposed yet.
  // - Field/Storage Mapping: The preserved API maps directly to EnergyPlus `Coil:Heating:Electric:MultiStage` stage-count storage.
  // - Evidence: `src/model/CoilHeatingElectricMultiStage.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingElectricMultiStage.cpp`, and `src/epmodel/test/CoilHeatingElectricMultiStage_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted stage-data and relationship helpers without changing the preserved scalar signatures.
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
