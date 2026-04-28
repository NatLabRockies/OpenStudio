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
  class ModelObject;
  class Schedule;

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
    // - Status: Partial Parity. The canonical scalar desuperheater surface plus optional availability / heating-source relationships and the current
    //   epmodel supply-side air-loop insertion path are present, while OA insertion and AFN helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilHeatingDesuperheater.
    // - Implemented Parity: `heatReclaimRecoveryEfficiency`, `parasiticElectricLoad`, and `onCycleParasiticElectricLoad` preserve the canonical
    //   scalar API, including the required-field no-op resets; `availabilitySchedule` and `heatingSource` preserve the bounded relationship slice;
    //   `addToNode` preserves the current epmodel supply-side air-loop insertion path.
    // - Documented Delta: OA insertion and AFN helpers from canonical `openstudio::model::CoilHeatingDesuperheater` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars and relationships map directly to EnergyPlus `Coil:Heating:Desuperheater` fields.
    // - Evidence: `src/model/CoilHeatingDesuperheater.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingDesuperheater.cpp`, and `src/epmodel/test/CoilHeatingDesuperheater_GTest.cpp`.
    // - Remaining Parity Work: Add AFN helpers without changing the preserved scalar signatures.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<ModelObject> heatingSource() const;
    bool setHeatingSource(const ModelObject& modelObject);
    void resetHeatingSource();

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
