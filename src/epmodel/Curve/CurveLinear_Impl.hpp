/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVELINEAR_IMPL_HPP
#define EPMODEL_CURVELINEAR_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveLinear_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveLinear_Impl() override = default;

      double coefficient1Constant() const;
      bool setCoefficient1Constant(double coefficient1Constant);

      double coefficient2x() const;
      bool setCoefficient2x(double coefficient2x);

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

      std::string inputUnitTypeforX() const;
      bool isInputUnitTypeforXDefaulted() const;
      bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
      void resetInputUnitTypeforX();
      std::vector<std::string> validInputUnitTypeforXValues() const;

      std::string outputUnitType() const;
      bool isOutputUnitTypeDefaulted() const;
      bool setOutputUnitType(const std::string& outputUnitType);
      void resetOutputUnitType();
      std::vector<std::string> validOutputUnitTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
