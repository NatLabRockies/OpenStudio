/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANSYSTEMMODEL_HPP
#define EPMODEL_FANSYSTEMMODEL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;
  class ThermalZone;

  namespace detail {
    class FanSystemModel_Impl;
  }

/** \brief One speed entry for a system-model fan.
 *
 * \par EnergyPlus object
 * No standalone EnergyPlus object. Each instance exposes one extensible speed
 * row of its parent \epobject{group-fans.html#fansystemmodel,Fan:SystemModel}: Speed Flow Fraction 1 and, when
 * present, Speed Electric Power Fraction 1.
 *
 * \par Important behavior
 * The flow and optional electric-power fractions are value objects used by FanSystemModel speed extensibles.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::FanSystemModelSpeed</code>.
 *
 * \par Known limitations
 * The value is an immutable, detached entry. Use
 * <code>FanSystemModel::addSpeed(...)</code> or
 * <code>FanSystemModel::setSpeeds(...)</code> to store it on a fan.
 */
  class EPMODEL_API FanSystemModelSpeed
  {
   public:
    explicit FanSystemModelSpeed(double flowFraction);
    FanSystemModelSpeed(double flowFraction, double electricPowerFraction);

    double flowFraction() const;
    boost::optional<double> electricPowerFraction() const;

    bool operator<(const FanSystemModelSpeed& other) const;

   private:
    double m_flowFraction;
    boost::optional<double> m_electricPowerFraction;
  };

  EPMODEL_API std::ostream& operator<<(std::ostream& out, const FanSystemModelSpeed& speed);

/** \brief A fan using the EnergyPlus system-model representation.
 *
 * \par EnergyPlus object
 * \epobject{group-fans.html#fansystemmodel,Fan:SystemModel}
 *
 * \par Important behavior
 * Availability, electric-power curve, motor-loss zone, and speed data are represented directly, with speed data stored in Fan:SystemModel extensible groups.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::FanSystemModel</code>.
 *
 * \par Known limitations
 * AirflowNetwork helpers are not available.
 */
  class EPMODEL_API FanSystemModel : public StraightComponent
  {
   public:
    explicit FanSystemModel(const Model& model);

    virtual ~FanSystemModel() override = default;
    FanSystemModel(const FanSystemModel& other) = default;
    FanSystemModel(FanSystemModel&& other) = default;
    FanSystemModel& operator=(const FanSystemModel&) = default;
    FanSystemModel& operator=(FanSystemModel&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> speedControlMethodValues();
    static std::vector<std::string> designPowerSizingMethodValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> designMaximumAirFlowRate() const;
    bool isDesignMaximumAirFlowRateAutosized() const;
    bool setDesignMaximumAirFlowRate(double designMaximumAirFlowRate);
    void autosizeDesignMaximumAirFlowRate();

    std::string speedControlMethod() const;
    bool setSpeedControlMethod(const std::string& speedControlMethod);

    double electricPowerMinimumFlowRateFraction() const;
    bool setElectricPowerMinimumFlowRateFraction(double electricPowerMinimumFlowRateFraction);

    double designPressureRise() const;
    bool setDesignPressureRise(double designPressureRise);

    double motorEfficiency() const;
    bool setMotorEfficiency(double motorEfficiency);

    double motorInAirStreamFraction() const;
    bool setMotorInAirStreamFraction(double motorInAirStreamFraction);

    boost::optional<double> designElectricPowerConsumption() const;
    bool isDesignElectricPowerConsumptionAutosized() const;
    bool setDesignElectricPowerConsumption(double designElectricPowerConsumption);
    void autosizeDesignElectricPowerConsumption();

    std::string designPowerSizingMethod() const;
    bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

    double electricPowerPerUnitFlowRate() const;
    bool setElectricPowerPerUnitFlowRate(double electricPowerPerUnitFlowRate);

    double electricPowerPerUnitFlowRatePerUnitPressure() const;
    bool setElectricPowerPerUnitFlowRatePerUnitPressure(double electricPowerPerUnitFlowRatePerUnitPressure);

    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    boost::optional<Curve> electricPowerFunctionofFlowFractionCurve() const;
    bool setElectricPowerFunctionofFlowFractionCurve(const Curve& curve);
    void resetElectricPowerFunctionofFlowFractionCurve();

    boost::optional<double> nightVentilationModePressureRise() const;
    bool setNightVentilationModePressureRise(double nightVentilationModePressureRise);
    void resetNightVentilationModePressureRise();

    boost::optional<double> nightVentilationModeFlowFraction() const;
    bool setNightVentilationModeFlowFraction(double nightVentilationModeFlowFraction);
    void resetNightVentilationModeFlowFraction();

    boost::optional<ThermalZone> motorLossZone() const;
    bool setMotorLossZone(const ThermalZone& thermalZone);
    void resetMotorLossZone();

    double motorLossRadiativeFraction() const;
    bool setMotorLossRadiativeFraction(double motorLossRadiativeFraction);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    unsigned numberofSpeeds() const;
    std::vector<FanSystemModelSpeed> speeds() const;
    boost::optional<unsigned> speedIndex(const FanSystemModelSpeed& speed) const;
    boost::optional<FanSystemModelSpeed> getSpeed(unsigned speedIndex) const;

    bool addSpeed(const FanSystemModelSpeed& speed);
    bool addSpeed(double flowFraction);
    bool addSpeed(double flowFraction, double electricPowerFraction);
    bool removeSpeed(unsigned speedIndex);
    void removeAllSpeeds();
    bool setSpeeds(const std::vector<FanSystemModelSpeed>& speeds);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::FanSystemModel_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanSystemModel(std::shared_ptr<detail::FanSystemModel_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
