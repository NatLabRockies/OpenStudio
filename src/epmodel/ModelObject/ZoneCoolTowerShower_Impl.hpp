/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONECOOLTOWER_SHOWER_IMPL_HPP
#define EPMODEL_ZONECOOLTOWER_SHOWER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneCoolTowerShower_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneCoolTowerShower_Impl() override = default;

      std::string flowControlType() const;
      bool setFlowControlType(const std::string& flowControlType);
      bool isFlowControlTypeDefaulted() const;
      void resetFlowControlType();

      double maximumWaterFlowRate() const;
      bool setMaximumWaterFlowRate(double maximumWaterFlowRate);

      double effectiveTowerHeight() const;
      bool setEffectiveTowerHeight(double effectiveTowerHeight);

      double airflowOutletArea() const;
      bool setAirflowOutletArea(double airflowOutletArea);

      double maximumAirFlowRate() const;
      bool setMaximumAirFlowRate(double maximumAirFlowRate);

      double minimumIndoorTemperature() const;
      bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

      boost::optional<double> fractionofWaterLoss() const;
      bool setFractionofWaterLoss(double fractionofWaterLoss);
      bool isFractionofWaterLossDefaulted() const;
      void resetFractionofWaterLoss();

      boost::optional<double> fractionofFlowSchedule() const;
      bool setFractionofFlowSchedule(double fractionofFlowSchedule);
      bool isFractionofFlowScheduleDefaulted() const;
      void resetFractionofFlowSchedule();

      double ratedPowerConsumption() const;
      bool setRatedPowerConsumption(double ratedPowerConsumption);

      std::vector<std::string> flowControlTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
