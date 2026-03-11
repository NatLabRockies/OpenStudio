/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVECUBICLINEAR_HPP
#define EPMODEL_CURVECUBICLINEAR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveCubicLinear_Impl;
}

class EPMODEL_API CurveCubicLinear : public ModelObject
{
 public:
  explicit CurveCubicLinear(const Model& model);

  virtual ~CurveCubicLinear() override = default;
  CurveCubicLinear(const CurveCubicLinear& other) = default;
  CurveCubicLinear(CurveCubicLinear&& other) = default;
  CurveCubicLinear& operator=(const CurveCubicLinear&) = default;
  CurveCubicLinear& operator=(CurveCubicLinear&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validInputUnitTypeforXValues();
  static std::vector<std::string> validInputUnitTypeforYValues();
  static std::vector<std::string> validOutputUnitTypeValues();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart exists; accessor names are IDD-derived.
  // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:CubicLinear fields.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
  double coefficient1Constant() const;
  double coefficient2x() const;
  double coefficient3xPOW2() const;
  double coefficient4xPOW3() const;
  double coefficient5y() const;
  double coefficient6xTIMESY() const;
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
  bool setCoefficient4xPOW3(double coefficient4xPOW3);
  bool setCoefficient5y(double coefficient5y);
  bool setCoefficient6xTIMESY(double coefficient6xTIMESY);
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
  using ImplType = detail::CurveCubicLinear_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveCubicLinear(std::shared_ptr<detail::CurveCubicLinear_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
