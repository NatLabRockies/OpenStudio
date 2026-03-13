/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneAirHeatBalanceAlgorithm.hpp"
#include "ZoneAirHeatBalanceAlgorithm_Impl.hpp"

#include "Model.hpp"

#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneAirHeatBalanceAlgorithm_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneAirHeatBalanceAlgorithm::ZoneAirHeatBalanceAlgorithm(const Model& model) : ModelObject(ZoneAirHeatBalanceAlgorithm::iddObjectType(), model) {}

  ZoneAirHeatBalanceAlgorithm::ZoneAirHeatBalanceAlgorithm(std::shared_ptr<detail::ZoneAirHeatBalanceAlgorithm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneAirHeatBalanceAlgorithm::iddObjectType() {
    return IddObjectType::ZoneAirHeatBalanceAlgorithm;
  }

  std::vector<std::string> ZoneAirHeatBalanceAlgorithm::validAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneAirHeatBalanceAlgorithmFields::Algorithm);
  }

  std::string ZoneAirHeatBalanceAlgorithm::algorithm() const {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->algorithm();
  }

  bool ZoneAirHeatBalanceAlgorithm::isAlgorithmDefaulted() const {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->isAlgorithmDefaulted();
  }

  bool ZoneAirHeatBalanceAlgorithm::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->setAlgorithm(algorithm);
  }

  void ZoneAirHeatBalanceAlgorithm::resetAlgorithm() {
    getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->resetAlgorithm();
  }

  bool ZoneAirHeatBalanceAlgorithm::doSpaceHeatBalanceforSizing() const {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->doSpaceHeatBalanceforSizing();
  }

  bool ZoneAirHeatBalanceAlgorithm::isDoSpaceHeatBalanceforSizingDefaulted() const {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->isDoSpaceHeatBalanceforSizingDefaulted();
  }

  bool ZoneAirHeatBalanceAlgorithm::setDoSpaceHeatBalanceforSizing(bool doSpaceHeatBalanceforSizing) {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->setDoSpaceHeatBalanceforSizing(doSpaceHeatBalanceforSizing);
  }

  void ZoneAirHeatBalanceAlgorithm::resetDoSpaceHeatBalanceforSizing() {
    getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->resetDoSpaceHeatBalanceforSizing();
  }

  bool ZoneAirHeatBalanceAlgorithm::doSpaceHeatBalanceforSimulation() const {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->doSpaceHeatBalanceforSimulation();
  }

  bool ZoneAirHeatBalanceAlgorithm::isDoSpaceHeatBalanceforSimulationDefaulted() const {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->isDoSpaceHeatBalanceforSimulationDefaulted();
  }

  bool ZoneAirHeatBalanceAlgorithm::setDoSpaceHeatBalanceforSimulation(bool doSpaceHeatBalanceforSimulation) {
    return getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->setDoSpaceHeatBalanceforSimulation(doSpaceHeatBalanceforSimulation);
  }

  void ZoneAirHeatBalanceAlgorithm::resetDoSpaceHeatBalanceforSimulation() {
    getImpl<detail::ZoneAirHeatBalanceAlgorithm_Impl>()->resetDoSpaceHeatBalanceforSimulation();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {

  namespace {

    bool getBooleanFieldValue(const detail::ModelObject_Impl& impl, int fieldIndex) {
      const auto value = impl.getString(fieldIndex, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool setBooleanFieldValue(detail::ModelObject_Impl& impl, int fieldIndex, bool value) {
      return impl.setString(fieldIndex, value ? "Yes" : "No");
    }

  }  // namespace

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneAirHeatBalanceAlgorithm_Impl::algorithm() const {
      const auto value = getString(openstudio::ZoneAirHeatBalanceAlgorithmFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::ZoneAirHeatBalanceAlgorithmFields::Algorithm);
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::doSpaceHeatBalanceforSizing() const {
      return getBooleanFieldValue(*this, openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSizing);
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::isDoSpaceHeatBalanceforSizingDefaulted() const {
      return isEmpty(openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSizing);
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::doSpaceHeatBalanceforSimulation() const {
      return getBooleanFieldValue(*this, openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSimulation);
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::isDoSpaceHeatBalanceforSimulationDefaulted() const {
      return isEmpty(openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSimulation);
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::ZoneAirHeatBalanceAlgorithmFields::Algorithm, algorithm);
    }

    void ZoneAirHeatBalanceAlgorithm_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::ZoneAirHeatBalanceAlgorithmFields::Algorithm, ""));
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::setDoSpaceHeatBalanceforSizing(bool doSpaceHeatBalanceforSizing) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSizing, doSpaceHeatBalanceforSizing);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirHeatBalanceAlgorithm_Impl::resetDoSpaceHeatBalanceforSizing() {
      OS_ASSERT(setString(openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSizing, ""));
    }

    bool ZoneAirHeatBalanceAlgorithm_Impl::setDoSpaceHeatBalanceforSimulation(bool doSpaceHeatBalanceforSimulation) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSimulation, doSpaceHeatBalanceforSimulation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneAirHeatBalanceAlgorithm_Impl::resetDoSpaceHeatBalanceforSimulation() {
      OS_ASSERT(setString(openstudio::ZoneAirHeatBalanceAlgorithmFields::DoSpaceHeatBalanceforSimulation, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
