/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveQuadLinear.hpp"
#include "Curve/CurveQuadLinear_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_QuadLinear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveQuadLinear::CurveQuadLinear(const Model& model) : ModelObject(CurveQuadLinear::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveQuadLinear_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2w(1.0));
    OS_ASSERT(setCoefficient3x(1.0));
    OS_ASSERT(setCoefficient4y(1.0));
    OS_ASSERT(setCoefficient5z(1.0));
    OS_ASSERT(setMinimumValueofw(-100.0));
    OS_ASSERT(setMaximumValueofw(100.0));
    OS_ASSERT(setMinimumValueofx(-100.0));
    OS_ASSERT(setMaximumValueofx(100.0));
    OS_ASSERT(setMinimumValueofy(0.0));
    OS_ASSERT(setMaximumValueofy(100.0));
    OS_ASSERT(setMinimumValueofz(0.0));
    OS_ASSERT(setMaximumValueofz(100.0));
    resetMinimumCurveOutput();
    resetMaximumCurveOutput();
    resetInputUnitTypeforw();
    resetInputUnitTypeforx();
    resetInputUnitTypefory();
    resetInputUnitTypeforz();
  }

  CurveQuadLinear::CurveQuadLinear(std::shared_ptr<detail::CurveQuadLinear_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType CurveQuadLinear::iddObjectType() {
    return IddObjectType::Curve_QuadLinear;
  }

  std::vector<std::string> CurveQuadLinear::inputUnitTypeforwValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadLinearFields::InputUnitTypeforw);
  }

  std::vector<std::string> CurveQuadLinear::inputUnitTypeforxValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadLinearFields::InputUnitTypeforx);
  }

  std::vector<std::string> CurveQuadLinear::inputUnitTypeforyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadLinearFields::InputUnitTypefory);
  }

  std::vector<std::string> CurveQuadLinear::inputUnitTypeforzValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuadLinearFields::InputUnitTypeforz);
  }

  double CurveQuadLinear::coefficient1Constant() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->coefficient1Constant();
  }

  bool CurveQuadLinear::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveQuadLinear::coefficient2w() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->coefficient2w();
  }

  bool CurveQuadLinear::setCoefficient2w(double coefficient2w) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setCoefficient2w(coefficient2w);
  }

  double CurveQuadLinear::coefficient3x() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->coefficient3x();
  }

  bool CurveQuadLinear::setCoefficient3x(double coefficient3x) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setCoefficient3x(coefficient3x);
  }

  double CurveQuadLinear::coefficient4y() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->coefficient4y();
  }

  bool CurveQuadLinear::setCoefficient4y(double coefficient4y) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setCoefficient4y(coefficient4y);
  }

  double CurveQuadLinear::coefficient5z() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->coefficient5z();
  }

  bool CurveQuadLinear::setCoefficient5z(double coefficient5z) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setCoefficient5z(coefficient5z);
  }

  double CurveQuadLinear::minimumValueofw() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->minimumValueofw();
  }

  bool CurveQuadLinear::setMinimumValueofw(double minimumValueofw) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMinimumValueofw(minimumValueofw);
  }

  double CurveQuadLinear::maximumValueofw() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->maximumValueofw();
  }

  bool CurveQuadLinear::setMaximumValueofw(double maximumValueofw) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMaximumValueofw(maximumValueofw);
  }

  double CurveQuadLinear::minimumValueofx() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->minimumValueofx();
  }

  bool CurveQuadLinear::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveQuadLinear::maximumValueofx() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->maximumValueofx();
  }

  bool CurveQuadLinear::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  double CurveQuadLinear::minimumValueofy() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->minimumValueofy();
  }

  bool CurveQuadLinear::setMinimumValueofy(double minimumValueofy) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMinimumValueofy(minimumValueofy);
  }

  double CurveQuadLinear::maximumValueofy() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->maximumValueofy();
  }

  bool CurveQuadLinear::setMaximumValueofy(double maximumValueofy) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMaximumValueofy(maximumValueofy);
  }

  double CurveQuadLinear::minimumValueofz() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->minimumValueofz();
  }

  bool CurveQuadLinear::setMinimumValueofz(double minimumValueofz) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMinimumValueofz(minimumValueofz);
  }

  double CurveQuadLinear::maximumValueofz() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->maximumValueofz();
  }

  bool CurveQuadLinear::setMaximumValueofz(double maximumValueofz) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMaximumValueofz(maximumValueofz);
  }

  boost::optional<double> CurveQuadLinear::minimumCurveOutput() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->minimumCurveOutput();
  }

  bool CurveQuadLinear::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveQuadLinear::resetMinimumCurveOutput() {
    getImpl<detail::CurveQuadLinear_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveQuadLinear::maximumCurveOutput() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->maximumCurveOutput();
  }

  bool CurveQuadLinear::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveQuadLinear::resetMaximumCurveOutput() {
    getImpl<detail::CurveQuadLinear_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveQuadLinear::inputUnitTypeforw() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->inputUnitTypeforw();
  }

  bool CurveQuadLinear::isInputUnitTypeforwDefaulted() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->isInputUnitTypeforwDefaulted();
  }

  bool CurveQuadLinear::setInputUnitTypeforw(const std::string& inputUnitTypeforw) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setInputUnitTypeforw(inputUnitTypeforw);
  }

  void CurveQuadLinear::resetInputUnitTypeforw() {
    getImpl<detail::CurveQuadLinear_Impl>()->resetInputUnitTypeforw();
  }

  std::string CurveQuadLinear::inputUnitTypeforx() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->inputUnitTypeforx();
  }

  bool CurveQuadLinear::isInputUnitTypeforxDefaulted() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->isInputUnitTypeforxDefaulted();
  }

  bool CurveQuadLinear::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
  }

  void CurveQuadLinear::resetInputUnitTypeforx() {
    getImpl<detail::CurveQuadLinear_Impl>()->resetInputUnitTypeforx();
  }

  std::string CurveQuadLinear::inputUnitTypefory() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->inputUnitTypefory();
  }

  bool CurveQuadLinear::isInputUnitTypeforyDefaulted() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->isInputUnitTypeforyDefaulted();
  }

  bool CurveQuadLinear::setInputUnitTypefory(const std::string& inputUnitTypefory) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setInputUnitTypefory(inputUnitTypefory);
  }

  void CurveQuadLinear::resetInputUnitTypefory() {
    getImpl<detail::CurveQuadLinear_Impl>()->resetInputUnitTypefory();
  }

  std::string CurveQuadLinear::inputUnitTypeforz() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->inputUnitTypeforz();
  }

  bool CurveQuadLinear::isInputUnitTypeforzDefaulted() const {
    return getImpl<detail::CurveQuadLinear_Impl>()->isInputUnitTypeforzDefaulted();
  }

  bool CurveQuadLinear::setInputUnitTypeforz(const std::string& inputUnitTypeforz) {
    return getImpl<detail::CurveQuadLinear_Impl>()->setInputUnitTypeforz(inputUnitTypeforz);
  }

  void CurveQuadLinear::resetInputUnitTypeforz() {
    getImpl<detail::CurveQuadLinear_Impl>()->resetInputUnitTypeforz();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveQuadLinear_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::coefficient2w() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::Coefficient2w, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setCoefficient2w(double coefficient2w) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::Coefficient2w, coefficient2w);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::coefficient3x() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::Coefficient3x, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setCoefficient3x(double coefficient3x) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::Coefficient3x, coefficient3x);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::coefficient4y() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::Coefficient4y, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setCoefficient4y(double coefficient4y) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::Coefficient4y, coefficient4y);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::coefficient5z() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::Coefficient5z, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setCoefficient5z(double coefficient5z) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::Coefficient5z, coefficient5z);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::minimumValueofw() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MinimumValueofw, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMinimumValueofw(double minimumValueofw) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MinimumValueofw, minimumValueofw);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::maximumValueofw() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MaximumValueofw, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMaximumValueofw(double maximumValueofw) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MaximumValueofw, maximumValueofw);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::minimumValueofy() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MinimumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMinimumValueofy(double minimumValueofy) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MinimumValueofy, minimumValueofy);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::maximumValueofy() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MaximumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMaximumValueofy(double maximumValueofy) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MaximumValueofy, maximumValueofy);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::minimumValueofz() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MinimumValueofz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMinimumValueofz(double minimumValueofz) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MinimumValueofz, minimumValueofz);
      OS_ASSERT(result);
      return result;
    }

    double CurveQuadLinear_Impl::maximumValueofz() const {
      const auto value = getDouble(openstudio::Curve_QuadLinearFields::MaximumValueofz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::setMaximumValueofz(double maximumValueofz) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MaximumValueofz, maximumValueofz);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveQuadLinear_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_QuadLinearFields::MinimumCurveOutput, true);
    }

    bool CurveQuadLinear_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuadLinear_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuadLinearFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveQuadLinear_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_QuadLinearFields::MaximumCurveOutput, true);
    }

    bool CurveQuadLinear_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuadLinearFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuadLinear_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuadLinearFields::MaximumCurveOutput, ""));
    }

    std::string CurveQuadLinear_Impl::inputUnitTypeforw() const {
      const auto value = getString(openstudio::Curve_QuadLinearFields::InputUnitTypeforw, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::isInputUnitTypeforwDefaulted() const {
      return isEmpty(openstudio::Curve_QuadLinearFields::InputUnitTypeforw);
    }

    bool CurveQuadLinear_Impl::setInputUnitTypeforw(const std::string& inputUnitTypeforw) {
      return setString(openstudio::Curve_QuadLinearFields::InputUnitTypeforw, inputUnitTypeforw);
    }

    void CurveQuadLinear_Impl::resetInputUnitTypeforw() {
      OS_ASSERT(setString(openstudio::Curve_QuadLinearFields::InputUnitTypeforw, ""));
    }

    std::vector<std::string> CurveQuadLinear_Impl::inputUnitTypeforwValues() const {
      return openstudio::epmodel::CurveQuadLinear::inputUnitTypeforwValues();
    }

    std::string CurveQuadLinear_Impl::inputUnitTypeforx() const {
      const auto value = getString(openstudio::Curve_QuadLinearFields::InputUnitTypeforx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::isInputUnitTypeforxDefaulted() const {
      return isEmpty(openstudio::Curve_QuadLinearFields::InputUnitTypeforx);
    }

    bool CurveQuadLinear_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
      return setString(openstudio::Curve_QuadLinearFields::InputUnitTypeforx, inputUnitTypeforx);
    }

    void CurveQuadLinear_Impl::resetInputUnitTypeforx() {
      OS_ASSERT(setString(openstudio::Curve_QuadLinearFields::InputUnitTypeforx, ""));
    }

    std::vector<std::string> CurveQuadLinear_Impl::inputUnitTypeforxValues() const {
      return openstudio::epmodel::CurveQuadLinear::inputUnitTypeforxValues();
    }

    std::string CurveQuadLinear_Impl::inputUnitTypefory() const {
      const auto value = getString(openstudio::Curve_QuadLinearFields::InputUnitTypefory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::isInputUnitTypeforyDefaulted() const {
      return isEmpty(openstudio::Curve_QuadLinearFields::InputUnitTypefory);
    }

    bool CurveQuadLinear_Impl::setInputUnitTypefory(const std::string& inputUnitTypefory) {
      return setString(openstudio::Curve_QuadLinearFields::InputUnitTypefory, inputUnitTypefory);
    }

    void CurveQuadLinear_Impl::resetInputUnitTypefory() {
      OS_ASSERT(setString(openstudio::Curve_QuadLinearFields::InputUnitTypefory, ""));
    }

    std::vector<std::string> CurveQuadLinear_Impl::inputUnitTypeforyValues() const {
      return openstudio::epmodel::CurveQuadLinear::inputUnitTypeforyValues();
    }

    std::string CurveQuadLinear_Impl::inputUnitTypeforz() const {
      const auto value = getString(openstudio::Curve_QuadLinearFields::InputUnitTypeforz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuadLinear_Impl::isInputUnitTypeforzDefaulted() const {
      return isEmpty(openstudio::Curve_QuadLinearFields::InputUnitTypeforz);
    }

    bool CurveQuadLinear_Impl::setInputUnitTypeforz(const std::string& inputUnitTypeforz) {
      return setString(openstudio::Curve_QuadLinearFields::InputUnitTypeforz, inputUnitTypeforz);
    }

    void CurveQuadLinear_Impl::resetInputUnitTypeforz() {
      OS_ASSERT(setString(openstudio::Curve_QuadLinearFields::InputUnitTypeforz, ""));
    }

    std::vector<std::string> CurveQuadLinear_Impl::inputUnitTypeforzValues() const {
      return openstudio::epmodel::CurveQuadLinear::inputUnitTypeforzValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
