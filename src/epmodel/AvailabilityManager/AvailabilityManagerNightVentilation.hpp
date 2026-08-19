/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTVENTILATION_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerNightVentilation_Impl;
  }

  /** \brief Controls night ventilation using outdoor temperature and flow-fraction limits.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagernightventilation,AvailabilityManager:NightVentilation}
   *
   * \par Important behavior
   * A newly constructed manager initializes the ventilation temperature
   * difference to 2.0, the low limit to 15.0, and the night-venting flow
   * fraction to 0.333.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerNightVentilation</code>.
   *
   * - <b>Not yet available:</b> <code>loop()</code>, the applicability and
   *   ventilation-temperature schedule methods, and the control-zone methods:
   *   <code>applicabilitySchedule()</code>,
   *   <code>setApplicabilitySchedule(...)</code>,
   *   <code>ventilationTemperatureSchedule()</code>,
   *   <code>setVentilationTemperatureSchedule(...)</code>,
   *   <code>resetVentilationTemperatureSchedule()</code>,
   *   <code>controlZone()</code>, <code>setControlZone(...)</code>, and
   *   <code>resetControlZone()</code>.
   *
   * \par Known limitations
   * The EPModel wrapper currently exposes scalar fields only. It cannot be
   * passed to typed loop-assignment APIs or fully configured through typed
   * schedule and control-zone relationships.
   */
  class EPMODEL_API AvailabilityManagerNightVentilation : public ModelObject
  {
   public:
    explicit AvailabilityManagerNightVentilation(const Model& model);

    virtual ~AvailabilityManagerNightVentilation() override = default;
    AvailabilityManagerNightVentilation(const AvailabilityManagerNightVentilation& other) = default;
    AvailabilityManagerNightVentilation(AvailabilityManagerNightVentilation&& other) = default;
    AvailabilityManagerNightVentilation& operator=(const AvailabilityManagerNightVentilation&) = default;
    AvailabilityManagerNightVentilation& operator=(AvailabilityManagerNightVentilation&&) = default;

    static IddObjectType iddObjectType();

    /** ventilationTemperatureDifference */
    double ventilationTemperatureDifference() const;
    bool setVentilationTemperatureDifference(double ventilationTemperatureDifference);

    /** ventilationTemperatureLowLimit */
    double ventilationTemperatureLowLimit() const;
    bool setVentilationTemperatureLowLimit(double ventilationTemperatureLowLimit);

    /** nightVentingFlowFraction */
    double nightVentingFlowFraction() const;
    bool setNightVentingFlowFraction(double nightVentingFlowFraction);

   protected:
    using ImplType = detail::AvailabilityManagerNightVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerNightVentilation(std::shared_ptr<detail::AvailabilityManagerNightVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
