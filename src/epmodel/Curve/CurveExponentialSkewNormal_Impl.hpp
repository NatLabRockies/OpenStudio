/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENTIALSKEWNORMAL_IMPL_HPP
#define EPMODEL_CURVEEXPONENTIALSKEWNORMAL_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveExponentialSkewNormal_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveExponentialSkewNormal_Impl() override = default;

      double coefficient1C1() const;
      bool setCoefficient1C1(double coefficient1C1);

      double coefficient2C2() const;
      bool setCoefficient2C2(double coefficient2C2);

      double coefficient3C3() const;
      bool setCoefficient3C3(double coefficient3C3);

      double coefficient4C4() const;
      bool setCoefficient4C4(double coefficient4C4);

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
      bool isInputUnitTypeforxDefaulted() const;
      bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
      void resetInputUnitTypeforx();
      std::vector<std::string> validInputUnitTypeforxValues() const;

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
