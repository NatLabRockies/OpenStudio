/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORFUELCELLSTACKCOOLER_IMPL_HPP
#define EPMODEL_GENERATORFUELCELLSTACKCOOLER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class GeneratorFuelCell;
  class Node;

  namespace detail {

    class EPMODEL_API GeneratorFuelCellStackCooler_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~GeneratorFuelCellStackCooler_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      double nominalStackTemperature() const;
      bool setNominalStackTemperature(double nominalStackTemperature);
      void resetNominalStackTemperature();

      double actualStackTemperature() const;
      bool setActualStackTemperature(double actualStackTemperature);
      void resetActualStackTemperature();

      double coefficientr0() const;
      bool setCoefficientr0(double coefficientr0);
      void resetCoefficientr0();

      double coefficientr1() const;
      bool setCoefficientr1(double coefficientr1);
      void resetCoefficientr1();

      double coefficientr2() const;
      bool setCoefficientr2(double coefficientr2);
      void resetCoefficientr2();

      double coefficientr3() const;
      bool setCoefficientr3(double coefficientr3);
      void resetCoefficientr3();

      double stackCoolantFlowRate() const;
      bool setStackCoolantFlowRate(double stackCoolantFlowRate);
      void resetStackCoolantFlowRate();

      double stackCoolerUFactorTimesAreaValue() const;
      bool setStackCoolerUFactorTimesAreaValue(double stackCoolerUFactorTimesAreaValue);
      void resetStackCoolerUFactorTimesAreaValue();

      double fscogenAdjustmentFactor() const;
      bool setFscogenAdjustmentFactor(double fscogenAdjustmentFactor);
      void resetFscogenAdjustmentFactor();

      double stackCogenerationExchangerArea() const;
      bool setStackCogenerationExchangerArea(double stackCogenerationExchangerArea);
      void resetStackCogenerationExchangerArea();

      double stackCogenerationExchangerNominalFlowRate() const;
      bool setStackCogenerationExchangerNominalFlowRate(double stackCogenerationExchangerNominalFlowRate);
      void resetStackCogenerationExchangerNominalFlowRate();

      double stackCogenerationExchangerNominalHeatTransferCoefficient() const;
      bool setStackCogenerationExchangerNominalHeatTransferCoefficient(double stackCogenerationExchangerNominalHeatTransferCoefficient);
      void resetStackCogenerationExchangerNominalHeatTransferCoefficient();

      double stackCogenerationExchangerNominalHeatTransferCoefficientExponent() const;
      bool
        setStackCogenerationExchangerNominalHeatTransferCoefficientExponent(double stackCogenerationExchangerNominalHeatTransferCoefficientExponent);
      void resetStackCogenerationExchangerNominalHeatTransferCoefficientExponent();

      double stackCoolerPumpPower() const;
      bool setStackCoolerPumpPower(double stackCoolerPumpPower);
      void resetStackCoolerPumpPower();

      double stackCoolerPumpHeatLossFraction() const;
      bool setStackCoolerPumpHeatLossFraction(double stackCoolerPumpHeatLossFraction);
      void resetStackCoolerPumpHeatLossFraction();

      double stackAirCoolerFanCoefficientf0() const;
      bool setStackAirCoolerFanCoefficientf0(double stackAirCoolerFanCoefficientf0);
      void resetStackAirCoolerFanCoefficientf0();

      double stackAirCoolerFanCoefficientf1() const;
      bool setStackAirCoolerFanCoefficientf1(double stackAirCoolerFanCoefficientf1);
      void resetStackAirCoolerFanCoefficientf1();

      double stackAirCoolerFanCoefficientf2() const;
      bool setStackAirCoolerFanCoefficientf2(double stackAirCoolerFanCoefficientf2);
      void resetStackAirCoolerFanCoefficientf2();

      boost::optional<openstudio::epmodel::GeneratorFuelCell> fuelCell() const;

      bool addToNode(Node& node) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
