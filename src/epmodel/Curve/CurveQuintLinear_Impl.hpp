/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUINTLINEAR_IMPL_HPP
#define EPMODEL_CURVEQUINTLINEAR_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveQuintLinear_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveQuintLinear_Impl() override = default;

  double coefficient1Constant() const;
  double coefficient2v() const;
  double coefficient3w() const;
  double coefficient4x() const;
  double coefficient5y() const;
  double coefficient6z() const;
  double minimumValueofv() const;
  double maximumValueofv() const;
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
  std::string inputUnitTypeforv() const;
  bool isInputUnitTypeforvDefaulted() const;
  std::string inputUnitTypeforw() const;
  bool isInputUnitTypeforwDefaulted() const;
  std::string inputUnitTypeforx() const;
  bool isInputUnitTypeforxDefaulted() const;
  std::string inputUnitTypefory() const;
  bool isInputUnitTypeforyDefaulted() const;
  std::string inputUnitTypeforz() const;
  bool isInputUnitTypeforzDefaulted() const;

  bool setCoefficient1Constant(double coefficient1Constant);
  bool setCoefficient2v(double coefficient2v);
  bool setCoefficient3w(double coefficient3w);
  bool setCoefficient4x(double coefficient4x);
  bool setCoefficient5y(double coefficient5y);
  bool setCoefficient6z(double coefficient6z);
  bool setMinimumValueofv(double minimumValueofv);
  bool setMaximumValueofv(double maximumValueofv);
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
  bool setInputUnitTypeforv(const std::string& inputUnitTypeforv);
  void resetInputUnitTypeforv();
  bool setInputUnitTypeforw(const std::string& inputUnitTypeforw);
  void resetInputUnitTypeforw();
  bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
  void resetInputUnitTypeforx();
  bool setInputUnitTypefory(const std::string& inputUnitTypefory);
  void resetInputUnitTypefory();
  bool setInputUnitTypeforz(const std::string& inputUnitTypeforz);
  void resetInputUnitTypeforz();

  std::vector<std::string> inputUnitTypeforvValues() const;
  std::vector<std::string> inputUnitTypeforwValues() const;
  std::vector<std::string> inputUnitTypeforxValues() const;
  std::vector<std::string> inputUnitTypeforyValues() const;
  std::vector<std::string> inputUnitTypeforzValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
