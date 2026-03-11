/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACWINDOWAIRCONDITIONER_IMPL_HPP
#define EPMODEL_ZONEHVACWINDOWAIRCONDITIONER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACWindowAirConditioner_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACWindowAirConditioner_Impl() override = default;

      boost::optional<double> maximumSupplyAirFlowRate() const;
      bool isMaximumSupplyAirFlowRateAutosized() const;
      bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
      void autosizeMaximumSupplyAirFlowRate();
      boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;

      boost::optional<double> maximumOutdoorAirFlowRate() const;
      bool isMaximumOutdoorAirFlowRateAutosized() const;
      bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
      void autosizeMaximumOutdoorAirFlowRate();
      boost::optional<double> autosizedMaximumOutdoorAirFlowRate() const;

      std::string outdoorAirMixerObjectType() const;
      bool setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType);

      std::string supplyAirFanObjectType() const;
      bool setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType);

      std::string coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

      std::string fanPlacement() const;
      bool setFanPlacement(const std::string& fanPlacement);

      std::vector<std::string> outdoorAirMixerObjectTypeValues() const;
      std::vector<std::string> supplyAirFanObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;
      std::vector<std::string> fanPlacementValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
