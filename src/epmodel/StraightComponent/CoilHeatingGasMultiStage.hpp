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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::CoilHeatingGasMultiStage scalar-accessor names/signatures.
    // - Field Mapping: offCycleParasiticGasLoad/parasiticGasLoad map to E+ Coil:Heating:Gas:MultiStage Off-Cycle Parasitic Gas Load.
    // - Field Mapping: numberOfStages maps to E+ Coil:Heating:Gas:MultiStage Number of Stages.
    // - Field Mapping: relationship/extensible fields (availability schedule, node links, curve link, stage data) are excluded.
    // - ForwardTranslator evidence: ForwardTranslateCoilHeatingGasMultiStage.cpp writes OffCycleParasiticGasLoad and NumberofStages directly.
    // - TODO(parity): Add excluded relationship/stage APIs later without changing preserved scalar signatures.
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
