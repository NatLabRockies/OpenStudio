/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNON_HPP
#define EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNON_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerHighTemperatureTurnOn_Impl;
  }

  /** \brief Turns availability on when a sensor temperature exceeds a limit.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerhightemperatureturnon,AvailabilityManager:HighTemperatureTurnOn}
   *
   * \par Important behavior
   * A newly constructed manager initializes its temperature limit to 30.0.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerHighTemperatureTurnOn</code>.
   *
   * - <b>Not yet available:</b> <code>loop()</code>,
   *   <code>sensorNode()</code>, <code>setSensorNode(...)</code>, and
   *   <code>resetSensorNode()</code>.
   *
   * \par Known limitations
   * The EPModel wrapper currently exposes only the scalar temperature limit.
   * It cannot be passed to typed loop-assignment APIs until its sensor-node
   * relationship and availability-manager base interface are exposed.
   */
  class EPMODEL_API AvailabilityManagerHighTemperatureTurnOn : public ModelObject
  {
   public:
    explicit AvailabilityManagerHighTemperatureTurnOn(const Model& model);

    virtual ~AvailabilityManagerHighTemperatureTurnOn() override = default;
    AvailabilityManagerHighTemperatureTurnOn(const AvailabilityManagerHighTemperatureTurnOn& other) = default;
    AvailabilityManagerHighTemperatureTurnOn(AvailabilityManagerHighTemperatureTurnOn&& other) = default;
    AvailabilityManagerHighTemperatureTurnOn& operator=(const AvailabilityManagerHighTemperatureTurnOn&) = default;
    AvailabilityManagerHighTemperatureTurnOn& operator=(AvailabilityManagerHighTemperatureTurnOn&&) = default;

    static IddObjectType iddObjectType();

    /** @name Temperature Accessors */
    //@{
    double temperature() const;
    bool setTemperature(double temperature);
    //@}

   protected:
    using ImplType = detail::AvailabilityManagerHighTemperatureTurnOn_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerHighTemperatureTurnOn(std::shared_ptr<detail::AvailabilityManagerHighTemperatureTurnOn_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
