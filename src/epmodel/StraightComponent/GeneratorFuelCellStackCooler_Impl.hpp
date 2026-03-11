/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLSTACKCOOLER_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLSTACKCOOLER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API GeneratorFuelCellStackCooler_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~GeneratorFuelCellStackCooler_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  double nominalStackTemperature() const;
  double actualStackTemperature() const;
  double coefficientr0() const;
  double coefficientr1() const;
  double coefficientr2() const;
  double coefficientr3() const;
  double stackCoolantFlowRate() const;
  double stackCoolerUFactorTimesAreaValue() const;
  double fscogenAdjustmentFactor() const;
  double stackCogenerationExchangerArea() const;
  double stackCogenerationExchangerNominalFlowRate() const;
  double stackCogenerationExchangerNominalHeatTransferCoefficient() const;
  double stackCogenerationExchangerNominalHeatTransferCoefficientExponent() const;
  double stackCoolerPumpPower() const;
  double stackCoolerPumpHeatLossFraction() const;
  double stackAirCoolerFanCoefficientf0() const;
  double stackAirCoolerFanCoefficientf1() const;
  double stackAirCoolerFanCoefficientf2() const;

  bool setNominalStackTemperature(double nominalStackTemperature);
  void resetNominalStackTemperature();

  bool setActualStackTemperature(double actualStackTemperature);
  void resetActualStackTemperature();

  bool setCoefficientr0(double coefficientr0);
  void resetCoefficientr0();

  bool setCoefficientr1(double coefficientr1);
  void resetCoefficientr1();

  bool setCoefficientr2(double coefficientr2);
  void resetCoefficientr2();

  bool setCoefficientr3(double coefficientr3);
  void resetCoefficientr3();

  bool setStackCoolantFlowRate(double stackCoolantFlowRate);
  void resetStackCoolantFlowRate();

  bool setStackCoolerUFactorTimesAreaValue(double stackCoolerUFactorTimesAreaValue);
  void resetStackCoolerUFactorTimesAreaValue();

  bool setFscogenAdjustmentFactor(double fscogenAdjustmentFactor);
  void resetFscogenAdjustmentFactor();

  bool setStackCogenerationExchangerArea(double stackCogenerationExchangerArea);
  void resetStackCogenerationExchangerArea();

  bool setStackCogenerationExchangerNominalFlowRate(double stackCogenerationExchangerNominalFlowRate);
  void resetStackCogenerationExchangerNominalFlowRate();

  bool setStackCogenerationExchangerNominalHeatTransferCoefficient(double stackCogenerationExchangerNominalHeatTransferCoefficient);
  void resetStackCogenerationExchangerNominalHeatTransferCoefficient();

  bool setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(double stackCogenerationExchangerNominalHeatTransferCoefficientExponent);
  void resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent();

  bool setStackCoolerPumpPower(double stackCoolerPumpPower);
  void resetStackCoolerPumpPower();

  bool setStackCoolerPumpHeatLossFraction(double stackCoolerPumpHeatLossFraction);
  void resetStackCoolerPumpHeatLossFraction();

  bool setStackAirCoolerFanCoefficientf0(double stackAirCoolerFanCoefficientf0);
  void resetStackAirCoolerFanCoefficientf0();

  bool setStackAirCoolerFanCoefficientf1(double stackAirCoolerFanCoefficientf1);
  void resetStackAirCoolerFanCoefficientf1();

  bool setStackAirCoolerFanCoefficientf2(double stackAirCoolerFanCoefficientf2);
  void resetStackAirCoolerFanCoefficientf2();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
