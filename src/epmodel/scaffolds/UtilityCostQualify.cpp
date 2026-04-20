/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostQualify.hpp"
#include "UtilityCostQualify_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/UtilityCost_Qualify_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  UtilityCostQualify::UtilityCostQualify(const Model& model) : ModelObject(UtilityCostQualify::iddObjectType(), model) {}

  UtilityCostQualify::UtilityCostQualify(std::shared_ptr<detail::UtilityCostQualify_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostQualify::iddObjectType() {
    return IddObjectType::UtilityCost_Qualify;
  }

  std::vector<std::string> UtilityCostQualify::qualifyTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_QualifyFields::QualifyType);
  }

  std::vector<std::string> UtilityCostQualify::seasonValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_QualifyFields::Season);
  }

  std::vector<std::string> UtilityCostQualify::thresholdTestValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_QualifyFields::ThresholdTest);
  }

  std::string UtilityCostQualify::variableName() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->variableName();
  }

  bool UtilityCostQualify::setVariableName(const std::string& variableName) {
    return getImpl<detail::UtilityCostQualify_Impl>()->setVariableName(variableName);
  }

  std::string UtilityCostQualify::qualifyType() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->qualifyType();
  }

  bool UtilityCostQualify::setQualifyType(const std::string& qualifyType) {
    return getImpl<detail::UtilityCostQualify_Impl>()->setQualifyType(qualifyType);
  }

  std::string UtilityCostQualify::thresholdValueorVariableName() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->thresholdValueorVariableName();
  }

  bool UtilityCostQualify::setThresholdValueorVariableName(const std::string& thresholdValueorVariableName) {
    return getImpl<detail::UtilityCostQualify_Impl>()->setThresholdValueorVariableName(thresholdValueorVariableName);
  }

  std::string UtilityCostQualify::season() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->season();
  }

  bool UtilityCostQualify::setSeason(const std::string& season) {
    return getImpl<detail::UtilityCostQualify_Impl>()->setSeason(season);
  }

  bool UtilityCostQualify::isSeasonDefaulted() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->isSeasonDefaulted();
  }

  void UtilityCostQualify::resetSeason() {
    getImpl<detail::UtilityCostQualify_Impl>()->resetSeason();
  }

  std::string UtilityCostQualify::thresholdTest() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->thresholdTest();
  }

  bool UtilityCostQualify::setThresholdTest(const std::string& thresholdTest) {
    return getImpl<detail::UtilityCostQualify_Impl>()->setThresholdTest(thresholdTest);
  }

  int UtilityCostQualify::numberOfMonths() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->numberOfMonths();
  }

  bool UtilityCostQualify::setNumberOfMonths(int numberOfMonths) {
    return getImpl<detail::UtilityCostQualify_Impl>()->setNumberOfMonths(numberOfMonths);
  }

  bool UtilityCostQualify::isNumberOfMonthsDefaulted() const {
    return getImpl<detail::UtilityCostQualify_Impl>()->isNumberOfMonthsDefaulted();
  }

  void UtilityCostQualify::resetNumberOfMonths() {
    getImpl<detail::UtilityCostQualify_Impl>()->resetNumberOfMonths();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      bool setAlphaField(UtilityCostQualify_Impl* impl, unsigned fieldIndex, const std::string& value) {
        if (impl->setString(fieldIndex, value)) {
          return true;
        }
        return impl->setString(fieldIndex, value, false);
      }
    }  // namespace

    std::string UtilityCostQualify_Impl::variableName() const {
      const auto value = getString(openstudio::UtilityCost_QualifyFields::VariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostQualify_Impl::setVariableName(const std::string& variableName) {
      return setAlphaField(this, openstudio::UtilityCost_QualifyFields::VariableName, variableName);
    }

    std::string UtilityCostQualify_Impl::qualifyType() const {
      const auto value = getString(openstudio::UtilityCost_QualifyFields::QualifyType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostQualify_Impl::setQualifyType(const std::string& qualifyType) {
      return setAlphaField(this, openstudio::UtilityCost_QualifyFields::QualifyType, qualifyType);
    }

    std::string UtilityCostQualify_Impl::thresholdValueorVariableName() const {
      const auto value = getString(openstudio::UtilityCost_QualifyFields::ThresholdValueorVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostQualify_Impl::setThresholdValueorVariableName(const std::string& thresholdValueorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_QualifyFields::ThresholdValueorVariableName, thresholdValueorVariableName);
    }

    std::string UtilityCostQualify_Impl::season() const {
      const auto value = getString(openstudio::UtilityCost_QualifyFields::Season, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostQualify_Impl::setSeason(const std::string& season) {
      return setAlphaField(this, openstudio::UtilityCost_QualifyFields::Season, season);
    }

    bool UtilityCostQualify_Impl::isSeasonDefaulted() const {
      return isEmpty(openstudio::UtilityCost_QualifyFields::Season);
    }

    void UtilityCostQualify_Impl::resetSeason() {
      OS_ASSERT(setString(openstudio::UtilityCost_QualifyFields::Season, ""));
    }

    std::string UtilityCostQualify_Impl::thresholdTest() const {
      const auto value = getString(openstudio::UtilityCost_QualifyFields::ThresholdTest, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostQualify_Impl::setThresholdTest(const std::string& thresholdTest) {
      return setAlphaField(this, openstudio::UtilityCost_QualifyFields::ThresholdTest, thresholdTest);
    }

    int UtilityCostQualify_Impl::numberOfMonths() const {
      const auto value = getInt(openstudio::UtilityCost_QualifyFields::NumberofMonths, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostQualify_Impl::setNumberOfMonths(int numberOfMonths) {
      return setInt(openstudio::UtilityCost_QualifyFields::NumberofMonths, numberOfMonths);
    }

    bool UtilityCostQualify_Impl::isNumberOfMonthsDefaulted() const {
      return isEmpty(openstudio::UtilityCost_QualifyFields::NumberofMonths);
    }

    void UtilityCostQualify_Impl::resetNumberOfMonths() {
      const bool result = setString(openstudio::UtilityCost_QualifyFields::NumberofMonths, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
