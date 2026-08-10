/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERLOWTEMPERATURETURNON_IMPL_HPP

#include "AvailabilityManager_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Node;

  namespace detail {

    class EPMODEL_API AvailabilityManagerLowTemperatureTurnOn_Impl : public AvailabilityManager_Impl
    {
     public:
      using AvailabilityManager_Impl::AvailabilityManager_Impl;
      virtual ~AvailabilityManagerLowTemperatureTurnOn_Impl() override = default;

      boost::optional<openstudio::epmodel::Node> sensorNode() const;
      bool setSensorNode(const openstudio::epmodel::Node& node);
      void resetSensorNode();

      /** @name Temperature Accessors */
      //@{
      // Schema Alignment Notes:
      // - API: Keeps parity with openstudio::model scalar accessors for this field.
      // - Field Mapping: temperature ↔ AvailabilityManager:LowTemperatureTurnOn Temperature.
      double temperature() const;
      bool setTemperature(double temperature);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
