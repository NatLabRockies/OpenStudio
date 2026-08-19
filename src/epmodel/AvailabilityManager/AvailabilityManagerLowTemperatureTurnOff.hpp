/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNOFF_HPP
#define EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNOFF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerLowTemperatureTurnOff_Impl;
  }

  /** \brief Turns availability off when a sensor temperature falls below a limit.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerlowtemperatureturnoff,AvailabilityManager:LowTemperatureTurnOff}
   *
   * \par Important behavior
   * A newly constructed manager initializes its temperature limit to 30.0.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerLowTemperatureTurnOff</code>.
   *
   * - <b>Not yet available:</b> <code>loop()</code>,
   *   <code>sensorNode()</code>, <code>setSensorNode(...)</code>,
   *   <code>resetSensorNode()</code>, <code>applicabilitySchedule()</code>,
   *   and <code>setApplicabilitySchedule(...)</code>.
   *
   * \par Known limitations
   * The EPModel wrapper currently exposes only the scalar temperature limit.
   * It cannot be passed to typed loop-assignment APIs until its sensor-node and
   * applicability-schedule relationships and availability-manager base
   * interface are exposed.
   */
  class EPMODEL_API AvailabilityManagerLowTemperatureTurnOff : public ModelObject
  {
   public:
    explicit AvailabilityManagerLowTemperatureTurnOff(const Model& model);

    virtual ~AvailabilityManagerLowTemperatureTurnOff() override = default;
    AvailabilityManagerLowTemperatureTurnOff(const AvailabilityManagerLowTemperatureTurnOff& other) = default;
    AvailabilityManagerLowTemperatureTurnOff(AvailabilityManagerLowTemperatureTurnOff&& other) = default;
    AvailabilityManagerLowTemperatureTurnOff& operator=(const AvailabilityManagerLowTemperatureTurnOff&) = default;
    AvailabilityManagerLowTemperatureTurnOff& operator=(AvailabilityManagerLowTemperatureTurnOff&&) = default;

    static IddObjectType iddObjectType();

    /** @name Temperature Accessors */
    //@{
    double temperature() const;
    bool setTemperature(double temperature);
    //@}

   protected:
    using ImplType = detail::AvailabilityManagerLowTemperatureTurnOff_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerLowTemperatureTurnOff(std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOff_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
