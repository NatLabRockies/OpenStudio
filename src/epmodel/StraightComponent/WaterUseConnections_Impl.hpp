/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSECONNECTIONS_IMPL_HPP
#define EPMODEL_WATERUSECONNECTIONS_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WaterUseConnections_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~WaterUseConnections_Impl() override = default;

      std::vector<std::string> drainWaterHeatExchangerTypeValues() const;
      std::vector<std::string> drainWaterHeatExchangerDestinationValues() const;

      std::string drainWaterHeatExchangerType() const;
      bool setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType);

      std::string drainWaterHeatExchangerDestination() const;
      bool setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination);

      boost::optional<double> drainWaterHeatExchangerUFactorTimesArea() const;
      bool setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea);
      void resetDrainWaterHeatExchangerUFactorTimesArea();

      unsigned inletPort() const override;
      unsigned outletPort() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERUSECONNECTIONS_IMPL_HPP
