/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostVariable.hpp"
#include "UtilityCostVariable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/UtilityCost_Variable_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  UtilityCostVariable::UtilityCostVariable(const Model& model) : ModelObject(UtilityCostVariable::iddObjectType(), model) {}

  UtilityCostVariable::UtilityCostVariable(std::shared_ptr<detail::UtilityCostVariable_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostVariable::iddObjectType() {
    return IddObjectType::UtilityCost_Variable;
  }

  std::vector<std::string> UtilityCostVariable::variableTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_VariableFields::VariableType);
  }

  std::string UtilityCostVariable::variableType() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->variableType();
  }

  bool UtilityCostVariable::isVariableTypeDefaulted() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->isVariableTypeDefaulted();
  }

  boost::optional<double> UtilityCostVariable::januaryValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->januaryValue();
  }

  boost::optional<double> UtilityCostVariable::februaryValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->februaryValue();
  }

  boost::optional<double> UtilityCostVariable::marchValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->marchValue();
  }

  boost::optional<double> UtilityCostVariable::aprilValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->aprilValue();
  }

  boost::optional<double> UtilityCostVariable::mayValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->mayValue();
  }

  boost::optional<double> UtilityCostVariable::juneValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->juneValue();
  }

  boost::optional<double> UtilityCostVariable::julyValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->julyValue();
  }

  boost::optional<double> UtilityCostVariable::augustValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->augustValue();
  }

  boost::optional<double> UtilityCostVariable::septemberValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->septemberValue();
  }

  boost::optional<double> UtilityCostVariable::octoberValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->octoberValue();
  }

  boost::optional<double> UtilityCostVariable::novemberValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->novemberValue();
  }

  boost::optional<double> UtilityCostVariable::decemberValue() const {
    return getImpl<detail::UtilityCostVariable_Impl>()->decemberValue();
  }

  bool UtilityCostVariable::setVariableType(const std::string& variableType) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setVariableType(variableType);
  }

  void UtilityCostVariable::resetVariableType() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetVariableType();
  }

  bool UtilityCostVariable::setJanuaryValue(double januaryValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setJanuaryValue(januaryValue);
  }

  void UtilityCostVariable::resetJanuaryValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetJanuaryValue();
  }

  bool UtilityCostVariable::setFebruaryValue(double februaryValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setFebruaryValue(februaryValue);
  }

  void UtilityCostVariable::resetFebruaryValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetFebruaryValue();
  }

  bool UtilityCostVariable::setMarchValue(double marchValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setMarchValue(marchValue);
  }

  void UtilityCostVariable::resetMarchValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetMarchValue();
  }

  bool UtilityCostVariable::setAprilValue(double aprilValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setAprilValue(aprilValue);
  }

  void UtilityCostVariable::resetAprilValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetAprilValue();
  }

  bool UtilityCostVariable::setMayValue(double mayValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setMayValue(mayValue);
  }

  void UtilityCostVariable::resetMayValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetMayValue();
  }

  bool UtilityCostVariable::setJuneValue(double juneValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setJuneValue(juneValue);
  }

  void UtilityCostVariable::resetJuneValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetJuneValue();
  }

  bool UtilityCostVariable::setJulyValue(double julyValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setJulyValue(julyValue);
  }

  void UtilityCostVariable::resetJulyValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetJulyValue();
  }

  bool UtilityCostVariable::setAugustValue(double augustValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setAugustValue(augustValue);
  }

  void UtilityCostVariable::resetAugustValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetAugustValue();
  }

  bool UtilityCostVariable::setSeptemberValue(double septemberValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setSeptemberValue(septemberValue);
  }

  void UtilityCostVariable::resetSeptemberValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetSeptemberValue();
  }

  bool UtilityCostVariable::setOctoberValue(double octoberValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setOctoberValue(octoberValue);
  }

  void UtilityCostVariable::resetOctoberValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetOctoberValue();
  }

  bool UtilityCostVariable::setNovemberValue(double novemberValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setNovemberValue(novemberValue);
  }

  void UtilityCostVariable::resetNovemberValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetNovemberValue();
  }

  bool UtilityCostVariable::setDecemberValue(double decemberValue) {
    return getImpl<detail::UtilityCostVariable_Impl>()->setDecemberValue(decemberValue);
  }

  void UtilityCostVariable::resetDecemberValue() {
    getImpl<detail::UtilityCostVariable_Impl>()->resetDecemberValue();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      bool setAlphaField(UtilityCostVariable_Impl* impl, unsigned fieldIndex, const std::string& value) {
        if (impl->setString(fieldIndex, value)) {
          return true;
        }
        return impl->setString(fieldIndex, value, false);
      }
    }  // namespace

    std::string UtilityCostVariable_Impl::variableType() const {
      const auto value = getString(openstudio::UtilityCost_VariableFields::VariableType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostVariable_Impl::isVariableTypeDefaulted() const {
      return isEmpty(openstudio::UtilityCost_VariableFields::VariableType);
    }

    boost::optional<double> UtilityCostVariable_Impl::januaryValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::JanuaryValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::februaryValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::FebruaryValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::marchValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::MarchValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::aprilValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::AprilValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::mayValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::MayValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::juneValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::JuneValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::julyValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::JulyValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::augustValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::AugustValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::septemberValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::SeptemberValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::octoberValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::OctoberValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::novemberValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::NovemberValue, true);
    }

    boost::optional<double> UtilityCostVariable_Impl::decemberValue() const {
      return getDouble(openstudio::UtilityCost_VariableFields::DecemberValue, true);
    }

    bool UtilityCostVariable_Impl::setVariableType(const std::string& variableType) {
      return setAlphaField(this, openstudio::UtilityCost_VariableFields::VariableType, variableType);
    }

    void UtilityCostVariable_Impl::resetVariableType() {
      OS_ASSERT(setString(openstudio::UtilityCost_VariableFields::VariableType, ""));
    }

    bool UtilityCostVariable_Impl::setJanuaryValue(double januaryValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::JanuaryValue, januaryValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetJanuaryValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::JanuaryValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setFebruaryValue(double februaryValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::FebruaryValue, februaryValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetFebruaryValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::FebruaryValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setMarchValue(double marchValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::MarchValue, marchValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetMarchValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::MarchValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setAprilValue(double aprilValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::AprilValue, aprilValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetAprilValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::AprilValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setMayValue(double mayValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::MayValue, mayValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetMayValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::MayValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setJuneValue(double juneValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::JuneValue, juneValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetJuneValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::JuneValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setJulyValue(double julyValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::JulyValue, julyValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetJulyValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::JulyValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setAugustValue(double augustValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::AugustValue, augustValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetAugustValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::AugustValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setSeptemberValue(double septemberValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::SeptemberValue, septemberValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetSeptemberValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::SeptemberValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setOctoberValue(double octoberValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::OctoberValue, octoberValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetOctoberValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::OctoberValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setNovemberValue(double novemberValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::NovemberValue, novemberValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetNovemberValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::NovemberValue, "");
      OS_ASSERT(result);
    }

    bool UtilityCostVariable_Impl::setDecemberValue(double decemberValue) {
      const bool result = setDouble(openstudio::UtilityCost_VariableFields::DecemberValue, decemberValue);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostVariable_Impl::resetDecemberValue() {
      const bool result = setString(openstudio::UtilityCost_VariableFields::DecemberValue, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
