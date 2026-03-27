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
    // - Status: Scalar Parity. The canonical desuperheater scalar surface is largely present, while schedule, heating-source, and node-link helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingDesuperheater.
    // - Implemented Parity: `heatReclaimRecoveryEfficiency`, `parasiticElectricLoad`, and `onCycleParasiticElectricLoad` preserve the canonical scalar API, including the required-field no-op resets.
    // - Documented Delta: Availability schedule, heating-source, and node-link helpers from canonical `openstudio::model::CoilHeatingDesuperheater` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Heating:Desuperheater` fields.
    // - Evidence: `src/model/CoilHeatingDesuperheater.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDesuperheater.cpp`, and `src/epmodel/test/CoilHeatingDesuperheater_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted schedule, heating-source, and relationship helpers without changing the preserved scalar signatures.

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
