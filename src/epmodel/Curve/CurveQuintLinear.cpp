/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveQuintLinear.hpp"
#include "Curve/CurveQuintLinear_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Curve_QuintLinear_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CurveQuintLinear::CurveQuintLinear(const Model& model) : Curve(CurveQuintLinear::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveQuintLinear_Impl>());
    OS_ASSERT(setCoefficient1Constant(0.0));
    OS_ASSERT(setCoefficient2v(1.0));
    OS_ASSERT(setCoefficient3w(1.0));
    OS_ASSERT(setCoefficient4x(1.0));
    OS_ASSERT(setCoefficient5y(1.0));
    OS_ASSERT(setCoefficient6z(1.0));
    OS_ASSERT(setMinimumValueofv(-100.0));
    OS_ASSERT(setMaximumValueofv(100.0));
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
    resetInputUnitTypeforv();
    resetInputUnitTypeforw();
    resetInputUnitTypeforx();
    resetInputUnitTypefory();
    resetInputUnitTypeforz();
  }

  CurveQuintLinear::CurveQuintLinear(std::shared_ptr<detail::CurveQuintLinear_Impl> impl) : Curve(std::move(impl)) {}

  IddObjectType CurveQuintLinear::iddObjectType() {
    return IddObjectType::Curve_QuintLinear;
  }

  std::vector<std::string> CurveQuintLinear::inputUnitTypeforvValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuintLinearFields::InputUnitTypeforv);
  }

  std::vector<std::string> CurveQuintLinear::inputUnitTypeforwValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuintLinearFields::InputUnitTypeforw);
  }

  std::vector<std::string> CurveQuintLinear::inputUnitTypeforxValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuintLinearFields::InputUnitTypeforx);
  }

  std::vector<std::string> CurveQuintLinear::inputUnitTypeforyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuintLinearFields::InputUnitTypefory);
  }

  std::vector<std::string> CurveQuintLinear::inputUnitTypeforzValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_QuintLinearFields::InputUnitTypeforz);
  }

  double CurveQuintLinear::coefficient1Constant() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->coefficient1Constant();
  }

  bool CurveQuintLinear::setCoefficient1Constant(double coefficient1Constant) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setCoefficient1Constant(coefficient1Constant);
  }

  double CurveQuintLinear::coefficient2v() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->coefficient2v();
  }

  bool CurveQuintLinear::setCoefficient2v(double coefficient2v) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setCoefficient2v(coefficient2v);
  }

  double CurveQuintLinear::coefficient3w() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->coefficient3w();
  }

  bool CurveQuintLinear::setCoefficient3w(double coefficient3w) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setCoefficient3w(coefficient3w);
  }

  double CurveQuintLinear::coefficient4x() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->coefficient4x();
  }

  bool CurveQuintLinear::setCoefficient4x(double coefficient4x) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setCoefficient4x(coefficient4x);
  }

  double CurveQuintLinear::coefficient5y() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->coefficient5y();
  }

  bool CurveQuintLinear::setCoefficient5y(double coefficient5y) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setCoefficient5y(coefficient5y);
  }

  double CurveQuintLinear::coefficient6z() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->coefficient6z();
  }

  bool CurveQuintLinear::setCoefficient6z(double coefficient6z) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setCoefficient6z(coefficient6z);
  }

  double CurveQuintLinear::minimumValueofv() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->minimumValueofv();
  }

  bool CurveQuintLinear::setMinimumValueofv(double minimumValueofv) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMinimumValueofv(minimumValueofv);
  }

  double CurveQuintLinear::maximumValueofv() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->maximumValueofv();
  }

  bool CurveQuintLinear::setMaximumValueofv(double maximumValueofv) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMaximumValueofv(maximumValueofv);
  }

  double CurveQuintLinear::minimumValueofw() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->minimumValueofw();
  }

  bool CurveQuintLinear::setMinimumValueofw(double minimumValueofw) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMinimumValueofw(minimumValueofw);
  }

  double CurveQuintLinear::maximumValueofw() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->maximumValueofw();
  }

  bool CurveQuintLinear::setMaximumValueofw(double maximumValueofw) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMaximumValueofw(maximumValueofw);
  }

  double CurveQuintLinear::minimumValueofx() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->minimumValueofx();
  }

  bool CurveQuintLinear::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveQuintLinear::maximumValueofx() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->maximumValueofx();
  }

  bool CurveQuintLinear::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  double CurveQuintLinear::minimumValueofy() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->minimumValueofy();
  }

  bool CurveQuintLinear::setMinimumValueofy(double minimumValueofy) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMinimumValueofy(minimumValueofy);
  }

  double CurveQuintLinear::maximumValueofy() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->maximumValueofy();
  }

  bool CurveQuintLinear::setMaximumValueofy(double maximumValueofy) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMaximumValueofy(maximumValueofy);
  }

  double CurveQuintLinear::minimumValueofz() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->minimumValueofz();
  }

  bool CurveQuintLinear::setMinimumValueofz(double minimumValueofz) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMinimumValueofz(minimumValueofz);
  }

  double CurveQuintLinear::maximumValueofz() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->maximumValueofz();
  }

  bool CurveQuintLinear::setMaximumValueofz(double maximumValueofz) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMaximumValueofz(maximumValueofz);
  }

  boost::optional<double> CurveQuintLinear::minimumCurveOutput() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->minimumCurveOutput();
  }

  bool CurveQuintLinear::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveQuintLinear::resetMinimumCurveOutput() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveQuintLinear::maximumCurveOutput() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->maximumCurveOutput();
  }

  bool CurveQuintLinear::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveQuintLinear::resetMaximumCurveOutput() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveQuintLinear::inputUnitTypeforv() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->inputUnitTypeforv();
  }

  bool CurveQuintLinear::isInputUnitTypeforvDefaulted() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->isInputUnitTypeforvDefaulted();
  }

  bool CurveQuintLinear::setInputUnitTypeforv(const std::string& inputUnitTypeforv) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setInputUnitTypeforv(inputUnitTypeforv);
  }

  void CurveQuintLinear::resetInputUnitTypeforv() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetInputUnitTypeforv();
  }

  std::string CurveQuintLinear::inputUnitTypeforw() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->inputUnitTypeforw();
  }

  bool CurveQuintLinear::isInputUnitTypeforwDefaulted() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->isInputUnitTypeforwDefaulted();
  }

  bool CurveQuintLinear::setInputUnitTypeforw(const std::string& inputUnitTypeforw) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setInputUnitTypeforw(inputUnitTypeforw);
  }

  void CurveQuintLinear::resetInputUnitTypeforw() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetInputUnitTypeforw();
  }

  std::string CurveQuintLinear::inputUnitTypeforx() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->inputUnitTypeforx();
  }

  bool CurveQuintLinear::isInputUnitTypeforxDefaulted() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->isInputUnitTypeforxDefaulted();
  }

  bool CurveQuintLinear::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
  }

  void CurveQuintLinear::resetInputUnitTypeforx() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetInputUnitTypeforx();
  }

  std::string CurveQuintLinear::inputUnitTypefory() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->inputUnitTypefory();
  }

  bool CurveQuintLinear::isInputUnitTypeforyDefaulted() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->isInputUnitTypeforyDefaulted();
  }

  bool CurveQuintLinear::setInputUnitTypefory(const std::string& inputUnitTypefory) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setInputUnitTypefory(inputUnitTypefory);
  }

  void CurveQuintLinear::resetInputUnitTypefory() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetInputUnitTypefory();
  }

  std::string CurveQuintLinear::inputUnitTypeforz() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->inputUnitTypeforz();
  }

  bool CurveQuintLinear::isInputUnitTypeforzDefaulted() const {
    return getImpl<detail::CurveQuintLinear_Impl>()->isInputUnitTypeforzDefaulted();
  }

  bool CurveQuintLinear::setInputUnitTypeforz(const std::string& inputUnitTypeforz) {
    return getImpl<detail::CurveQuintLinear_Impl>()->setInputUnitTypeforz(inputUnitTypeforz);
  }

  void CurveQuintLinear::resetInputUnitTypeforz() {
    getImpl<detail::CurveQuintLinear_Impl>()->resetInputUnitTypeforz();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveQuintLinear_Impl::coefficient1Constant() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::Coefficient1Constant, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::coefficient2v() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::Coefficient2v, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::coefficient3w() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::Coefficient3w, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::coefficient4x() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::Coefficient4x, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::coefficient5y() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::Coefficient5y, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::coefficient6z() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::Coefficient6z, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::minimumValueofv() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MinimumValueofv, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::maximumValueofv() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MaximumValueofv, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::minimumValueofw() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MinimumValueofw, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::maximumValueofw() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MaximumValueofw, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::minimumValueofy() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MinimumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::maximumValueofy() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MaximumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::minimumValueofz() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MinimumValueofz, true);
      OS_ASSERT(value);
      return *value;
    }

    double CurveQuintLinear_Impl::maximumValueofz() const {
      const auto value = getDouble(openstudio::Curve_QuintLinearFields::MaximumValueofz, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> CurveQuintLinear_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_QuintLinearFields::MinimumCurveOutput, true);
    }

    boost::optional<double> CurveQuintLinear_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_QuintLinearFields::MaximumCurveOutput, true);
    }

    std::string CurveQuintLinear_Impl::inputUnitTypeforv() const {
      const auto value = getString(openstudio::Curve_QuintLinearFields::InputUnitTypeforv, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuintLinear_Impl::isInputUnitTypeforvDefaulted() const {
      return isEmpty(openstudio::Curve_QuintLinearFields::InputUnitTypeforv);
    }

    std::string CurveQuintLinear_Impl::inputUnitTypeforw() const {
      const auto value = getString(openstudio::Curve_QuintLinearFields::InputUnitTypeforw, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuintLinear_Impl::isInputUnitTypeforwDefaulted() const {
      return isEmpty(openstudio::Curve_QuintLinearFields::InputUnitTypeforw);
    }

    std::string CurveQuintLinear_Impl::inputUnitTypeforx() const {
      const auto value = getString(openstudio::Curve_QuintLinearFields::InputUnitTypeforx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuintLinear_Impl::isInputUnitTypeforxDefaulted() const {
      return isEmpty(openstudio::Curve_QuintLinearFields::InputUnitTypeforx);
    }

    std::string CurveQuintLinear_Impl::inputUnitTypefory() const {
      const auto value = getString(openstudio::Curve_QuintLinearFields::InputUnitTypefory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuintLinear_Impl::isInputUnitTypeforyDefaulted() const {
      return isEmpty(openstudio::Curve_QuintLinearFields::InputUnitTypefory);
    }

    std::string CurveQuintLinear_Impl::inputUnitTypeforz() const {
      const auto value = getString(openstudio::Curve_QuintLinearFields::InputUnitTypeforz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveQuintLinear_Impl::isInputUnitTypeforzDefaulted() const {
      return isEmpty(openstudio::Curve_QuintLinearFields::InputUnitTypeforz);
    }

    bool CurveQuintLinear_Impl::setCoefficient1Constant(double coefficient1Constant) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::Coefficient1Constant, coefficient1Constant);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setCoefficient2v(double coefficient2v) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::Coefficient2v, coefficient2v);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setCoefficient3w(double coefficient3w) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::Coefficient3w, coefficient3w);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setCoefficient4x(double coefficient4x) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::Coefficient4x, coefficient4x);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setCoefficient5y(double coefficient5y) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::Coefficient5y, coefficient5y);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setCoefficient6z(double coefficient6z) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::Coefficient6z, coefficient6z);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMinimumValueofv(double minimumValueofv) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MinimumValueofv, minimumValueofv);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMaximumValueofv(double maximumValueofv) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MaximumValueofv, maximumValueofv);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMinimumValueofw(double minimumValueofw) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MinimumValueofw, minimumValueofw);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMaximumValueofw(double maximumValueofw) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MaximumValueofw, maximumValueofw);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMinimumValueofy(double minimumValueofy) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MinimumValueofy, minimumValueofy);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMaximumValueofy(double maximumValueofy) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MaximumValueofy, maximumValueofy);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMinimumValueofz(double minimumValueofz) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MinimumValueofz, minimumValueofz);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMaximumValueofz(double maximumValueofz) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MaximumValueofz, maximumValueofz);
      OS_ASSERT(result);
      return result;
    }

    bool CurveQuintLinear_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuintLinear_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::MinimumCurveOutput, ""));
    }

    bool CurveQuintLinear_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_QuintLinearFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveQuintLinear_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::MaximumCurveOutput, ""));
    }

    bool CurveQuintLinear_Impl::setInputUnitTypeforv(const std::string& inputUnitTypeforv) {
      return setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforv, inputUnitTypeforv);
    }

    void CurveQuintLinear_Impl::resetInputUnitTypeforv() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforv, ""));
    }

    bool CurveQuintLinear_Impl::setInputUnitTypeforw(const std::string& inputUnitTypeforw) {
      return setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforw, inputUnitTypeforw);
    }

    void CurveQuintLinear_Impl::resetInputUnitTypeforw() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforw, ""));
    }

    bool CurveQuintLinear_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
      return setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforx, inputUnitTypeforx);
    }

    void CurveQuintLinear_Impl::resetInputUnitTypeforx() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforx, ""));
    }

    bool CurveQuintLinear_Impl::setInputUnitTypefory(const std::string& inputUnitTypefory) {
      return setString(openstudio::Curve_QuintLinearFields::InputUnitTypefory, inputUnitTypefory);
    }

    void CurveQuintLinear_Impl::resetInputUnitTypefory() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::InputUnitTypefory, ""));
    }

    bool CurveQuintLinear_Impl::setInputUnitTypeforz(const std::string& inputUnitTypeforz) {
      return setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforz, inputUnitTypeforz);
    }

    void CurveQuintLinear_Impl::resetInputUnitTypeforz() {
      OS_ASSERT(setString(openstudio::Curve_QuintLinearFields::InputUnitTypeforz, ""));
    }

    std::vector<std::string> CurveQuintLinear_Impl::inputUnitTypeforvValues() const {
      return openstudio::epmodel::CurveQuintLinear::inputUnitTypeforvValues();
    }

    std::vector<std::string> CurveQuintLinear_Impl::inputUnitTypeforwValues() const {
      return openstudio::epmodel::CurveQuintLinear::inputUnitTypeforwValues();
    }

    std::vector<std::string> CurveQuintLinear_Impl::inputUnitTypeforxValues() const {
      return openstudio::epmodel::CurveQuintLinear::inputUnitTypeforxValues();
    }

    std::vector<std::string> CurveQuintLinear_Impl::inputUnitTypeforyValues() const {
      return openstudio::epmodel::CurveQuintLinear::inputUnitTypeforyValues();
    }

    std::vector<std::string> CurveQuintLinear_Impl::inputUnitTypeforzValues() const {
      return openstudio::epmodel::CurveQuintLinear::inputUnitTypeforzValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
