/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSUNDERFLOORAIRDISTRIBUTIONEXTERIOR_IMPL_HPP
#define EPMODEL_ROOMAIRSETTINGSUNDERFLOORAIRDISTRIBUTIONEXTERIOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API RoomAirSettingsUnderFloorAirDistributionExterior_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirSettingsUnderFloorAirDistributionExterior_Impl() override = default;

      boost::optional<double> numberofDiffusersperZone() const;
      bool isNumberofDiffusersperZoneDefaulted() const;
      bool isNumberofDiffusersperZoneAutocalculated() const;
      bool setNumberofDiffusersperZone(double numberofDiffusersperZone);
      void resetNumberofDiffusersperZone();
      void autocalculateNumberofDiffusersperZone();

      boost::optional<double> powerperPlume() const;
      bool isPowerperPlumeDefaulted() const;
      bool isPowerperPlumeAutocalculated() const;
      bool setPowerperPlume(double powerperPlume);
      void resetPowerperPlume();
      void autocalculatePowerperPlume();

      boost::optional<double> designEffectiveAreaofDiffuser() const;
      bool isDesignEffectiveAreaofDiffuserDefaulted() const;
      bool isDesignEffectiveAreaofDiffuserAutocalculated() const;
      bool setDesignEffectiveAreaofDiffuser(double designEffectiveAreaofDiffuser);
      void resetDesignEffectiveAreaofDiffuser();
      void autocalculateDesignEffectiveAreaofDiffuser();

      boost::optional<double> diffuserSlotAnglefromVertical() const;
      bool isDiffuserSlotAnglefromVerticalDefaulted() const;
      bool isDiffuserSlotAnglefromVerticalAutocalculated() const;
      bool setDiffuserSlotAnglefromVertical(double diffuserSlotAnglefromVertical);
      void resetDiffuserSlotAnglefromVertical();
      void autocalculateDiffuserSlotAnglefromVertical();

      double thermostatHeight() const;
      bool isThermostatHeightDefaulted() const;
      bool setThermostatHeight(double thermostatHeight);
      void resetThermostatHeight();

      double comfortHeight() const;
      bool isComfortHeightDefaulted() const;
      bool setComfortHeight(double comfortHeight);
      void resetComfortHeight();

      double temperatureDifferenceThresholdforReporting() const;
      bool isTemperatureDifferenceThresholdforReportingDefaulted() const;
      bool setTemperatureDifferenceThresholdforReporting(double temperatureDifferenceThresholdforReporting);
      void resetTemperatureDifferenceThresholdforReporting();

      std::string floorDiffuserType() const;
      bool isFloorDiffuserTypeDefaulted() const;
      bool setFloorDiffuserType(const std::string& floorDiffuserType);
      void resetFloorDiffuserType();

      boost::optional<double> transitionHeight() const;
      bool isTransitionHeightDefaulted() const;
      bool isTransitionHeightAutocalculated() const;
      bool setTransitionHeight(double transitionHeight);
      void resetTransitionHeight();
      void autocalculateTransitionHeight();

      boost::optional<double> coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const;
      bool isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted() const;
      bool isCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated() const;
      bool setCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
        double coefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
      void resetCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
      void autocalculateCoefficientAinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();

      boost::optional<double> coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const;
      bool isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted() const;
      bool isCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated() const;
      bool setCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
        double coefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
      void resetCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
      void autocalculateCoefficientBinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();

      boost::optional<double> coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const;
      bool isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted() const;
      bool isCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated() const;
      bool setCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
        double coefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
      void resetCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
      void autocalculateCoefficientCinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();

      boost::optional<double> coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const;
      bool isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted() const;
      bool isCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated() const;
      bool setCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
        double coefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
      void resetCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
      void autocalculateCoefficientDinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();

      boost::optional<double> coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2() const;
      bool isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Defaulted() const;
      bool isCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2Autocalculated() const;
      bool setCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2(
        double coefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2);
      void resetCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();
      void autocalculateCoefficientEinformulaKcEQUALATIMESGammaPOWBPLUSCPLUSDTIMESGammaPLUSETIMESGammaPOW2();

      std::vector<std::string> floorDiffuserTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
