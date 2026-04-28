/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACVENTILATEDSLAB_IMPL_HPP
#define EPMODEL_ZONEHVACVENTILATEDSLAB_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACVentilatedSlab_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACVentilatedSlab_Impl() override = default;

      boost::optional<double> maximumAirFlowRate() const;
      bool isMaximumAirFlowRateAutosized() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);
      void autosizeMaximumAirFlowRate();

      boost::optional<double> minimumOutdoorAirFlowRate() const;
      bool isMinimumOutdoorAirFlowRateAutosized() const;
      bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
      void autosizeMinimumOutdoorAirFlowRate();

      boost::optional<double> maximumOutdoorAirFlowRate() const;
      bool isMaximumOutdoorAirFlowRateAutosized() const;
      bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
      void autosizeMaximumOutdoorAirFlowRate();

      std::string outdoorAirControlType() const;
      bool setOutdoorAirControlType(const std::string& outdoorAirControlType);

      std::string systemConfigurationType() const;
      bool isSystemConfigurationTypeDefaulted() const;
      bool setSystemConfigurationType(const std::string& systemConfigurationType);
      void resetSystemConfigurationType();

      boost::optional<double> hollowCoreInsideDiameter() const;
      bool isHollowCoreInsideDiameterDefaulted() const;
      bool setHollowCoreInsideDiameter(double hollowCoreInsideDiameter);
      void resetHollowCoreInsideDiameter();

      boost::optional<double> hollowCoreLength() const;
      bool setHollowCoreLength(double hollowCoreLength);
      void resetHollowCoreLength();

      std::string temperatureControlType() const;
      bool isTemperatureControlTypeDefaulted() const;
      bool setTemperatureControlType(const std::string& temperatureControlType);
      void resetTemperatureControlType();

      std::string coilOptionType() const;
      bool setCoilOptionType(const std::string& coilOptionType);

      boost::optional<std::string> heatingCoilObjectType() const;
      bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);
      void resetHeatingCoilObjectType();

      boost::optional<std::string> coolingCoilObjectType() const;
      bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);
      void resetCoolingCoilObjectType();

      std::vector<std::string> outdoorAirControlTypeValues() const;
      std::vector<std::string> systemConfigurationTypeValues() const;
      std::vector<std::string> temperatureControlTypeValues() const;
      std::vector<std::string> coilOptionTypeValues() const;
      std::vector<std::string> heatingCoilObjectTypeValues() const;
      std::vector<std::string> coolingCoilObjectTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
