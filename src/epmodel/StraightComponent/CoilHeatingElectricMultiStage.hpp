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
  // - API: Preserve openstudio::model::CoilHeatingElectricMultiStage scalar-accessor naming where present.
  // - Field Mapping: numberOfStages() maps directly to E+ Coil:Heating:Electric:MultiStage Number of Stages.
  // - Field Mapping: relationship-like fields (availability schedule, node links) and extensible stage data are excluded.
  // - ForwardTranslator evidence: ForwardTranslateCoilHeatingElectricMultiStage.cpp writes NumberofStages from model stage count.
  // - TODO(parity): Add stage/relationship APIs later without changing preserved scalar signatures.
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
