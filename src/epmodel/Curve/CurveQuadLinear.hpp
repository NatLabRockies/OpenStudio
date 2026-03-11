/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUADLINEAR_HPP
#define EPMODEL_CURVEQUADLINEAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveQuadLinear_Impl;
}

class EPMODEL_API CurveQuadLinear : public ModelObject
{
 public:
  explicit CurveQuadLinear(const Model& model);

  virtual ~CurveQuadLinear() override = default;
  CurveQuadLinear(const CurveQuadLinear& other) = default;
  CurveQuadLinear(CurveQuadLinear&& other) = default;
  CurveQuadLinear& operator=(const CurveQuadLinear&) = default;
  CurveQuadLinear& operator=(CurveQuadLinear&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> inputUnitTypeforwValues();
  static std::vector<std::string> inputUnitTypeforxValues();
  static std::vector<std::string> inputUnitTypeforyValues();
  static std::vector<std::string> inputUnitTypeforzValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveQuadLinear scalar accessor names/signatures.
  // - Field Mapping: coefficient/min/max and input-unit APIs map directly to E+ Curve:QuadLinear fields.
  // - ForwardTranslator evidence: ForwardTranslateCurveQuadLinear.cpp writes these scalar fields directly.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
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

 protected:
  using ImplType = detail::CurveQuadLinear_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveQuadLinear(std::shared_ptr<detail::CurveQuadLinear_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
