/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOWPERFORMANCEDATATYPE1_HPP
#define EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOWPERFORMANCEDATATYPE1_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

namespace openstudio {

namespace epmodel {

  namespace detail {

    class HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl;

  }  // namespace detail

  /** HeatExchangerDesiccantBalancedFlowPerformanceDataType1 is a ModelObject that wraps the EnergyPlus IDD object
   * 'HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1'. */
  class EPMODEL_API HeatExchangerDesiccantBalancedFlowPerformanceDataType1 : public ModelObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit HeatExchangerDesiccantBalancedFlowPerformanceDataType1(const Model& model);

    virtual ~HeatExchangerDesiccantBalancedFlowPerformanceDataType1() override = default;
    // Default the copy and move operators because the virtual dtor is explicit
    HeatExchangerDesiccantBalancedFlowPerformanceDataType1(const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& other) = default;
    HeatExchangerDesiccantBalancedFlowPerformanceDataType1(HeatExchangerDesiccantBalancedFlowPerformanceDataType1&& other) = default;
    HeatExchangerDesiccantBalancedFlowPerformanceDataType1& operator=(const HeatExchangerDesiccantBalancedFlowPerformanceDataType1&) = default;
    HeatExchangerDesiccantBalancedFlowPerformanceDataType1& operator=(HeatExchangerDesiccantBalancedFlowPerformanceDataType1&&) = default;

    //@}

    static IddObjectType iddObjectType();

    /** @name Field Accessors */
    //@{

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for this counterpart class.
    // - Field Mapping: Preserved scalar APIs map directly to matching E+ HeatExchanger:Desiccant:BalancedFlow:PerformanceDataType1 fields.
    // - ForwardTranslator evidence: ForwardTranslateHeatExchangerDesiccantBalancedFlowPerformanceDataType1 writes these scalar fields one-to-one.
    // - TODO(parity): Add non-scalar relationship APIs in a dedicated pass.

    // Nominal Air Flow Rate
    bool isNominalAirFlowRateAutosized() const;

    boost::optional<double> nominalAirFlowRate() const;

    void autosizeNominalAirFlowRate();

    bool setNominalAirFlowRate(double nominalAirFlowRate);

    // Nominal Air Face Velocity
    bool isNominalAirFaceVelocityAutosized() const;

    boost::optional<double> nominalAirFaceVelocity() const;

    void autosizeNominalAirFaceVelocity();

    bool setNominalAirFaceVelocity(double nominalAirFaceVelocity);

    // Nominal Electric Power
    double nominalElectricPower() const;

    bool setNominalElectricPower(double nominalElectricPower);

    // Temperature Equation Coefficients
    double temperatureEquationCoefficient1() const;

    bool setTemperatureEquationCoefficient1(double temperatureEquationCoefficient1);

    double temperatureEquationCoefficient2() const;

    bool setTemperatureEquationCoefficient2(double temperatureEquationCoefficient2);

    double temperatureEquationCoefficient3() const;

    bool setTemperatureEquationCoefficient3(double temperatureEquationCoefficient3);

    double temperatureEquationCoefficient4() const;

    bool setTemperatureEquationCoefficient4(double temperatureEquationCoefficient4);

    double temperatureEquationCoefficient5() const;

    bool setTemperatureEquationCoefficient5(double temperatureEquationCoefficient5);

    double temperatureEquationCoefficient6() const;

    bool setTemperatureEquationCoefficient6(double temperatureEquationCoefficient6);

    double temperatureEquationCoefficient7() const;

    bool setTemperatureEquationCoefficient7(double temperatureEquationCoefficient7);

    double temperatureEquationCoefficient8() const;

    bool setTemperatureEquationCoefficient8(double temperatureEquationCoefficient8);

    // Regeneration inlet air humidity ratio limits for temperature equation
    double minimumRegenerationInletAirHumidityRatioforTemperatureEquation() const;

    bool setMinimumRegenerationInletAirHumidityRatioforTemperatureEquation(double minimumRegenerationInletAirHumidityRatioforTemperatureEquation);

    double maximumRegenerationInletAirHumidityRatioforTemperatureEquation() const;

    bool setMaximumRegenerationInletAirHumidityRatioforTemperatureEquation(double maximumRegenerationInletAirHumidityRatioforTemperatureEquation);

    // Regeneration inlet air temperature limits for temperature equation
    double minimumRegenerationInletAirTemperatureforTemperatureEquation() const;

    bool setMinimumRegenerationInletAirTemperatureforTemperatureEquation(double minimumRegenerationInletAirTemperatureforTemperatureEquation);

    double maximumRegenerationInletAirTemperatureforTemperatureEquation() const;

