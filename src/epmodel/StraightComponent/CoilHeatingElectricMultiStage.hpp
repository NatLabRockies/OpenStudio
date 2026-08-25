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

  /** \brief Represents a multistage electric heating coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilheatingelectricmultistage,Coil:Heating:Electric:MultiStage}.
   *
   * \par Important behavior
   * The persisted scalar, schedule, and currently supported stage-control relationships use the EnergyPlus coil topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilHeatingElectricMultiStage</code>.
   * Not yet available: stage-data ownership and extensible stage-list APIs.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the listed API differences.
   */
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
