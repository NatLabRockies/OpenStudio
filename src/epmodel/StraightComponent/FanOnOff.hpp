/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANONOFF_HPP
#define EPMODEL_FANONOFF_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class FanOnOff_Impl;
  }

/** \brief An on/off fan.
 *
 * \par EnergyPlus object
 * \epobject{group-fans.html#fanonoff,Fan:OnOff}
 *
 * \par Important behavior
 * Availability and curve relationships are typed object links; contained-fan placement preserves the one-in/one-out path.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::FanOnOff</code>.
 *
 * \par Known limitations
 * AirflowNetwork helpers are not available.
 */
  class EPMODEL_API FanOnOff : public StraightComponent
  {
   public:
    explicit FanOnOff(const Model& model);
    explicit FanOnOff(const Model& model, Schedule& availabilitySchedule);
    explicit FanOnOff(const Model& model, Schedule& availabilitySchedule, Curve& fanPowerRatioFunctionofSpeedRatioCurve,
                      Curve& fanEfficiencyRatioFunctionofSpeedRatioCurve);

    virtual ~FanOnOff() override = default;
    FanOnOff(const FanOnOff& other) = default;
    FanOnOff(FanOnOff&& other) = default;
    FanOnOff& operator=(const FanOnOff&) = default;
    FanOnOff& operator=(FanOnOff&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    double fanTotalEfficiency() const;
    bool isFanTotalEfficiencyDefaulted() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);
    void resetFanTotalEfficiency();

    double fanEfficiency() const;
    bool isFanEfficiencyDefaulted() const;
    bool setFanEfficiency(double fanTotalEfficiency);
    void resetFanEfficiency();

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

    Curve fanPowerRatioFunctionofSpeedRatioCurve() const;
    bool setFanPowerRatioFunctionofSpeedRatioCurve(const Curve& curve);

    Curve fanEfficiencyRatioFunctionofSpeedRatioCurve() const;
    bool setFanEfficiencyRatioFunctionofSpeedRatioCurve(const Curve& curve);

   protected:
    using ImplType = detail::FanOnOff_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanOnOff(std::shared_ptr<detail::FanOnOff_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
