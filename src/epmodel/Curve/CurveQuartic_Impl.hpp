/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUARTIC_IMPL_HPP
#define EPMODEL_CURVEQUARTIC_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveQuartic_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveQuartic_Impl() override = default;

  double coefficient1Constant() const;
  bool setCoefficient1Constant(double coefficient1Constant);

  double coefficient2x() const;
  bool setCoefficient2x(double coefficient2x);

  double coefficient3xPOW2() const;
  bool setCoefficient3xPOW2(double coefficient3xPOW2);

  double coefficient4xPOW3() const;
  bool setCoefficient4xPOW3(double coefficient4xPOW3);

  double coefficient5xPOW4() const;
  bool setCoefficient5xPOW4(double coefficient5xPOW4);

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

  std::string outputUnitType() const;
  bool isOutputUnitTypeDefaulted() const;
  bool setOutputUnitType(const std::string& outputUnitType);
  void resetOutputUnitType();

  std::vector<std::string> validInputUnitTypeforXValues() const;
  std::vector<std::string> validOutputUnitTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
