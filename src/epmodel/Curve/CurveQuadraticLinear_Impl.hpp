/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADRATICLINEAR_IMPL_HPP
#define EPMODEL_CURVEQUADRATICLINEAR_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveQuadraticLinear_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveQuadraticLinear_Impl() override = default;

      std::vector<std::string> validInputUnitTypeforXValues() const;
      std::vector<std::string> validInputUnitTypeforYValues() const;
      std::vector<std::string> validOutputUnitTypeValues() const;

      double coefficient1Constant() const;
      bool setCoefficient1Constant(double coefficient1Constant);

      double coefficient2x() const;
      bool setCoefficient2x(double coefficient2x);

      double coefficient3xPOW2() const;
      bool setCoefficient3xPOW2(double coefficient3xPOW2);

      double coefficient4y() const;
      bool setCoefficient4y(double coefficient4y);

      double coefficient5xTIMESY() const;
      bool setCoefficient5xTIMESY(double coefficient5xTIMESY);

      double coefficient6xPOW2TIMESY() const;
      bool setCoefficient6xPOW2TIMESY(double coefficient6xPOW2TIMESY);

      double minimumValueofx() const;
      bool setMinimumValueofx(double minimumValueofx);

      double maximumValueofx() const;
      bool setMaximumValueofx(double maximumValueofx);

      double minimumValueofy() const;
      bool setMinimumValueofy(double minimumValueofy);

      double maximumValueofy() const;
      bool setMaximumValueofy(double maximumValueofy);

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

      std::string inputUnitTypeforY() const;
      bool isInputUnitTypeforYDefaulted() const;
      bool setInputUnitTypeforY(const std::string& inputUnitTypeforY);
      void resetInputUnitTypeforY();

      std::string outputUnitType() const;
      bool isOutputUnitTypeDefaulted() const;
      bool setOutputUnitType(const std::string& outputUnitType);
      void resetOutputUnitType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
