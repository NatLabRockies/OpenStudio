/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORWINDTURBINE_IMPL_HPP
#define EPMODEL_GENERATORWINDTURBINE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeneratorWindTurbine_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeneratorWindTurbine_Impl() override = default;

      std::string rotorType() const;
      bool setRotorType(const std::string& rotorType);

      std::string powerControl() const;
      bool setPowerControl(const std::string& powerControl);

      double ratedRotorSpeed() const;
      bool setRatedRotorSpeed(double ratedRotorSpeed);

      double rotorDiameter() const;
      bool setRotorDiameter(double rotorDiameter);

      double overallHeight() const;
      bool setOverallHeight(double overallHeight);

      int numberofBlades() const;
      bool setNumberofBlades(int numberofBlades);

      double ratedPower() const;
      bool setRatedPower(double ratedPower);

      double ratedWindSpeed() const;
      bool setRatedWindSpeed(double ratedWindSpeed);

      double cutInWindSpeed() const;
      bool setCutInWindSpeed(double cutInWindSpeed);

      double cutOutWindSpeed() const;
      bool setCutOutWindSpeed(double cutOutWindSpeed);

      double fractionSystemEfficiency() const;
      bool setFractionSystemEfficiency(double fractionSystemEfficiency);

      double maximumTipSpeedRatio() const;
      bool setMaximumTipSpeedRatio(double maximumTipSpeedRatio);

      double maximumPowerCoefficient() const;
      bool setMaximumPowerCoefficient(double maximumPowerCoefficient);

      boost::optional<double> annualLocalAverageWindSpeed() const;
      bool setAnnualLocalAverageWindSpeed(double annualLocalAverageWindSpeed);
      void resetAnnualLocalAverageWindSpeed();

      double heightforLocalAverageWindSpeed() const;
      bool setHeightforLocalAverageWindSpeed(double heightforLocalAverageWindSpeed);

      double bladeChordArea() const;
      bool setBladeChordArea(double bladeChordArea);

      double bladeDragCoefficient() const;
      bool setBladeDragCoefficient(double bladeDragCoefficient);

      double bladeLiftCoefficient() const;
      bool setBladeLiftCoefficient(double bladeLiftCoefficient);

      double powerCoefficientC1() const;
      bool setPowerCoefficientC1(double powerCoefficientC1);

      double powerCoefficientC2() const;
      bool setPowerCoefficientC2(double powerCoefficientC2);

      double powerCoefficientC3() const;
      bool setPowerCoefficientC3(double powerCoefficientC3);

      double powerCoefficientC4() const;
      bool setPowerCoefficientC4(double powerCoefficientC4);

      double powerCoefficientC5() const;
      bool setPowerCoefficientC5(double powerCoefficientC5);

      double powerCoefficientC6() const;
      bool setPowerCoefficientC6(double powerCoefficientC6);

      std::vector<std::string> rotorTypeValues() const;
      std::vector<std::string> powerControlValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
