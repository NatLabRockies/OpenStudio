/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVECHILLERPARTLOADWITHLIFT_IMPL_HPP
#define EPMODEL_CURVECHILLERPARTLOADWITHLIFT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CurveChillerPartLoadWithLift_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CurveChillerPartLoadWithLift_Impl() override = default;

  double coefficient1C1() const;
  double coefficient2C2() const;
  double coefficient3C3() const;
  double coefficient4C4() const;
  double coefficient5C5() const;
  double coefficient6C6() const;
  double coefficient7C7() const;
  double coefficient8C8() const;
  double coefficient9C9() const;
  double coefficient10C10() const;
  double coefficient11C11() const;
  double coefficient12C12() const;
  double minimumValueofx() const;
  double maximumValueofx() const;
  double minimumValueofy() const;
  double maximumValueofy() const;
  double minimumValueofz() const;
  double maximumValueofz() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;
  std::string inputUnitTypeforx() const;
  bool isInputUnitTypeforxDefaulted() const;
  std::string inputUnitTypefory() const;
  bool isInputUnitTypeforyDefaulted() const;
  std::string inputUnitTypeforz() const;
  bool isInputUnitTypeforzDefaulted() const;
  std::string outputUnitType() const;
  bool isOutputUnitTypeDefaulted() const;

  bool setCoefficient1C1(double coefficient1C1);
  bool setCoefficient2C2(double coefficient2C2);
  bool setCoefficient3C3(double coefficient3C3);
  bool setCoefficient4C4(double coefficient4C4);
  bool setCoefficient5C5(double coefficient5C5);
  bool setCoefficient6C6(double coefficient6C6);
  bool setCoefficient7C7(double coefficient7C7);
  bool setCoefficient8C8(double coefficient8C8);
  bool setCoefficient9C9(double coefficient9C9);
  bool setCoefficient10C10(double coefficient10C10);
  bool setCoefficient11C11(double coefficient11C11);
  bool setCoefficient12C12(double coefficient12C12);
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
  bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
  void resetInputUnitTypeforx();
  bool setInputUnitTypefory(const std::string& inputUnitTypefory);
  void resetInputUnitTypefory();
  bool setInputUnitTypeforz(const std::string& inputUnitTypeforz);
  void resetInputUnitTypeforz();
  bool setOutputUnitType(const std::string& outputUnitType);
  void resetOutputUnitType();

  std::vector<std::string> validInputUnitTypeforxValues() const;
  std::vector<std::string> validInputUnitTypeforyValues() const;
  std::vector<std::string> validInputUnitTypeforzValues() const;
  std::vector<std::string> validOutputUnitTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
