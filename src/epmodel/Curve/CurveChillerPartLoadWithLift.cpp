/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/CurveChillerPartLoadWithLift.hpp"
#include "Curve/CurveChillerPartLoadWithLift_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Curve_ChillerPartLoadWithLift_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    boost::optional<std::string> curveChillerPartLoadWithLiftDefaultString(unsigned fieldIndex) {
      const auto iddObject = IddFactory::instance().getObject(IddObjectType::Curve_ChillerPartLoadWithLift);
      if (!iddObject) {
        return boost::none;
      }

      const auto iddField = iddObject->getField(fieldIndex);
      if (!iddField || !iddField->properties().stringDefault) {
        return boost::none;
      }

      return *(iddField->properties().stringDefault);
    }

  }  // namespace

  CurveChillerPartLoadWithLift::CurveChillerPartLoadWithLift(const Model& model) : Curve(CurveChillerPartLoadWithLift::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CurveChillerPartLoadWithLift_Impl>());
    OS_ASSERT(setCoefficient1C1(0.0));
    OS_ASSERT(setCoefficient2C2(0.0));
    OS_ASSERT(setCoefficient3C3(0.0));
    OS_ASSERT(setCoefficient4C4(0.0));
    OS_ASSERT(setCoefficient5C5(0.0));
    OS_ASSERT(setCoefficient6C6(0.0));
    OS_ASSERT(setCoefficient7C7(0.0));
    OS_ASSERT(setCoefficient8C8(0.0));
    OS_ASSERT(setCoefficient9C9(0.0));
    OS_ASSERT(setCoefficient10C10(0.0));
    OS_ASSERT(setCoefficient11C11(0.0));
    OS_ASSERT(setCoefficient12C12(0.0));
    OS_ASSERT(setMinimumValueofx(0.0));
    OS_ASSERT(setMaximumValueofx(1.0));
    OS_ASSERT(setMinimumValueofy(0.0));
    OS_ASSERT(setMaximumValueofy(1.0));
    OS_ASSERT(setMinimumValueofz(0.0));
    OS_ASSERT(setMaximumValueofz(1.0));
  }

  CurveChillerPartLoadWithLift::CurveChillerPartLoadWithLift(std::shared_ptr<detail::CurveChillerPartLoadWithLift_Impl> impl)
    : Curve(std::move(impl)) {}

  IddObjectType CurveChillerPartLoadWithLift::iddObjectType() {
    return IddObjectType::Curve_ChillerPartLoadWithLift;
  }

  std::vector<std::string> CurveChillerPartLoadWithLift::validInputUnitTypeforxValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx);
  }

  std::vector<std::string> CurveChillerPartLoadWithLift::validInputUnitTypeforyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory);
  }

  std::vector<std::string> CurveChillerPartLoadWithLift::validInputUnitTypeforzValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz);
  }

  std::vector<std::string> CurveChillerPartLoadWithLift::validOutputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType);
  }

  double CurveChillerPartLoadWithLift::coefficient1C1() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient1C1();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient1C1(double coefficient1C1) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient1C1(coefficient1C1);
  }

  double CurveChillerPartLoadWithLift::coefficient2C2() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient2C2();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient2C2(double coefficient2C2) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient2C2(coefficient2C2);
  }

  double CurveChillerPartLoadWithLift::coefficient3C3() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient3C3();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient3C3(double coefficient3C3) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient3C3(coefficient3C3);
  }

  double CurveChillerPartLoadWithLift::coefficient4C4() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient4C4();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient4C4(double coefficient4C4) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient4C4(coefficient4C4);
  }

  double CurveChillerPartLoadWithLift::coefficient5C5() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient5C5();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient5C5(double coefficient5C5) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient5C5(coefficient5C5);
  }

  double CurveChillerPartLoadWithLift::coefficient6C6() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient6C6();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient6C6(double coefficient6C6) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient6C6(coefficient6C6);
  }

  double CurveChillerPartLoadWithLift::coefficient7C7() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient7C7();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient7C7(double coefficient7C7) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient7C7(coefficient7C7);
  }

  double CurveChillerPartLoadWithLift::coefficient8C8() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient8C8();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient8C8(double coefficient8C8) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient8C8(coefficient8C8);
  }

  double CurveChillerPartLoadWithLift::coefficient9C9() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient9C9();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient9C9(double coefficient9C9) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient9C9(coefficient9C9);
  }

  double CurveChillerPartLoadWithLift::coefficient10C10() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient10C10();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient10C10(double coefficient10C10) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient10C10(coefficient10C10);
  }

  double CurveChillerPartLoadWithLift::coefficient11C11() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient11C11();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient11C11(double coefficient11C11) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient11C11(coefficient11C11);
  }

  double CurveChillerPartLoadWithLift::coefficient12C12() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->coefficient12C12();
  }

  bool CurveChillerPartLoadWithLift::setCoefficient12C12(double coefficient12C12) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setCoefficient12C12(coefficient12C12);
  }

  double CurveChillerPartLoadWithLift::minimumValueofx() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->minimumValueofx();
  }

  bool CurveChillerPartLoadWithLift::setMinimumValueofx(double minimumValueofx) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMinimumValueofx(minimumValueofx);
  }

  double CurveChillerPartLoadWithLift::maximumValueofx() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->maximumValueofx();
  }

  bool CurveChillerPartLoadWithLift::setMaximumValueofx(double maximumValueofx) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMaximumValueofx(maximumValueofx);
  }

  double CurveChillerPartLoadWithLift::minimumValueofy() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->minimumValueofy();
  }

  bool CurveChillerPartLoadWithLift::setMinimumValueofy(double minimumValueofy) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMinimumValueofy(minimumValueofy);
  }

  double CurveChillerPartLoadWithLift::maximumValueofy() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->maximumValueofy();
  }

  bool CurveChillerPartLoadWithLift::setMaximumValueofy(double maximumValueofy) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMaximumValueofy(maximumValueofy);
  }

  double CurveChillerPartLoadWithLift::minimumValueofz() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->minimumValueofz();
  }

  bool CurveChillerPartLoadWithLift::setMinimumValueofz(double minimumValueofz) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMinimumValueofz(minimumValueofz);
  }

  double CurveChillerPartLoadWithLift::maximumValueofz() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->maximumValueofz();
  }

  bool CurveChillerPartLoadWithLift::setMaximumValueofz(double maximumValueofz) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMaximumValueofz(maximumValueofz);
  }

  boost::optional<double> CurveChillerPartLoadWithLift::minimumCurveOutput() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->minimumCurveOutput();
  }

  bool CurveChillerPartLoadWithLift::setMinimumCurveOutput(double minimumCurveOutput) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMinimumCurveOutput(minimumCurveOutput);
  }

  void CurveChillerPartLoadWithLift::resetMinimumCurveOutput() {
    getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->resetMinimumCurveOutput();
  }

  boost::optional<double> CurveChillerPartLoadWithLift::maximumCurveOutput() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->maximumCurveOutput();
  }

  bool CurveChillerPartLoadWithLift::setMaximumCurveOutput(double maximumCurveOutput) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setMaximumCurveOutput(maximumCurveOutput);
  }

  void CurveChillerPartLoadWithLift::resetMaximumCurveOutput() {
    getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->resetMaximumCurveOutput();
  }

  std::string CurveChillerPartLoadWithLift::inputUnitTypeforx() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->inputUnitTypeforx();
  }

  bool CurveChillerPartLoadWithLift::isInputUnitTypeforxDefaulted() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->isInputUnitTypeforxDefaulted();
  }

  bool CurveChillerPartLoadWithLift::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setInputUnitTypeforx(inputUnitTypeforx);
  }

  void CurveChillerPartLoadWithLift::resetInputUnitTypeforx() {
    getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->resetInputUnitTypeforx();
  }

  std::string CurveChillerPartLoadWithLift::inputUnitTypefory() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->inputUnitTypefory();
  }

  bool CurveChillerPartLoadWithLift::isInputUnitTypeforyDefaulted() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->isInputUnitTypeforyDefaulted();
  }

  bool CurveChillerPartLoadWithLift::setInputUnitTypefory(const std::string& inputUnitTypefory) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setInputUnitTypefory(inputUnitTypefory);
  }

  void CurveChillerPartLoadWithLift::resetInputUnitTypefory() {
    getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->resetInputUnitTypefory();
  }

  std::string CurveChillerPartLoadWithLift::inputUnitTypeforz() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->inputUnitTypeforz();
  }

  bool CurveChillerPartLoadWithLift::isInputUnitTypeforzDefaulted() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->isInputUnitTypeforzDefaulted();
  }

  bool CurveChillerPartLoadWithLift::setInputUnitTypeforz(const std::string& inputUnitTypeforz) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setInputUnitTypeforz(inputUnitTypeforz);
  }

  void CurveChillerPartLoadWithLift::resetInputUnitTypeforz() {
    getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->resetInputUnitTypeforz();
  }

  std::string CurveChillerPartLoadWithLift::outputUnitType() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->outputUnitType();
  }

  bool CurveChillerPartLoadWithLift::isOutputUnitTypeDefaulted() const {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->isOutputUnitTypeDefaulted();
  }

  bool CurveChillerPartLoadWithLift::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->setOutputUnitType(outputUnitType);
  }

  void CurveChillerPartLoadWithLift::resetOutputUnitType() {
    getImpl<detail::CurveChillerPartLoadWithLift_Impl>()->resetOutputUnitType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CurveChillerPartLoadWithLift_Impl::coefficient1C1() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient1C1, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient1C1(double coefficient1C1) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient1C1, coefficient1C1);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient2C2() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient2C2, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient2C2(double coefficient2C2) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient2C2, coefficient2C2);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient3C3() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient3C3, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient3C3(double coefficient3C3) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient3C3, coefficient3C3);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient4C4() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient4C4, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient4C4(double coefficient4C4) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient4C4, coefficient4C4);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient5C5() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient5C5, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient5C5(double coefficient5C5) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient5C5, coefficient5C5);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient6C6() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient6C6, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient6C6(double coefficient6C6) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient6C6, coefficient6C6);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient7C7() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient7C7, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient7C7(double coefficient7C7) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient7C7, coefficient7C7);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient8C8() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient8C8, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient8C8(double coefficient8C8) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient8C8, coefficient8C8);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient9C9() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient9C9, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient9C9(double coefficient9C9) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient9C9, coefficient9C9);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient10C10() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient10C10, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient10C10(double coefficient10C10) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient10C10, coefficient10C10);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient11C11() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient11C11, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient11C11(double coefficient11C11) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient11C11, coefficient11C11);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::coefficient12C12() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient12C12, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setCoefficient12C12(double coefficient12C12) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::Coefficient12C12, coefficient12C12);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::minimumValueofx() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setMinimumValueofx(double minimumValueofx) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumValueofx, minimumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::maximumValueofx() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumValueofx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setMaximumValueofx(double maximumValueofx) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumValueofx, maximumValueofx);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::minimumValueofy() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setMinimumValueofy(double minimumValueofy) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumValueofy, minimumValueofy);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::maximumValueofy() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumValueofy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setMaximumValueofy(double maximumValueofy) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumValueofy, maximumValueofy);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::minimumValueofz() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumValueofz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setMinimumValueofz(double minimumValueofz) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumValueofz, minimumValueofz);
      OS_ASSERT(result);
      return result;
    }

    double CurveChillerPartLoadWithLift_Impl::maximumValueofz() const {
      const auto value = getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumValueofz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::setMaximumValueofz(double maximumValueofz) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumValueofz, maximumValueofz);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CurveChillerPartLoadWithLift_Impl::minimumCurveOutput() const {
      return getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumCurveOutput, true);
    }

    bool CurveChillerPartLoadWithLift_Impl::setMinimumCurveOutput(double minimumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumCurveOutput, minimumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveChillerPartLoadWithLift_Impl::resetMinimumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_ChillerPartLoadWithLiftFields::MinimumCurveOutput, ""));
    }

    boost::optional<double> CurveChillerPartLoadWithLift_Impl::maximumCurveOutput() const {
      return getDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumCurveOutput, true);
    }

    bool CurveChillerPartLoadWithLift_Impl::setMaximumCurveOutput(double maximumCurveOutput) {
      const bool result = setDouble(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumCurveOutput, maximumCurveOutput);
      OS_ASSERT(result);
      return result;
    }

    void CurveChillerPartLoadWithLift_Impl::resetMaximumCurveOutput() {
      OS_ASSERT(setString(openstudio::Curve_ChillerPartLoadWithLiftFields::MaximumCurveOutput, ""));
    }

    std::string CurveChillerPartLoadWithLift_Impl::inputUnitTypeforx() const {
      const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::isInputUnitTypeforxDefaulted() const {
      if (const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx, false, true)) {
        if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveChillerPartLoadWithLift_Impl::setInputUnitTypeforx(const std::string& inputUnitTypeforx) {
      return setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx, inputUnitTypeforx);
    }

    void CurveChillerPartLoadWithLift_Impl::resetInputUnitTypeforx() {
      bool result = false;
      if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx)) {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx, *defaultValue);
      } else {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx, "");
      }
      OS_ASSERT(result);
    }

    std::string CurveChillerPartLoadWithLift_Impl::inputUnitTypefory() const {
      const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::isInputUnitTypeforyDefaulted() const {
      if (const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory, false, true)) {
        if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveChillerPartLoadWithLift_Impl::setInputUnitTypefory(const std::string& inputUnitTypefory) {
      return setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory, inputUnitTypefory);
    }

    void CurveChillerPartLoadWithLift_Impl::resetInputUnitTypefory() {
      bool result = false;
      if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory)) {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory, *defaultValue);
      } else {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory, "");
      }
      OS_ASSERT(result);
    }

    std::string CurveChillerPartLoadWithLift_Impl::inputUnitTypeforz() const {
      const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::isInputUnitTypeforzDefaulted() const {
      if (const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz, false, true)) {
        if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveChillerPartLoadWithLift_Impl::setInputUnitTypeforz(const std::string& inputUnitTypeforz) {
      return setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz, inputUnitTypeforz);
    }

    void CurveChillerPartLoadWithLift_Impl::resetInputUnitTypeforz() {
      bool result = false;
      if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz)) {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz, *defaultValue);
      } else {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz, "");
      }
      OS_ASSERT(result);
    }

    std::string CurveChillerPartLoadWithLift_Impl::outputUnitType() const {
      const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CurveChillerPartLoadWithLift_Impl::isOutputUnitTypeDefaulted() const {
      if (const auto value = getString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType, false, true)) {
        if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType)) {
          return openstudio::istringEqual(*value, *defaultValue);
        }
        return false;
      }
      return true;
    }

    bool CurveChillerPartLoadWithLift_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType, outputUnitType);
    }

    void CurveChillerPartLoadWithLift_Impl::resetOutputUnitType() {
      bool result = false;
      if (const auto defaultValue = curveChillerPartLoadWithLiftDefaultString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType)) {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType, *defaultValue);
      } else {
        result = setString(openstudio::Curve_ChillerPartLoadWithLiftFields::OutputUnitType, "");
      }
      OS_ASSERT(result);
    }

    std::vector<std::string> CurveChillerPartLoadWithLift_Impl::validInputUnitTypeforxValues() const {
      return openstudio::epmodel::CurveChillerPartLoadWithLift::validInputUnitTypeforxValues();
    }

    std::vector<std::string> CurveChillerPartLoadWithLift_Impl::validInputUnitTypeforyValues() const {
      return openstudio::epmodel::CurveChillerPartLoadWithLift::validInputUnitTypeforyValues();
    }

    std::vector<std::string> CurveChillerPartLoadWithLift_Impl::validInputUnitTypeforzValues() const {
      return openstudio::epmodel::CurveChillerPartLoadWithLift::validInputUnitTypeforzValues();
    }

    std::vector<std::string> CurveChillerPartLoadWithLift_Impl::validOutputUnitTypeValues() const {
      return openstudio::epmodel::CurveChillerPartLoadWithLift::validOutputUnitTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
