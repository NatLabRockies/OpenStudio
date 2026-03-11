/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADRATICLINEAR_HPP
#define EPMODEL_CURVEQUADRATICLINEAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveQuadraticLinear_Impl;
}

class EPMODEL_API CurveQuadraticLinear : public ModelObject
{
 public:
  explicit CurveQuadraticLinear(const Model& model);

  virtual ~CurveQuadraticLinear() override = default;
  CurveQuadraticLinear(const CurveQuadraticLinear& other) = default;
  CurveQuadraticLinear(CurveQuadraticLinear&& other) = default;
  CurveQuadraticLinear& operator=(const CurveQuadraticLinear&) = default;
  CurveQuadraticLinear& operator=(CurveQuadraticLinear&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validInputUnitTypeforXValues();
  static std::vector<std::string> validInputUnitTypeforYValues();
  static std::vector<std::string> validOutputUnitTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveQuadraticLinear scalar accessor names/signatures.
  // - Field Mapping: coefficients/min-max/unit-type APIs map directly to E+ Curve:QuadraticLinear fields.
  // - ForwardTranslator evidence: ForwardTranslateCurveQuadraticLinear.cpp writes these scalar fields directly.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
  double coefficient1Constant() const;
  double coefficient2x() const;
  double coefficient3xPOW2() const;
  double coefficient4y() const;
  double coefficient5xTIMESY() const;
  double coefficient6xPOW2TIMESY() const;
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
  bool setCoefficient4y(double coefficient4y);
  bool setCoefficient5xTIMESY(double coefficient5xTIMESY);
  bool setCoefficient6xPOW2TIMESY(double coefficient6xPOW2TIMESY);
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

 protected:
  using ImplType = detail::CurveQuadraticLinear_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveQuadraticLinear(std::shared_ptr<detail::CurveQuadraticLinear_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
