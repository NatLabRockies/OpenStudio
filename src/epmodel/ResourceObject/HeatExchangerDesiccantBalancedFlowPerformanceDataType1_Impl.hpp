/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOWPERFORMANCEDATATYPE1_IMPL_HPP
#define EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOWPERFORMANCEDATATYPE1_IMPL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    /** HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl is a ModelObject_Impl that is the implementation class for HeatExchangerDesiccantBalancedFlowPerformanceDataType1.*/
    class EPMODEL_API HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl : public ModelObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                                  bool keepHandle);

      HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl(const HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl& other,
                                                                  Model_Impl* model, bool keepHandle);

      virtual ~HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl() override = default;
      //@}
      /** @name Field Accessors */
      //@{

      bool isNominalAirFlowRateAutosized() const;

      boost::optional<double> nominalAirFlowRate() const;

      void autosizeNominalAirFlowRate();

      bool setNominalAirFlowRate(double nominalAirFlowRate);

      boost::optional<double> autosizedNominalAirFlowRate();

      bool isNominalAirFaceVelocityAutosized() const;

      boost::optional<double> nominalAirFaceVelocity() const;

      void autosizeNominalAirFaceVelocity();

      bool setNominalAirFaceVelocity(double nominalAirFaceVelocity);

      boost::optional<double> autosizedNominalAirFaceVelocity();

      double nominalElectricPower() const;

      bool setNominalElectricPower(double nominalElectricPower);

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

      double minimumRegenerationInletAirHumidityRatioforTemperatureEquation() const;

      bool setMinimumRegenerationInletAirHumidityRatioforTemperatureEquation(double minimumRegenerationInletAirHumidityRatioforTemperatureEquation);

      double maximumRegenerationInletAirHumidityRatioforTemperatureEquation() const;

      bool setMaximumRegenerationInletAirHumidityRatioforTemperatureEquation(double maximumRegenerationInletAirHumidityRatioforTemperatureEquation);

      double minimumRegenerationInletAirTemperatureforTemperatureEquation() const;

      bool setMinimumRegenerationInletAirTemperatureforTemperatureEquation(double minimumRegenerationInletAirTemperatureforTemperatureEquation);

      double maximumRegenerationInletAirTemperatureforTemperatureEquation() const;

      bool setMaximumRegenerationInletAirTemperatureforTemperatureEquation(double maximumRegenerationInletAirTemperatureforTemperatureEquation);

      double minimumProcessInletAirHumidityRatioforTemperatureEquation() const;

      bool setMinimumProcessInletAirHumidityRatioforTemperatureEquation(double minimumProcessInletAirHumidityRatioforTemperatureEquation);

      double maximumProcessInletAirHumidityRatioforTemperatureEquation() const;

      bool setMaximumProcessInletAirHumidityRatioforTemperatureEquation(double maximumProcessInletAirHumidityRatioforTemperatureEquation);

      double minimumProcessInletAirTemperatureforTemperatureEquation() const;

      bool setMinimumProcessInletAirTemperatureforTemperatureEquation(double minimumProcessInletAirTemperatureforTemperatureEquation);

      double maximumProcessInletAirTemperatureforTemperatureEquation() const;

      bool setMaximumProcessInletAirTemperatureforTemperatureEquation(double maximumProcessInletAirTemperatureforTemperatureEquation);

      double minimumRegenerationAirVelocityforTemperatureEquation() const;

      bool setMinimumRegenerationAirVelocityforTemperatureEquation(double minimumRegenerationAirVelocityforTemperatureEquation);

      double maximumRegenerationAirVelocityforTemperatureEquation() const;

      bool setMaximumRegenerationAirVelocityforTemperatureEquation(double maximumRegenerationAirVelocityforTemperatureEquation);

      double minimumRegenerationOutletAirTemperatureforTemperatureEquation() const;

      bool setMinimumRegenerationOutletAirTemperatureforTemperatureEquation(double minimumRegenerationOutletAirTemperatureforTemperatureEquation);

      double maximumRegenerationOutletAirTemperatureforTemperatureEquation() const;

      bool setMaximumRegenerationOutletAirTemperatureforTemperatureEquation(double maximumRegenerationOutletAirTemperatureforTemperatureEquation);

      double minimumRegenerationInletAirRelativeHumidityforTemperatureEquation() const;

      bool setMinimumRegenerationInletAirRelativeHumidityforTemperatureEquation(
        double minimumRegenerationInletAirRelativeHumidityforTemperatureEquation);

      double maximumRegenerationInletAirRelativeHumidityforTemperatureEquation() const;

      bool setMaximumRegenerationInletAirRelativeHumidityforTemperatureEquation(
        double maximumRegenerationInletAirRelativeHumidityforTemperatureEquation);

      double minimumProcessInletAirRelativeHumidityforTemperatureEquation() const;

      bool setMinimumProcessInletAirRelativeHumidityforTemperatureEquation(double minimumProcessInletAirRelativeHumidityforTemperatureEquation);

      double maximumProcessInletAirRelativeHumidityforTemperatureEquation() const;

      bool setMaximumProcessInletAirRelativeHumidityforTemperatureEquation(double maximumProcessInletAirRelativeHumidityforTemperatureEquation);

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

      double minimumRegenerationInletAirHumidityRatioforHumidityRatioEquation() const;

      bool
        setMinimumRegenerationInletAirHumidityRatioforHumidityRatioEquation(double minimumRegenerationInletAirHumidityRatioforHumidityRatioEquation);

      double maximumRegenerationInletAirHumidityRatioforHumidityRatioEquation() const;

      bool
        setMaximumRegenerationInletAirHumidityRatioforHumidityRatioEquation(double maximumRegenerationInletAirHumidityRatioforHumidityRatioEquation);

      double minimumRegenerationInletAirTemperatureforHumidityRatioEquation() const;

      bool setMinimumRegenerationInletAirTemperatureforHumidityRatioEquation(double minimumRegenerationInletAirTemperatureforHumidityRatioEquation);

      double maximumRegenerationInletAirTemperatureforHumidityRatioEquation() const;

      bool setMaximumRegenerationInletAirTemperatureforHumidityRatioEquation(double maximumRegenerationInletAirTemperatureforHumidityRatioEquation);

      double minimumProcessInletAirHumidityRatioforHumidityRatioEquation() const;

      bool setMinimumProcessInletAirHumidityRatioforHumidityRatioEquation(double minimumProcessInletAirHumidityRatioforHumidityRatioEquation);

      double maximumProcessInletAirHumidityRatioforHumidityRatioEquation() const;

      bool setMaximumProcessInletAirHumidityRatioforHumidityRatioEquation(double maximumProcessInletAirHumidityRatioforHumidityRatioEquation);

      double minimumProcessInletAirTemperatureforHumidityRatioEquation() const;

      bool setMinimumProcessInletAirTemperatureforHumidityRatioEquation(double minimumProcessInletAirTemperatureforHumidityRatioEquation);

      double maximumProcessInletAirTemperatureforHumidityRatioEquation() const;

      bool setMaximumProcessInletAirTemperatureforHumidityRatioEquation(double maximumProcessInletAirTemperatureforHumidityRatioEquation);

      double minimumRegenerationAirVelocityforHumidityRatioEquation() const;

      bool setMinimumRegenerationAirVelocityforHumidityRatioEquation(double minimumRegenerationAirVelocityforHumidityRatioEquation);

      double maximumRegenerationAirVelocityforHumidityRatioEquation() const;

      bool setMaximumRegenerationAirVelocityforHumidityRatioEquation(double maximumRegenerationAirVelocityforHumidityRatioEquation);

      double minimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation() const;

      bool setMinimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation(
        double minimumRegenerationOutletAirHumidityRatioforHumidityRatioEquation);

      double maximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation() const;

      bool setMaximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation(
        double maximumRegenerationOutletAirHumidityRatioforHumidityRatioEquation);

      double minimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation() const;

      bool setMinimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation(
        double minimumRegenerationInletAirRelativeHumidityforHumidityRatioEquation);

      double maximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation() const;

      bool setMaximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation(
        double maximumRegenerationInletAirRelativeHumidityforHumidityRatioEquation);

      double minimumProcessInletAirRelativeHumidityforHumidityRatioEquation() const;

      bool setMinimumProcessInletAirRelativeHumidityforHumidityRatioEquation(double minimumProcessInletAirRelativeHumidityforHumidityRatioEquation);

      double maximumProcessInletAirRelativeHumidityforHumidityRatioEquation() const;

      bool setMaximumProcessInletAirRelativeHumidityforHumidityRatioEquation(double maximumProcessInletAirRelativeHumidityforHumidityRatioEquation);

      //@}
      /** @name Other */
      //@{

      void autosize();

      void applySizingValues();

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.epmodel.HeatExchangerDesiccantBalancedFlowPerformanceDataType1");
    };

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOWPERFORMANCEDATATYPE1_IMPL_HPP
