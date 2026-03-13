/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEDOUBLEEXPONENTIALDECAY_IMPL_HPP
#define EPMODEL_CURVEDOUBLEEXPONENTIALDECAY_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveDoubleExponentialDecay_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveDoubleExponentialDecay_Impl() override = default;

      double coefficient1C1() const;
      bool setCoefficient1C1(double coefficient1C1);

      double coefficient2C2() const;
      bool setCoefficient2C2(double coefficient2C2);

      double coefficient3C3() const;
      bool setCoefficient3C3(double coefficient3C3);

      double coefficient4C4() const;
      bool setCoefficient4C4(double coefficient4C4);

      double coefficient5C5() const;
      bool setCoefficient5C5(double coefficient5C5);

      double minimumValueofx() const;
      bool setMinimumValueofx(double minimumValueofx);

      double maximumValueofx() const;
      bool setMaximumValueofx(double maximumValueofx);

      boost::optional<double> minimumCurveOutput() const;
      bool setMinimumCurveOutput(double minimumCurveOutput);
      void resetMinimumCurveOutput();

      boost::optional<double> maximumCurveOutput() const;
      bool setMaximumCurveOutput(double maximumCurveOutput);
      void resetMaximumCurveOutput();

      std::string inputUnitTypeforx() const;
      bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
      bool isInputUnitTypeforxDefaulted() const;
      void resetInputUnitTypeforx();

      std::string outputUnitType() const;
      bool setOutputUnitType(const std::string& outputUnitType);
      bool isOutputUnitTypeDefaulted() const;
      void resetOutputUnitType();

      std::vector<std::string> validInputUnitTypeforxValues() const;
      std::vector<std::string> validOutputUnitTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
