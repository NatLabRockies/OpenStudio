/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEQUINTLINEAR_HPP
#define EPMODEL_CURVEQUINTLINEAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveQuintLinear_Impl;
}

class EPMODEL_API CurveQuintLinear : public ModelObject
{
 public:
  explicit CurveQuintLinear(const Model& model);

  virtual ~CurveQuintLinear() override = default;
  CurveQuintLinear(const CurveQuintLinear& other) = default;
  CurveQuintLinear(CurveQuintLinear&& other) = default;
  CurveQuintLinear& operator=(const CurveQuintLinear&) = default;
  CurveQuintLinear& operator=(CurveQuintLinear&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> inputUnitTypeforvValues();
  static std::vector<std::string> inputUnitTypeforwValues();
  static std::vector<std::string> inputUnitTypeforxValues();
  static std::vector<std::string> inputUnitTypeforyValues();
  static std::vector<std::string> inputUnitTypeforzValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveQuintLinear scalar accessor names/signatures.
  // - Field Mapping: coefficient/min-max and input-unit APIs map directly to E+ Curve:QuintLinear fields.
  // - ForwardTranslator evidence: ForwardTranslateCurveQuintLinear.cpp writes these scalar fields directly.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
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

 protected:
  using ImplType = detail::CurveQuintLinear_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveQuintLinear(std::shared_ptr<detail::CurveQuintLinear_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
