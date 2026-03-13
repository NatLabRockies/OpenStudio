/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveRectangularHyperbola1.hpp"
#include "Curve/CurveRectangularHyperbola1_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_RectangularHyperbola1_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveRectangularHyperbola1::CurveRectangularHyperbola1(const Model& model) : ModelObject(CurveRectangularHyperbola1::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveRectangularHyperbola1_Impl>());
    OS_ASSERT(setCoefficient1C1(1.0));
    OS_ASSERT(setCoefficient2C2(1.0));
    OS_ASSERT(setCoefficient3C3(0.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
  }

  CurveRectangularHyperbola1::CurveRectangularHyperbola1(std::shared_ptr<detail::CurveRectangularHyperbola1_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CurveRectangularHyperbola1::iddObjectType() {
    return IddObjectType::Curve_RectangularHyperbola1;
  }

  std::vector<std::string> CurveRectangularHyperbola1::validInputUnitTypeforxValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_RectangularHyperbola1Fields::InputUnitTypeforx);
  }

  std::vector<std::string> CurveRectangularHyperbola1::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_RectangularHyperbola1Fields::OutputUnitType);
  }

  double CurveRectangularHyperbola1::coefficient1C1() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->coefficient1C1();
  }

  bool CurveRectangularHyperbola1::setCoefficient1C1(double coefficient1C1) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setCoefficient1C1(coefficient1C1);
  }

  double CurveRectangularHyperbola1::coefficient2C2() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->coefficient2C2();
  }

  bool CurveRectangularHyperbola1::setCoefficient2C2(double coefficient2C2) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setCoefficient2C2(coefficient2C2);
  }

  double CurveRectangularHyperbola1::coefficient3C3() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->coefficient3C3();
  }

  bool CurveRectangularHyperbola1::setCoefficient3C3(double coefficient3C3) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setCoefficient3C3(coefficient3C3);
  }

  double CurveRectangularHyperbola1::minimumValueofx() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->minimumValueofx();
  }

  bool CurveRectangularHyperbola1::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveRectangularHyperbola1::maximumValueofx() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->maximumValueofx();
  }

  bool CurveRectangularHyperbola1::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  boost::optional<double> CurveRectangularHyperbola1::minimumCurveOutput() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->minimumCurveOutput();
  }

  bool CurveRectangularHyperbola1::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveRectangularHyperbola1::resetMinimumCurveOutput() {
    getImpl<detail::CurveRectangularHyperbola1_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveRectangularHyperbola1::maximumCurveOutput() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->maximumCurveOutput();
  }

  bool CurveRectangularHyperbola1::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveRectangularHyperbola1::resetMaximumCurveOutput() {
    getImpl<detail::CurveRectangularHyperbola1_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveRectangularHyperbola1::inputUnitTypeforx() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->inputUnitTypeforx();
  }

  bool CurveRectangularHyperbola1::isInputUnitTypeforxDefaulted() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->isInputUnitTypeforxDefaulted();
  }

  bool CurveRectangularHyperbola1::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
  }

  void CurveRectangularHyperbola1::resetInputUnitTypeforx() {
    getImpl<detail::CurveRectangularHyperbola1_Impl>()->resetInputUnitTypeforx();
  }

  std::string CurveRectangularHyperbola1::outputUnitType() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->outputUnitType();
  }

  bool CurveRectangularHyperbola1::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveRectangularHyperbola1::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveRectangularHyperbola1_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveRectangularHyperbola1::resetOutputUnitType() {
    getImpl<detail::CurveRectangularHyperbola1_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveRectangularHyperbola1_Impl::coefficient1C1() const {
      const auto value = getDouble(openstudio::Curve_RectangularHyperbola1Fields::Coefficient1C1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::setCoefficient1C1(double coefficient1C1) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::Coefficient1C1, coefficient1C1);
      OS_ASSERT(result);
      return result;
    }

    double CurveRectangularHyperbola1_Impl::coefficient2C2() const {
      const auto value = getDouble(openstudio::Curve_RectangularHyperbola1Fields::Coefficient2C2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::setCoefficient2C2(double coefficient2C2) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::Coefficient2C2, coefficient2C2);
      OS_ASSERT(result);
      return result;
    }

    double CurveRectangularHyperbola1_Impl::coefficient3C3() const {
      const auto value = getDouble(openstudio::Curve_RectangularHyperbola1Fields::Coefficient3C3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::setCoefficient3C3(double coefficient3C3) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::Coefficient3C3, coefficient3C3);
      OS_ASSERT(result);
      return result;
    }

    double CurveRectangularHyperbola1_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_RectangularHyperbola1Fields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveRectangularHyperbola1_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_RectangularHyperbola1Fields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveRectangularHyperbola1_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_RectangularHyperbola1Fields::MinimumCurveOutput, true);
    }

    bool CurveRectangularHyperbola1_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveRectangularHyperbola1_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola1Fields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveRectangularHyperbola1_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_RectangularHyperbola1Fields::MaximumCurveOutput, true);
    }

    bool CurveRectangularHyperbola1_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_RectangularHyperbola1Fields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveRectangularHyperbola1_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola1Fields::MaximumCurveOutput, ""));
    }

    std::string CurveRectangularHyperbola1_Impl::inputUnitTypeforx() const {
      const auto value = getString(openstudio::Curve_RectangularHyperbola1Fields::InputUnitTypeforx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::isInputUnitTypeforxDefaulted() const {
      return isEmpty(openstudio::Curve_RectangularHyperbola1Fields::InputUnitTypeforx);
    }

    bool CurveRectangularHyperbola1_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
      return setString(openstudio::Curve_RectangularHyperbola1Fields::InputUnitTypeforx, inputUnitTypeforx);
    }

    void CurveRectangularHyperbola1_Impl::resetInputUnitTypeforx() {
      OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola1Fields::InputUnitTypeforx, ""));
    }

    std::string CurveRectangularHyperbola1_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_RectangularHyperbola1Fields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveRectangularHyperbola1_Impl::isOutputUnitTypeDefaulted() const {
      return isEmpty(openstudio::Curve_RectangularHyperbola1Fields::OutputUnitType);
    }

    bool CurveRectangularHyperbola1_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_RectangularHyperbola1Fields::OutputUnitType, outputUnitType);
    }

    void CurveRectangularHyperbola1_Impl::resetOutputUnitType() {
      OS_ASSERT(setString(openstudio::Curve_RectangularHyperbola1Fields::OutputUnitType, ""));
    }

    std::vector<std::string> CurveRectangularHyperbola1_Impl::validInputUnitTypeforxValues() const {
      return openstudio::epmodel::CurveRectangularHyperbola1::validInputUnitTypeforxValues();
    }

    std::vector<std::string> CurveRectangularHyperbola1_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveRectangularHyperbola1::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