    bool setMaximumRegenerationInletAirTemperatureforTemperatureEquation(double maximumRegenerationInletAirTemperatureforTemperatureEquation);

    // Process inlet air humidity ratio limits for temperature equation
    double minimumProcessInletAirHumidityRatioforTemperatureEquation() const;

    bool setMinimumProcessInletAirHumidityRatioforTemperatureEquation(double minimumProcessInletAirHumidityRatioforTemperatureEquation);

    double maximumProcessInletAirHumidityRatioforTemperatureEquation() const;

    bool setMaximumProcessInletAirHumidityRatioforTemperatureEquation(double maximumProcessInletAirHumidityRatioforTemperatureEquation);

    // Process inlet air temperature limits for temperature equation
    double minimumProcessInletAirTemperatureforTemperatureEquation() const;

    bool setMinimumProcessInletAirTemperatureforTemperatureEquation(double minimumProcessInletAirTemperatureforTemperatureEquation);

    double maximumProcessInletAirTemperatureforTemperatureEquation() const;

    bool setMaximumProcessInletAirTemperatureforTemperatureEquation(double maximumProcessInletAirTemperatureforTemperatureEquation);

    // Regeneration air velocity limits for temperature equation
    double minimumRegenerationAirVelocityforTemperatureEquation() const;

    bool setMinimumRegenerationAirVelocityforTemperatureEquation(double minimumRegenerationAirVelocityforTemperatureEquation);

    double maximumRegenerationAirVelocityforTemperatureEquation() const;

    bool setMaximumRegenerationAirVelocityforTemperatureEquation(double maximumRegenerationAirVelocityforTemperatureEquation);

    // Regeneration outlet air temperature limits for temperature equation
    double minimumRegenerationOutletAirTemperatureforTemperatureEquation() const;

    bool setMinimumRegenerationOutletAirTemperatureforTemperatureEquation(double minimumRegenerationOutletAirTemperatureforTemperatureEquation);

    double maximumRegenerationOutletAirTemperatureforTemperatureEquation() const;

    bool setMaximumRegenerationOutletAirTemperatureforTemperatureEquation(double maximumRegenerationOutletAirTemperatureforTemperatureEquation);

    // Regeneration inlet air relative humidity limits for temperature equation
    double minimumRegenerationInletAirRelativeHumidityforTemperatureEquation() const;

    bool
      setMinimumRegenerationInletAirRelativeHumidityforTemperatureEquation(double minimumRegenerationInletAirRelativeHumidityforTemperatureEquation);

    double maximumRegenerationInletAirRelativeHumidityforTemperatureEquation() const;

    bool
      setMaximumRegenerationInletAirRelativeHumidityforTemperatureEquation(double maximumRegenerationInletAirRelativeHumidityforTemperatureEquation);

    // Process inlet air relative humidity limits for temperature equation
    double minimumProcessInletAirRelativeHumidityforTemperatureEquation() const;

    bool setMinimumProcessInletAirRelativeHumidityforTemperatureEquation(double minimumProcessInletAirRelativeHumidityforTemperatureEquation);

    double maximumProcessInletAirRelativeHumidityforTemperatureEquation() const;

    bool setMaximumProcessInletAirRelativeHumidityforTemperatureEquation(double maximumProcessInletAirRelativeHumidityforTemperatureEquation);

    // Humidity ratio equation coefficients
    double humidityRatioEquationCoefficient1() const;

    bool setHumidityRatioEquationCoefficient1(double humidityRatioEquationCoefficient1);

    double humidityRatioEquationCoefficient2() const;

    bool setHumidityRatioEquationCoefficient2(double humidityRatioEquationCoefficient2);

    double humidityRatioEquationCoefficient3() const;

    bool setHumidityRatioEquationCoefficient3(double humidityRatioEquationCoefficient3);

    double humidityRatioEquationCoefficient4() const;

    bool setHumidityRatioEquationCoefficient4(double humidityRatioEquationCoefficient4);

    double humidityRatioEquationCoefficient5() const;

    bool setHumidityRatioEquationCoefficient5(double humidityRatioEquationCoefficient5);

    double humidityRatioEquationCoefficient6() const;

    bool setHumidityRatioEquationCoefficient6(double humidityRatioEquationCoefficient6);

    double humidityRatioEquationCoefficient7() const;

    bool setHumidityRatioEquationCoefficient7(double humidityRatioEquationCoefficient7);

    double humidityRatioEquationCoefficient8() const;

    bool setHumidityRatioEquationCoefficient8(double humidityRatioEquationCoefficient8);

