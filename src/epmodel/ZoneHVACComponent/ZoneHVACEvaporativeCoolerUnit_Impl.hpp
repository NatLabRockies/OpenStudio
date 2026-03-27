/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_IMPL_HPP
#define EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_IMPL_HPP

#include "ZoneHVACComponent_Impl.hpp"

#include <string>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACEvaporativeCoolerUnit_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACEvaporativeCoolerUnit_Impl() override = default;

      boost::optional<double> designSupplyAirFlowRate() const;
      bool isDesignSupplyAirFlowRateAutosized() const;
      bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
      void autosizeDesignSupplyAirFlowRate();

      std::string fanPlacement() const;
      bool setFanPlacement(const std::string& fanPlacement);

      std::string coolerUnitControlMethod() const;
      bool setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod);

      double throttlingRangeTemperatureDifference() const;
      bool setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference);

      double coolingLoadControlThresholdHeatTransferRate() const;
      bool setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate);

      double shutOffRelativeHumidity() const;
      bool setShutOffRelativeHumidity(double shutOffRelativeHumidity);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
