/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLEXHAUSTGASTOWATERHEATEXCHANGER_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLEXHAUSTGASTOWATERHEATEXCHANGER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  double heatRecoveryWaterMaximumFlowRate() const;
  bool setHeatRecoveryWaterMaximumFlowRate(double heatRecoveryWaterMaximumFlowRate);
  void resetHeatRecoveryWaterMaximumFlowRate();

  std::string heatExchangerCalculationMethod() const;
  bool setHeatExchangerCalculationMethod(const std::string& heatExchangerCalculationMethod);
  void resetHeatExchangerCalculationMethod();

  boost::optional<double> method1HeatExchangerEffectiveness() const;
  bool setMethod1HeatExchangerEffectiveness(double method1HeatExchangerEffectiveness);
  void resetMethod1HeatExchangerEffectiveness();

  boost::optional<double> method2Parameterhxs0() const;
  bool setMethod2Parameterhxs0(double method2Parameterhxs0);
  void resetMethod2Parameterhxs0();

  boost::optional<double> method2Parameterhxs1() const;
  bool setMethod2Parameterhxs1(double method2Parameterhxs1);
  void resetMethod2Parameterhxs1();

  boost::optional<double> method2Parameterhxs2() const;
  bool setMethod2Parameterhxs2(double method2Parameterhxs2);
  void resetMethod2Parameterhxs2();

  boost::optional<double> method2Parameterhxs3() const;
  bool setMethod2Parameterhxs3(double method2Parameterhxs3);
  void resetMethod2Parameterhxs3();

  boost::optional<double> method2Parameterhxs4() const;
  bool setMethod2Parameterhxs4(double method2Parameterhxs4);
  void resetMethod2Parameterhxs4();

  boost::optional<double> method3h0GasCoefficient() const;
  bool setMethod3h0GasCoefficient(double method3h0GasCoefficient);
  void resetMethod3h0GasCoefficient();

  boost::optional<double> method3NdotGasRefCoefficient() const;
  bool setMethod3NdotGasRefCoefficient(double method3NdotGasRefCoefficient);
  void resetMethod3NdotGasRefCoefficient();

  boost::optional<double> method3nCoefficient() const;
  bool setMethod3nCoefficient(double method3nCoefficient);
  void resetMethod3nCoefficient();

  boost::optional<double> method3GasArea() const;
  bool setMethod3GasArea(double method3GasArea);
  void resetMethod3GasArea();

  boost::optional<double> method3h0WaterCoefficient() const;
  bool setMethod3h0WaterCoefficient(double method3h0WaterCoefficient);
  void resetMethod3h0WaterCoefficient();

  boost::optional<double> method3NdotWaterrefCoefficient() const;
  bool setMethod3NdotWaterrefCoefficient(double method3NdotWaterrefCoefficient);
  void resetMethod3NdotWaterrefCoefficient();

  boost::optional<double> method3mCoefficient() const;
  bool setMethod3mCoefficient(double method3mCoefficient);
  void resetMethod3mCoefficient();

  boost::optional<double> method3WaterArea() const;
  bool setMethod3WaterArea(double method3WaterArea);
  void resetMethod3WaterArea();

  boost::optional<double> method3FAdjustmentFactor() const;
  bool setMethod3FAdjustmentFactor(double method3FAdjustmentFactor);
  void resetMethod3FAdjustmentFactor();

  boost::optional<double> method4hxl1Coefficient() const;
  bool setMethod4hxl1Coefficient(double method4hxl1Coefficient);
  void resetMethod4hxl1Coefficient();

  boost::optional<double> method4hxl2Coefficient() const;
  bool setMethod4hxl2Coefficient(double method4hxl2Coefficient);
  void resetMethod4hxl2Coefficient();

  boost::optional<double> method4CondensationThreshold() const;
  bool setMethod4CondensationThreshold(double method4CondensationThreshold);
  void resetMethod4CondensationThreshold();

  std::vector<std::string> heatExchangerCalculationMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
