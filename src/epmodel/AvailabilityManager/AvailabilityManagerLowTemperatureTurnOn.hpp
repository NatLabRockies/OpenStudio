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

    // Schema Alignment Notes:
    // - API: Inherits AvailabilityManager so this object participates in loop assignment and live reverse discovery.
    // - Field Mapping: temperature maps to E+ AvailabilityManager:LowTemperatureTurnOn Temperature.
    // - Field Mapping: sensorNode maps to E+ AvailabilityManager:LowTemperatureTurnOn Sensor Node Name as a managed Node target.
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
