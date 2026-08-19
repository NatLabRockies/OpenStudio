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

  /** \brief Represents a water-heating desuperheater coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingdesuperheater,Coil:Heating:Desuperheater}.
   *
   * \par Important behavior
   * The availability schedule, heat-reclaim fields, and performance relationships map directly to the EnergyPlus object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingDesuperheater</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code>, parasitic-load fields, and default-state queries. <b>Not yet available:</b> the Model heat-rejection-target relationship and broader outdoor-air insertion conveniences.
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
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
