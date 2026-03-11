/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVEBIQUADRATIC_HPP
#define EPMODEL_CURVEBIQUADRATIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CurveBiquadratic_Impl;
}

class EPMODEL_API CurveBiquadratic : public ModelObject
{
 public:
  explicit CurveBiquadratic(const Model& model);

  virtual ~CurveBiquadratic() override = default;
  CurveBiquadratic(const CurveBiquadratic& other) = default;
  CurveBiquadratic(CurveBiquadratic&& other) = default;
  CurveBiquadratic& operator=(const CurveBiquadratic&) = default;
  CurveBiquadratic& operator=(CurveBiquadratic&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validInputUnitTypeforXValues();
  static std::vector<std::string> validInputUnitTypeforYValues();
  static std::vector<std::string> validOutputUnitTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model CurveBiquadratic scalar accessor names/signatures.
  // - Field Mapping: coefficient/min/max and unit-type APIs map directly to E+ Curve:Biquadratic fields.
  // - Field Mapping: Input/Output unit type default/reset behavior mirrors ForwardTranslator default-omission checks.
  // - TODO(parity): Keep this pass scalar-only; relationship APIs remain out of scope.
  double coefficient1Constant() const;
  double coefficient2x() const;
  double coefficient3xPOW2() const;
  double coefficient4y() const;
  double coefficient5yPOW2() const;
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
  bool setCoefficient4y(double coefficient4y);
  bool setCoefficient5yPOW2(double coefficient5yPOW2);
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
  using ImplType = detail::CurveBiquadratic_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CurveBiquadratic(std::shared_ptr<detail::CurveBiquadratic_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
