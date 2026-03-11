/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEFANPRESSURERISE_IMPL_HPP
#define EPMODEL_CURVEFANPRESSURERISE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveFanPressureRise_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveFanPressureRise_Impl() override = default;

  double coefficient1C1() const;
  double coefficient2C2() const;
  double coefficient3C3() const;
  double coefficient4C4() const;
  double minimumValueofQfan() const;
  double maximumValueofQfan() const;
  double minimumValueofPsm() const;
  double maximumValueofPsm() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;

  bool setCoefficient1C1(double coefficient1C1);
  bool setCoefficient2C2(double coefficient2C2);
  bool setCoefficient3C3(double coefficient3C3);
  bool setCoefficient4C4(double coefficient4C4);
  bool setMinimumValueofQfan(double minimumValueofQfan);
  bool setMaximumValueofQfan(double maximumValueofQfan);
  bool setMinimumValueofPsm(double minimumValueofPsm);
  bool setMaximumValueofPsm(double maximumValueofPsm);
  bool setMinimumCurveOutput(double minimumCurveOutput);
  void resetMinimumCurveOutput();
  bool setMaximumCurveOutput(double maximumCurveOutput);
  void resetMaximumCurveOutput();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
