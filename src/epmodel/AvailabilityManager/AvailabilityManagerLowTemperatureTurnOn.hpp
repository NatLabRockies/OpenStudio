/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_HPP
#define EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_HPP

#include "EPModelAPI.hpp"
#include "AvailabilityManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class AvailabilityManagerLowTemperatureTurnOn_Impl;
  }

  /** \brief Turns availability on when a sensor temperature falls below a limit.
   *
   * \par EnergyPlus object
   * \epobject{group-system-availability-managers.html#availabilitymanagerlowtemperatureturnon,AvailabilityManager:LowTemperatureTurnOn}
   *
   * \par Important behavior
   * A newly constructed manager initializes its temperature limit to 30.0.
   * Its sensor node is a live relationship and can be reset without removing
   * the availability manager from its assigned loop.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManagerLowTemperatureTurnOn</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API AvailabilityManagerLowTemperatureTurnOn : public AvailabilityManager
  {
   public:
    explicit AvailabilityManagerLowTemperatureTurnOn(const Model& model);

    virtual ~AvailabilityManagerLowTemperatureTurnOn() override = default;
    AvailabilityManagerLowTemperatureTurnOn(const AvailabilityManagerLowTemperatureTurnOn& other) = default;
    AvailabilityManagerLowTemperatureTurnOn(AvailabilityManagerLowTemperatureTurnOn&& other) = default;
    AvailabilityManagerLowTemperatureTurnOn& operator=(const AvailabilityManagerLowTemperatureTurnOn&) = default;
    AvailabilityManagerLowTemperatureTurnOn& operator=(AvailabilityManagerLowTemperatureTurnOn&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<Node> sensorNode() const;
    bool setSensorNode(const Node& node);
    void resetSensorNode();

    /** @name Temperature field */
    //@{
    double temperature() const;
    bool setTemperature(double temperature);
    //@}

   protected:
    using ImplType = detail::AvailabilityManagerLowTemperatureTurnOn_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerLowTemperatureTurnOn(std::shared_ptr<detail::AvailabilityManagerLowTemperatureTurnOn_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
