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
    // - Status: Partial Parity. The stage-count and parasitic-load surface is present, but stage-data and relationship helpers remain model-owned.
    // - Canonical Counterpart: openstudio::model::CoilHeatingGasMultiStage.
    // - Implemented Parity: `parasiticGasLoad`, `offCycleParasiticGasLoad`, and `numberOfStages` preserve the canonical scalar API.
    // - Documented Delta: Availability schedule, curve links, stage-data, and node-link helpers from canonical `openstudio::model::CoilHeatingGasMultiStage` are not exposed yet.
    // - Field/Storage Mapping: The preserved API maps directly to EnergyPlus `Coil:Heating:Gas:MultiStage` storage.
    // - Evidence: `src/model/CoilHeatingGasMultiStage.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingGasMultiStage.cpp`, and `src/epmodel/test/CoilHeatingGasMultiStage_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted stage-data and relationship helpers without changing the preserved scalar signatures.
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
