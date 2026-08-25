/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ConstructionBase/ConstructionAirBoundary.hpp"
#include "ConstructionBase/ConstructionAirBoundary_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Construction_AirBoundary_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  ConstructionAirBoundary::ConstructionAirBoundary(const Model& model) : ConstructionBase(ConstructionAirBoundary::iddObjectType(), model) {
    const bool ok = setSimpleMixingAirChangesPerHour(0.0);
    OS_ASSERT(ok);
  }

  ConstructionAirBoundary::ConstructionAirBoundary(std::shared_ptr<detail::ConstructionAirBoundary_Impl> impl) : ConstructionBase(std::move(impl)) {}

  IddObjectType ConstructionAirBoundary::iddObjectType() {
    return IddObjectType::Construction_AirBoundary;
  }

  std::vector<std::string> ConstructionAirBoundary::solarAndDaylightingMethodValues() {
    return {};
  }

  std::vector<std::string> ConstructionAirBoundary::radiantExchangeMethodValues() {
    return {};
  }

  std::vector<std::string> ConstructionAirBoundary::airExchangeMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Construction_AirBoundaryFields::AirExchangeMethod);
  }

  std::string ConstructionAirBoundary::solarAndDaylightingMethod() const {
    return "GroupedZones";
  }

  bool ConstructionAirBoundary::isSolarAndDaylightingMethodDefaulted() const {
    return true;
  }

  bool ConstructionAirBoundary::setSolarAndDaylightingMethod(const std::string&) {
    // Preserved legacy API: schema no longer has a mapped field for this deprecated concept.
    return false;
  }

  void ConstructionAirBoundary::resetSolarAndDaylightingMethod() {}

  std::string ConstructionAirBoundary::radiantExchangeMethod() const {
    return "GroupedZones";
  }

  bool ConstructionAirBoundary::isRadiantExchangeMethodDefaulted() const {
    return true;
  }

  bool ConstructionAirBoundary::setRadiantExchangeMethod(const std::string&) {
    // Preserved legacy API: schema no longer has a mapped field for this deprecated concept.
    return false;
  }

  void ConstructionAirBoundary::resetRadiantExchangeMethod() {}

  std::string ConstructionAirBoundary::airExchangeMethod() const {
    return getImpl<detail::ConstructionAirBoundary_Impl>()->airExchangeMethod();
  }

  bool ConstructionAirBoundary::isAirExchangeMethodDefaulted() const {
    return getImpl<detail::ConstructionAirBoundary_Impl>()->isAirExchangeMethodDefaulted();
  }

  bool ConstructionAirBoundary::setAirExchangeMethod(const std::string& airExchangeMethod) {
    return getImpl<detail::ConstructionAirBoundary_Impl>()->setAirExchangeMethod(airExchangeMethod);
  }

  void ConstructionAirBoundary::resetAirExchangeMethod() {
    getImpl<detail::ConstructionAirBoundary_Impl>()->resetAirExchangeMethod();
  }

  double ConstructionAirBoundary::simpleMixingAirChangesPerHour() const {
    return getImpl<detail::ConstructionAirBoundary_Impl>()->simpleMixingAirChangesPerHour();
  }

  bool ConstructionAirBoundary::isSimpleMixingAirChangesPerHourDefaulted() const {
    return getImpl<detail::ConstructionAirBoundary_Impl>()->isSimpleMixingAirChangesPerHourDefaulted();
  }

  bool ConstructionAirBoundary::setSimpleMixingAirChangesPerHour(double simpleMixingAirChangesPerHour) {
    return getImpl<detail::ConstructionAirBoundary_Impl>()->setSimpleMixingAirChangesPerHour(simpleMixingAirChangesPerHour);
  }

  void ConstructionAirBoundary::resetSimpleMixingAirChangesPerHour() {
    getImpl<detail::ConstructionAirBoundary_Impl>()->resetSimpleMixingAirChangesPerHour();
  }

  namespace detail {

    std::string ConstructionAirBoundary_Impl::airExchangeMethod() const {
      const auto value = getString(openstudio::Construction_AirBoundaryFields::AirExchangeMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConstructionAirBoundary_Impl::isAirExchangeMethodDefaulted() const {
      return isEmpty(openstudio::Construction_AirBoundaryFields::AirExchangeMethod);
    }

    bool ConstructionAirBoundary_Impl::setAirExchangeMethod(const std::string& airExchangeMethod) {
      const bool result = setString(openstudio::Construction_AirBoundaryFields::AirExchangeMethod, airExchangeMethod);
      return result;
    }

    void ConstructionAirBoundary_Impl::resetAirExchangeMethod() {
      OS_ASSERT(setString(openstudio::Construction_AirBoundaryFields::AirExchangeMethod, ""));
    }

    double ConstructionAirBoundary_Impl::simpleMixingAirChangesPerHour() const {
      const auto value = getDouble(openstudio::Construction_AirBoundaryFields::SimpleMixingAirChangesperHour, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConstructionAirBoundary_Impl::isSimpleMixingAirChangesPerHourDefaulted() const {
      return isEmpty(openstudio::Construction_AirBoundaryFields::SimpleMixingAirChangesperHour);
    }

    bool ConstructionAirBoundary_Impl::setSimpleMixingAirChangesPerHour(double simpleMixingAirChangesPerHour) {
      const bool result = setDouble(openstudio::Construction_AirBoundaryFields::SimpleMixingAirChangesperHour, simpleMixingAirChangesPerHour);
      return result;
    }

    void ConstructionAirBoundary_Impl::resetSimpleMixingAirChangesPerHour() {
      OS_ASSERT(setString(openstudio::Construction_AirBoundaryFields::SimpleMixingAirChangesperHour, ""));
    }
  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
