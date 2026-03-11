/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEEXPONENT_HPP
#define EPMODEL_CURVEEXPONENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveExponent_Impl;
}

class EPMODEL_API CurveExponent : public ModelObject
{
 public:
  explicit CurveExponent(const Model& model);

  virtual ~CurveExponent() override = default;
  CurveExponent(const CurveExponent& other) = default;
  CurveExponent(CurveExponent&& other) = default;
  CurveExponent& operator=(const CurveExponent&) = default;
  CurveExponent& operator=(CurveExponent&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validInputUnitTypeforXValues();
  static std::vector<std::string> validOutputUnitTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveExponent scalar accessor names/signatures.
  // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Exponent fields.
  // - ForwardTranslator evidence: ForwardTranslateCurveExponent.cpp writes these scalar fields directly.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
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

 protected:
  using ImplType = detail::CurveExponent_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveExponent(std::shared_ptr<detail::CurveExponent_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