    // Regeneration inlet air humidity ratio limits for humidity ratio equation
    double minimumRegenerationInletAirHumidityRatioforHumidityRatioEquation() const;

    bool setMinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation(double minimumRegenerationInletAirHumidityRatioforHumidityRatioEquation);

    double maximumRegenerationInletAirHumidityRatioforHumidityRatioEquation() const;

    bool setMaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation(double maximumRegenerationInletAirHumidityRatioforHumidityRatioEquation);

    // Regeneration inlet air temperature limits for humidity ratio equation
    double minimumRegenerationInletAirTemperatureforHumidityRatioEquation() const;

    bool setMinimumRegenerationInletAirTemperatureforHumidityRatioEquation(double minimumRegenerationInletAirTemperatureforHumidityRatioEquation);

    double maximumRegenerationInletAirTemperatureforHumidityRatioEquation() const;

    bool setMaximumRegenerationInletAirTemperatureforHumidityRatioEquation(double maximumRegenerationInletAirTemperatureforHumidityRatioEquation);

    // Process inlet air humidity ratio limits for humidity ratio equation
    double minimumProcessInletAirHumidityRatioforHumidityRatioEquation() const;

    bool setMinimumProcessInletAirHumidityRatioforHumidityRatioEquation(double minimumProcessInletAirHumidityRatioforHumidityRatioEquation);

    double maximumProcessInletAirHumidityRatioforHumidityRatioEquation() const;

    bool setMaximumProcessInletAirHumidityRatioforHumidityRatioEquation(double maximumProcessInletAirHumidityRatioforHumidityRatioEquation);

    // Process inlet air temperature limits for humidity ratio equation
    double minimumProcessInletAirTemperatureforHumidityRatioEquation() const;

    bool setMinimumProcessInletAirTemperatureforHumidityRatioEquation(double minimumProcessInletAirTemperatureforHumidityRatioEquation);

    double maximumProcessInletAirTemperatureforHumidityRatioEquation() const;

    bool setMaximumProcessInletAirTemperatureforHumidityRatioEquation(double maximumProcessInletAirTemperatureforHumidityRatioEquation);

    // Regeneration air velocity limits for humidity ratio equation
    double minimumRegenerationAirVelocityforHumidityRatioEquation() const;

    bool setMinimumRegenerationAirVelocityforHumidityRatioEquation(double minimumRegenerationAirVelocityforHumidityRatioEquation);

    double maximumRegenerationAirVelocityforHumidityRatioEquation() const;

    bool setMaximumRegenerationAirVelocityforHumidityRatioEquation(double maximumRegenerationAirVelocityforHumidityRatioEquation);

    // Regeneration outlet air humidity ratio limits for humidity ratio equation
    double minimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation() const;

    bool
      setMinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation(double minimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation);

    double maximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation() const;

    bool
      setMaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation(double maximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation);

    // Regeneration inlet air relative humidity limits for humidity ratio equation
    double minimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation() const;

    bool setMinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation(
      double minimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation);

    double maximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation() const;

    bool setMaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation(
      double maximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation);

    // Process inlet air relative humidity limits for humidity ratio equation
    double minimumProcessInletAirRelativeHumidityforHumidityRatioEquation() const;

    bool setMinimumProcessInletAirRelativeHumidityforHumidityRatioEquation(double minimumProcessInletAirRelativeHumidityforHumidityRatioEquation);

    double maximumProcessInletAirRelativeHumidityforHumidityRatioEquation() const;

    bool setMaximumProcessInletAirRelativeHumidityforHumidityRatioEquation(double maximumProcessInletAirRelativeHumidityforHumidityRatioEquation);

    //@}
    /** @name Other */
    //@{

    boost::optional<double> autosizedNominalAirFlowRate();

    boost::optional<double> autosizedNominalAirFaceVelocity();

    void autosize();

    void applySizingValues();

    //@}
   protected:
    /// @cond
    using ImplType = detail::HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl;

    explicit HeatExchangerDesiccantBalancedFlowPerformanceDataType1(
      std::shared_ptr<detail::HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl> impl);

    friend class detail::HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.epmodel.HeatExchangerDesiccantBalancedFlowPerformanceDataType1");
  };

  /** \relates HeatExchangerDesiccantBalancedFlowPerformanceDataType1*/
  using OptionalHeatExchangerDesiccantBalancedFlowPerformanceDataType1 = boost::optional<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>;

  /** \relates HeatExchangerDesiccantBalancedFlowPerformanceDataType1*/
  using HeatExchangerDesiccantBalancedFlowPerformanceDataType1Vector = std::vector<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOWPERFORMANCEDATATYPE1_HPP
