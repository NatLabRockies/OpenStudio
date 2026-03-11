/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENT_IMPL_HPP
#define EPMODEL_CURVEEXPONENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveExponent_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveExponent_Impl() override = default;

  double coefficient1Constant() const;
  double coefficient2Constant() const;
  double coefficient3Constant() const;
  double minimumValueofx() const;
  double maximumValueofx() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;
  std::string inputUnitTypeforX() const;
  bool isInputUnitTypeforXDefaulted() const;
  std::string outputUnitType() const;
  bool isOutputUnitTypeDefaulted() const;

  bool setCoefficient1Constant(double coefficient1Constant);
  bool setCoefficient2Constant(double coefficient2Constant);
  bool setCoefficient3Constant(double coefficient3Constant);
  bool setMinimumValueofx(double minimumValueofx);
  bool setMaximumValueofx(double maximumValueofx);
  bool setMinimumCurveOutput(double minimumCurveOutput);
  void resetMinimumCurveOutput();
  bool setMaximumCurveOutput(double maximumCurveOutput);
  void resetMaximumCurveOutput();
  bool setInputUnitTypeforX(const std::string& inputUnitTypeforX);
  void resetInputUnitTypeforX();
  bool setOutputUnitType(const std::string& outputUnitType);
  void resetOutputUnitType();

  std::vector<std::string> validInputUnitTypeforXValues() const;
  std::vector<std::string> validOutputUnitTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
