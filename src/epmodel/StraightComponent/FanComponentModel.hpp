/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCOMPONENTMODEL_HPP
#define EPMODEL_FANCOMPONENTMODEL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class FanComponentModel_Impl;
  }

  class EPMODEL_API FanComponentModel : public StraightComponent
  {
   public:
    explicit FanComponentModel(const Model& model);
    explicit FanComponentModel(const Model& model, const Curve& fanPressureRiseCurve, const Curve& ductStaticPressureResetCurve,
                               const Curve& normalizedFanStaticEfficiencyCurveNonStallRegion,
                               const Curve& normalizedFanStaticEfficiencyCurveStallRegion,
                               const Curve& normalizedDimensionlessAirflowCurveNonStallRegion,
                               const Curve& normalizedDimensionlessAirflowCurveStallRegion);

    virtual ~FanComponentModel() override = default;
    FanComponentModel(const FanComponentModel& other) = default;
    FanComponentModel(FanComponentModel&& other) = default;
    FanComponentModel& operator=(const FanComponentModel&) = default;
    FanComponentModel& operator=(FanComponentModel&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> vFDEfficiencyTypeValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Near Parity. The core fan-component scalar surface, required and optional curve relationships, constructor defaults, and node insertion are aligned.
    // - Canonical Counterpart: openstudio::model::FanComponentModel.
    // - Implemented Parity: The canonical constructors, required and optional curve relationships, `assignDefaultOptionalCurves()`, and the availability-schedule plus scalar sizing, pulley/belt, efficiency, VFD, and end-use-subcategory accessors preserve the main `openstudio::model::FanComponentModel` behavior.
    // - Documented Delta: Autosized convenience getters and airflow-network helpers from the canonical model remain absent.
    // - Field/Storage Mapping: The availability schedule and curve references are typed object relationships, while the scalar fields map directly to `Fan:ComponentModel` storage in EnergyPlus.
    // - Evidence: `src/model/FanComponentModel.hpp`, `src/model/FanComponentModel.cpp`, `src/model/test/FanComponentModel_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanComponentModel.cpp` anchor the canonical API and translation behavior.
    // - Remaining Parity Work: Add the remaining autosized convenience getters and any airflow-network helper surface if epmodel later grows the corresponding fan helper types.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> maximumFlowRate() const;
    bool isMaximumFlowRateAutosized() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void autosizeMaximumFlowRate();

    boost::optional<double> minimumFlowRate() const;
    bool isMinimumFlowRateAutosized() const;
    bool setMinimumFlowRate(double minimumFlowRate);
    void autosizeMinimumFlowRate();

    double fanSizingFactor() const;
    bool setFanSizingFactor(double fanSizingFactor);

    double fanWheelDiameter() const;
    bool setFanWheelDiameter(double fanWheelDiameter);

    double fanOutletArea() const;
    bool setFanOutletArea(double fanOutletArea);

    double maximumFanStaticEfficiency() const;
    bool setMaximumFanStaticEfficiency(double maximumFanStaticEfficiency);

    double eulerNumberatMaximumFanStaticEfficiency() const;
    bool setEulerNumberatMaximumFanStaticEfficiency(double eulerNumberatMaximumFanStaticEfficiency);

    double maximumDimensionlessFanAirflow() const;
    bool setMaximumDimensionlessFanAirflow(double maximumDimensionlessFanAirflow);

    boost::optional<double> motorFanPulleyRatio() const;
    bool isMotorFanPulleyRatioAutosized() const;
    bool setMotorFanPulleyRatio(double motorFanPulleyRatio);
    void autosizeMotorFanPulleyRatio();

    boost::optional<double> beltMaximumTorque() const;
    bool isBeltMaximumTorqueAutosized() const;
    bool setBeltMaximumTorque(double beltMaximumTorque);
    void autosizeBeltMaximumTorque();

    double beltSizingFactor() const;
    bool setBeltSizingFactor(double beltSizingFactor);

    double beltFractionalTorqueTransition() const;
    bool setBeltFractionalTorqueTransition(double beltFractionalTorqueTransition);

    double motorMaximumSpeed() const;
    bool setMotorMaximumSpeed(double motorMaximumSpeed);

    boost::optional<double> maximumMotorOutputPower() const;
    bool isMaximumMotorOutputPowerAutosized() const;
    bool setMaximumMotorOutputPower(double maximumMotorOutputPower);
    void autosizeMaximumMotorOutputPower();

    double motorSizingFactor() const;
    bool setMotorSizingFactor(double motorSizingFactor);

    double motorInAirstreamFraction() const;
    bool setMotorInAirstreamFraction(double motorInAirstreamFraction);

    std::string vFDEfficiencyType() const;
    bool setVFDEfficiencyType(const std::string& vFDEfficiencyType);

    boost::optional<double> maximumVFDOutputPower() const;
    bool isMaximumVFDOutputPowerAutosized() const;
    bool setMaximumVFDOutputPower(double maximumVFDOutputPower);
    void autosizeMaximumVFDOutputPower();

    double vFDSizingFactor() const;
    bool setVFDSizingFactor(double vFDSizingFactor);

    Curve fanPressureRiseCurve() const;
    bool setFanPressureRiseCurve(const Curve& bivariateFunctions);

    Curve ductStaticPressureResetCurve() const;
    bool setDuctStaticPressureResetCurve(const Curve& univariateFunctions);

    Curve normalizedFanStaticEfficiencyCurveNonStallRegion() const;
    bool setNormalizedFanStaticEfficiencyCurveNonStallRegion(const Curve& univariateFunctions);

    Curve normalizedFanStaticEfficiencyCurveStallRegion() const;
    bool setNormalizedFanStaticEfficiencyCurveStallRegion(const Curve& univariateFunctions);

    Curve normalizedDimensionlessAirflowCurveNonStallRegion() const;
    bool setNormalizedDimensionlessAirflowCurveNonStallRegion(const Curve& univariateFunctions);

    Curve normalizedDimensionlessAirflowCurveStallRegion() const;
    bool setNormalizedDimensionlessAirflowCurveStallRegion(const Curve& univariateFunctions);

    boost::optional<Curve> maximumBeltEfficiencyCurve() const;
    bool setMaximumBeltEfficiencyCurve(const Curve& univariateFunctions);
    void resetMaximumBeltEfficiencyCurve();

    boost::optional<Curve> normalizedBeltEfficiencyCurveRegion1() const;
    bool setNormalizedBeltEfficiencyCurveRegion1(const Curve& univariateFunctions);
    void resetNormalizedBeltEfficiencyCurveRegion1();

    boost::optional<Curve> normalizedBeltEfficiencyCurveRegion2() const;
    bool setNormalizedBeltEfficiencyCurveRegion2(const Curve& univariateFunctions);
    void resetNormalizedBeltEfficiencyCurveRegion2();

    boost::optional<Curve> normalizedBeltEfficiencyCurveRegion3() const;
    bool setNormalizedBeltEfficiencyCurveRegion3(const Curve& univariateFunctions);
    void resetNormalizedBeltEfficiencyCurveRegion3();

    boost::optional<Curve> maximumMotorEfficiencyCurve() const;
    bool setMaximumMotorEfficiencyCurve(const Curve& univariateFunctions);
    void resetMaximumMotorEfficiencyCurve();

    boost::optional<Curve> normalizedMotorEfficiencyCurve() const;
    bool setNormalizedMotorEfficiencyCurve(const Curve& univariateFunctions);
    void resetNormalizedMotorEfficiencyCurve();

    boost::optional<Curve> vFDEfficiencyCurve() const;
    bool setVFDEfficiencyCurve(const Curve& univariateFunctions);
    void resetVFDEfficiencyCurve();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    bool assignDefaultOptionalCurves();

   protected:
    using ImplType = detail::FanComponentModel_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanComponentModel(std::shared_ptr<detail::FanComponentModel_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
