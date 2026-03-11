/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVECUBICLINEAR_IMPL_HPP
#define EPMODEL_CURVECUBICLINEAR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveCubicLinear_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveCubicLinear_Impl() override = default;

  double coefficient1Constant() const;
  double coefficient2x() const;
  double coefficient3xPOW2() const;
  double coefficient4xPOW3() const;
  double coefficient5y() const;
  double coefficient6xTIMESY() const;
  double minimumValueofx() const;
  double maximumValueofx() const;
  double minimumValueofy() const;
  double maximumValueofy() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;
  std::string inputUnitTypeforX() const;
  bool isInputUnitTypeforXDefaulted() const;
  std::string inputUnitTypeforY() const;
  bool isInputUnitTypeforYDefaulted() const;
  std::string outputUnitType() const;
  bool isOutputUnitTypeDefaulted() const;

  bool setCoefficient1Constant(double coefficient1Constant);
  bool setCoefficient2x(double coefficient2x);
  bool setCoefficient3xPOW2(double coefficient3xPOW2);
  bool setCoefficient4xPOW3(double coefficient4xPOW3);
  bool setCoefficient5y(double coefficient5y);
  bool setCoefficient6xTIMESY(double coefficient6xTIMESY);
  bool setMinimumValueofx(double minimumValueofx);
  bool setMaximumValueofx(double maximumValueofx);
  bool setMinimumValueofy(double minimumValueofy);
  bool setMaximumValueofy(double maximumValueofy);
  bool setMinimumCurveOutput(double minimumCurveOutput);
  void resetMinimumCurveOutput();
  bool setMaximumCurveOutput(double maximumCurveOutput);
  void resetMaximumCurveOutput();
  bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
  void resetInputUnitTypeforX();
  bool setInputUnitTypeforY(const std::string& inputUnitTypeforY);
  void resetInputUnitTypeforY();
  bool setOutputUnitType(const std::string& outputUnitType);
  void resetOutputUnitType();

  std::vector<std::string> validInputUnitTypeforXValues() const;
  std::vector<std::string> validInputUnitTypeforYValues() const;
  std::vector<std::string> validOutputUnitTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
