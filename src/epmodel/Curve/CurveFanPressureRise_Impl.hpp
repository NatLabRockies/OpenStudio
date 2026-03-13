/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFANPRESSURERISE_IMPL_HPP
#define EPMODEL_CURVEFANPRESSURERISE_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CurveFanPressureRise_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~CurveFanPressureRise_Impl() override = default;

      double coefficient1C1() const;
      bool setCoefficient1C1(double coefficient1C1);

      double coefficient2C2() const;
      bool setCoefficient2C2(double coefficient2C2);

      double coefficient3C3() const;
      bool setCoefficient3C3(double coefficient3C3);

      double coefficient4C4() const;
      bool setCoefficient4C4(double coefficient4C4);

      double minimumValueofQfan() const;
      bool setMinimumValueofQfan(double minimumValueofQfan);

      double maximumValueofQfan() const;
      bool setMaximumValueofQfan(double maximumValueofQfan);

      double minimumValueofPsm() const;
      bool setMinimumValueofPsm(double minimumValueofPsm);

      double maximumValueofPsm() const;
      bool setMaximumValueofPsm(double maximumValueofPsm);

      boost::optional<double> minimumCurveOutput() const;
      bool setMinimumCurveOutput(double minimumCurveOutput);
      void resetMinimumCurveOutput();

      boost::optional<double> maximumCurveOutput() const;
      bool setMaximumCurveOutput(double maximumCurveOutput);
      void resetMaximumCurveOutput();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
