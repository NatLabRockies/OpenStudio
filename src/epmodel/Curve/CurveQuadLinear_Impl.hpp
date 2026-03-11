/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADLINEAR_IMPL_HPP
#define EPMODEL_CURVEQUADLINEAR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveQuadLinear_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveQuadLinear_Impl() override = default;

  double coefficient1Constant() const;
  double coefficient2w() const;
  double coefficient3x() const;
  double coefficient4y() const;
  double coefficient5z() const;
  double minimumValueofw() const;
  double maximumValueofw() const;
  double minimumValueofx() const;
  double maximumValueofx() const;
  double minimumValueofy() const;
  double maximumValueofy() const;
  double minimumValueofz() const;
  double maximumValueofz() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;
  std::string inputUnitTypeforw() const;
  bool isInputUnitTypeforwDefaulted() const;
  std::string inputUnitTypeforx() const;
  bool isInputUnitTypeforxDefaulted() const;
  std::string inputUnitTypefory() const;
  bool isInputUnitTypeforyDefaulted() const;
  std::string inputUnitTypeforz() const;
  bool isInputUnitTypeforzDefaulted() const;

  bool setCoefficient1Constant(double coefficient1Constant);
  bool setCoefficient2w(double coefficient2w);
  bool setCoefficient3x(double coefficient3x);
  bool setCoefficient4y(double coefficient4y);
  bool setCoefficient5z(double coefficient5z);
  bool setMinimumValueofw(double minimumValueofw);
  bool setMaximumValueofw(double maximumValueofw);
  bool setMinimumValueofx(double minimumValueofx);
  bool setMaximumValueofx(double maximumValueofx);
  bool setMinimumValueofy(double minimumValueofy);
  bool setMaximumValueofy(double maximumValueofy);
  bool setMinimumValueofz(double minimumValueofz);
  bool setMaximumValueofz(double maximumValueofz);
  bool setMinimumCurveOutput(double minimumCurveOutput);
  void resetMinimumCurveOutput();
  bool setMaximumCurveOutput(double maximumCurveOutput);
  void resetMaximumCurveOutput();
  bool setInputUnitTypeforw(const std::string& inputUnitTypeforw);
  void resetInputUnitTypeforw();
  bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
  void resetInputUnitTypeforx();
  bool setInputUnitTypefory(const std::string& inputUnitTypefory);
  void resetInputUnitTypefory();
  bool setInputUnitTypeforz(const std::string& inputUnitTypeforz);
  void resetInputUnitTypeforz();

  std::vector<std::string> inputUnitTypeforwValues() const;
  std::vector<std::string> inputUnitTypeforxValues() const;
  std::vector<std::string> inputUnitTypeforyValues() const;
  std::vector<std::string> inputUnitTypeforzValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
