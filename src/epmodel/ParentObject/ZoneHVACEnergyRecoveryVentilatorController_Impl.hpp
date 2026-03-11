/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACENERGYRECOVERYVENTILATORCONTROLLER_IMPL_HPP
#define EPMODEL_ZONEHVACENERGYRECOVERYVENTILATORCONTROLLER_IMPL_HPP

#include "ParentObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACEnergyRecoveryVentilatorController_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~ZoneHVACEnergyRecoveryVentilatorController_Impl() override = default;

      boost::optional<double> temperatureHighLimit() const;
      bool setTemperatureHighLimit(double temperatureHighLimit);
      void resetTemperatureHighLimit();

      boost::optional<double> temperatureLowLimit() const;
      bool setTemperatureLowLimit(double temperatureLowLimit);
      void resetTemperatureLowLimit();

      boost::optional<double> enthalpyHighLimit() const;
      bool setEnthalpyHighLimit(double enthalpyHighLimit);
      void resetEnthalpyHighLimit();

      boost::optional<double> dewpointTemperatureLimit() const;
      bool setDewpointTemperatureLimit(double dewpointTemperatureLimit);
      void resetDewpointTemperatureLimit();

      std::string exhaustAirTemperatureLimit() const;
      bool setExhaustAirTemperatureLimit(const std::string& value);

      std::string exhaustAirEnthalpyLimit() const;
      bool setExhaustAirEnthalpyLimit(const std::string& value);

      bool highHumidityControlFlag() const;
      bool setHighHumidityControlFlag(bool highHumidityControlFlag);

      double highHumidityOutdoorAirFlowRatio() const;
      bool setHighHumidityOutdoorAirFlowRatio(double highHumidityOutdoorAirFlowRatio);

      bool controlHighIndoorHumidityBasedOnOutdoorHumidityRatio() const;
      bool setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(bool value);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
