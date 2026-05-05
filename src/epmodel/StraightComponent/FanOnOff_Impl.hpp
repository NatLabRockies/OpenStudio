/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANONOFF_IMPL_HPP
#define EPMODEL_FANONOFF_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {
  class Node;
  class Schedule;
  class Curve;
  namespace detail {

    class EPMODEL_API FanOnOff_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~FanOnOff_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;
      openstudio::epmodel::Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);

      double fanTotalEfficiency() const;
      bool isFanTotalEfficiencyDefaulted() const;
      bool setFanTotalEfficiency(double fanTotalEfficiency);
      void resetFanTotalEfficiency();

      double pressureRise() const;
      bool setPressureRise(double pressureRise);

      boost::optional<double> maximumFlowRate() const;
      bool setMaximumFlowRate(double maximumFlowRate);
      void resetMaximumFlowRate();
      void autosizeMaximumFlowRate();
      bool isMaximumFlowRateAutosized() const;

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;
      bool setMotorEfficiency(double motorEfficiency);
      void resetMotorEfficiency();

      boost::optional<double> motorInAirstreamFraction() const;
      bool setMotorInAirstreamFraction(double motorInAirstreamFraction);
      void resetMotorInAirstreamFraction();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      openstudio::epmodel::Curve fanPowerRatioFunctionofSpeedRatioCurve() const;
      bool setFanPowerRatioFunctionofSpeedRatioCurve(const openstudio::epmodel::Curve& curve);

      openstudio::epmodel::Curve fanEfficiencyRatioFunctionofSpeedRatioCurve() const;
      bool setFanEfficiencyRatioFunctionofSpeedRatioCurve(const openstudio::epmodel::Curve& curve);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
