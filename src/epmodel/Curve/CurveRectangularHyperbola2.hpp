/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVERECTANGULARHYPERBOLA2_HPP
#define EPMODEL_CURVERECTANGULARHYPERBOLA2_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveRectangularHyperbola2_Impl;
}

class EPMODEL_API CurveRectangularHyperbola2 : public ModelObject
{
 public:
  explicit CurveRectangularHyperbola2(const Model& model);

  virtual ~CurveRectangularHyperbola2() override = default;
  CurveRectangularHyperbola2(const CurveRectangularHyperbola2& other) = default;
  CurveRectangularHyperbola2(CurveRectangularHyperbola2&& other) = default;
  CurveRectangularHyperbola2& operator=(const CurveRectangularHyperbola2&) = default;
  CurveRectangularHyperbola2& operator=(CurveRectangularHyperbola2&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validInputUnitTypeforxValues();
  static std::vector<std::string> validOutputUnitTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveRectangularHyperbola2 scalar accessor names/signatures.
  // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:RectangularHyperbola2 fields.
  // - ForwardTranslator evidence: ForwardTranslateCurveRectangularHyperbola2.cpp writes these scalar fields directly.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
  double coefficient1C1() const;
  double coefficient2C2() const;
  double coefficient3C3() const;
  double minimumValueofx() const;
  double maximumValueofx() const;
  boost::optional<double> minimumCurveOutput() const;
  boost::optional<double> maximumCurveOutput() const;
  std::string inputUnitTypeforx() const;
  bool isInputUnitTypeforxDefaulted() const;
  std::string outputUnitType() const;
  bool isOutputUnitTypeDefaulted() const;

  bool setCoefficient1C1(double coefficient1C1);
  bool setCoefficient2C2(double coefficient2C2);
  bool setCoefficient3C3(double coefficient3C3);
  bool setMinimumValueofx(double minimumValueofx);
  bool setMaximumValueofx(double maximumValueofx);
  bool setMinimumCurveOutput(double minimumCurveOutput);
  void resetMinimumCurveOutput();
  bool setMaximumCurveOutput(double maximumCurveOutput);
  void resetMaximumCurveOutput();
  bool setInputUnitTypeforx(const std::string& inputUnitTypeforx);
  void resetInputUnitTypeforx();
  bool setOutputUnitType(const std::string& outputUnitType);
  void resetOutputUnitType();

 protected:
  using ImplType = detail::CurveRectangularHyperbola2_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveRectangularHyperbola2(std::shared_ptr<detail::CurveRectangularHyperbola2_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
