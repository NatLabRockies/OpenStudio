/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNOFF_HPP
#define EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNOFF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerHighTemperatureTurnOff_Impl;
  }

  /** \brief Turns availability off when a sensor temperature exceeds a limit.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerhightemperatureturnoff,AvailabilityManager:HighTemperatureTurnOff}
   *
   * \par Important behavior
   * A newly constructed manager initializes its temperature limit to 30.0.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerHighTemperatureTurnOff</code>.
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
  class EPMODEL_API AvailabilityManagerHighTemperatureTurnOff : public ModelObject
  {
   public:
    explicit AvailabilityManagerHighTemperatureTurnOff(const Model& model);

    virtual ~AvailabilityManagerHighTemperatureTurnOff() override = default;
    AvailabilityManagerHighTemperatureTurnOff(const AvailabilityManagerHighTemperatureTurnOff& other) = default;
    AvailabilityManagerHighTemperatureTurnOff(AvailabilityManagerHighTemperatureTurnOff&& other) = default;
    AvailabilityManagerHighTemperatureTurnOff& operator=(const AvailabilityManagerHighTemperatureTurnOff&) = default;
    AvailabilityManagerHighTemperatureTurnOff& operator=(AvailabilityManagerHighTemperatureTurnOff&&) = default;

    static IddObjectType iddObjectType();

    double temperature() const;
    bool setTemperature(double temperature);

   protected:
    using ImplType = detail::AvailabilityManagerHighTemperatureTurnOff_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerHighTemperatureTurnOff(std::shared_ptr<detail::AvailabilityManagerHighTemperatureTurnOff_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
