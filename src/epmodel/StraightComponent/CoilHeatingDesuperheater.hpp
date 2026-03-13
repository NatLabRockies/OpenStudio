/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDESUPERHEATER_HPP
#define EPMODEL_COILHEATINGDESUPERHEATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingDesuperheater_Impl;
  }

  class EPMODEL_API CoilHeatingDesuperheater : public StraightComponent
  {
   public:
    explicit CoilHeatingDesuperheater(const Model& model);

    virtual ~CoilHeatingDesuperheater() override = default;
    CoilHeatingDesuperheater(const CoilHeatingDesuperheater& other) = default;
    CoilHeatingDesuperheater(CoilHeatingDesuperheater&& other) = default;
    CoilHeatingDesuperheater& operator=(const CoilHeatingDesuperheater&) = default;
    CoilHeatingDesuperheater& operator=(CoilHeatingDesuperheater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::CoilHeatingDesuperheater scalar accessor names/signatures.
    // - Field Mapping: heatReclaimRecoveryEfficiency maps to E+ Coil:Heating:Desuperheater Heat Reclaim Recovery Efficiency.
    // - Field Mapping: onCycleParasiticElectricLoad and deprecated parasiticElectricLoad map to E+ On Cycle Parasitic Electric Load.
    // - API: resetHeatReclaimRecoveryEfficiency/resetOnCycleParasiticElectricLoad are preserved but no-op because those E+ fields are required.
    // - Field Mapping: Relationship-like fields (availability schedule, heating source, and node/target links) are excluded in this pass.
    // - ForwardTranslator evidence: ForwardTranslateCoilHeatingDesuperheater.cpp writes these scalar fields directly.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.

    double heatReclaimRecoveryEfficiency() const;
    bool isHeatReclaimRecoveryEfficiencyDefaulted() const;
    bool setHeatReclaimRecoveryEfficiency(double heatReclaimRecoveryEfficiency);
    void resetHeatReclaimRecoveryEfficiency();

    double parasiticElectricLoad() const;
    bool isParasiticElectricLoadDefaulted() const;
    bool setParasiticElectricLoad(double parasiticElectricLoad);
    void resetParasiticElectricLoad();

    double onCycleParasiticElectricLoad() const;
    bool isOnCycleParasiticElectricLoadDefaulted() const;
    bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
    void resetOnCycleParasiticElectricLoad();

   protected:
    using ImplType = detail::CoilHeatingDesuperheater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingDesuperheater(std::shared_ptr<detail::CoilHeatingDesuperheater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
