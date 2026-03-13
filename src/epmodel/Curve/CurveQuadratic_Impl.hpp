/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADRATIC_IMPL_HPP
#define EPMODEL_CURVEQUADRATIC_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveQuadratic_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveQuadratic_Impl() override = default;

      double coefficient1Constant() const;
      bool setCoefficient1Constant(double coefficient1Constant);

      double coefficient2x() const;
      bool setCoefficient2x(double coefficient2x);

      double coefficient3xPOW2() const;
      bool setCoefficient3xPOW2(double coefficient3xPOW2);

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
      bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
      void resetInputUnitTypeforX();
      bool isInputUnitTypeforXDefaulted() const;

      std::string outputUnitType() const;
      bool setOutputUnitType(const std::string& outputUnitType);
      void resetOutputUnitType();
      bool isOutputUnitTypeDefaulted() const;

      std::vector<std::string> validInputUnitTypeforXValues() const;
      std::vector<std::string> validOutputUnitTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
