/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/HVACSystemRootFindingAlgorithm.hpp"
#include "scaffolds/HVACSystemRootFindingAlgorithm_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HVACSystemRootFindingAlgorithm_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACSystemRootFindingAlgorithm::HVACSystemRootFindingAlgorithm(const Model& model)
    : ModelObject(HVACSystemRootFindingAlgorithm::iddObjectType(), model) {}

  HVACSystemRootFindingAlgorithm::HVACSystemRootFindingAlgorithm(std::shared_ptr<detail::HVACSystemRootFindingAlgorithm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACSystemRootFindingAlgorithm::iddObjectType() {
    return IddObjectType::HVACSystemRootFindingAlgorithm;
  }

  std::vector<std::string> HVACSystemRootFindingAlgorithm::algorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACSystemRootFindingAlgorithmFields::Algorithm);
  }

  std::string HVACSystemRootFindingAlgorithm::algorithm() const {
    return getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->algorithm();
  }

  bool HVACSystemRootFindingAlgorithm::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->setAlgorithm(algorithm);
  }

  bool HVACSystemRootFindingAlgorithm::isAlgorithmDefaulted() const {
    return getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->isAlgorithmDefaulted();
  }

  void HVACSystemRootFindingAlgorithm::resetAlgorithm() {
    getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->resetAlgorithm();
  }

  int HVACSystemRootFindingAlgorithm::numberofIterationsBeforeAlgorithmSwitch() const {
    return getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->numberofIterationsBeforeAlgorithmSwitch();
  }

  bool HVACSystemRootFindingAlgorithm::setNumberofIterationsBeforeAlgorithmSwitch(int numberofIterationsBeforeAlgorithmSwitch) {
    return getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->setNumberofIterationsBeforeAlgorithmSwitch(
      numberofIterationsBeforeAlgorithmSwitch);
  }

  bool HVACSystemRootFindingAlgorithm::isNumberofIterationsBeforeAlgorithmSwitchDefaulted() const {
    return getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->isNumberofIterationsBeforeAlgorithmSwitchDefaulted();
  }

  void HVACSystemRootFindingAlgorithm::resetNumberofIterationsBeforeAlgorithmSwitch() {
    getImpl<detail::HVACSystemRootFindingAlgorithm_Impl>()->resetNumberofIterationsBeforeAlgorithmSwitch();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string HVACSystemRootFindingAlgorithm_Impl::algorithm() const {
      const auto value = getString(openstudio::HVACSystemRootFindingAlgorithmFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACSystemRootFindingAlgorithm_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::HVACSystemRootFindingAlgorithmFields::Algorithm, algorithm);
    }

    bool HVACSystemRootFindingAlgorithm_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::HVACSystemRootFindingAlgorithmFields::Algorithm);
    }

    void HVACSystemRootFindingAlgorithm_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::HVACSystemRootFindingAlgorithmFields::Algorithm, "RegulaFalsi"));
    }

    int HVACSystemRootFindingAlgorithm_Impl::numberofIterationsBeforeAlgorithmSwitch() const {
      const auto value = getInt(openstudio::HVACSystemRootFindingAlgorithmFields::NumberofIterationsBeforeAlgorithmSwitch, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACSystemRootFindingAlgorithm_Impl::setNumberofIterationsBeforeAlgorithmSwitch(int numberofIterationsBeforeAlgorithmSwitch) {
      return setInt(openstudio::HVACSystemRootFindingAlgorithmFields::NumberofIterationsBeforeAlgorithmSwitch,
                    numberofIterationsBeforeAlgorithmSwitch);
    }

    bool HVACSystemRootFindingAlgorithm_Impl::isNumberofIterationsBeforeAlgorithmSwitchDefaulted() const {
      return !getInt(openstudio::HVACSystemRootFindingAlgorithmFields::NumberofIterationsBeforeAlgorithmSwitch, false);
    }

    void HVACSystemRootFindingAlgorithm_Impl::resetNumberofIterationsBeforeAlgorithmSwitch() {
      OS_ASSERT(setString(openstudio::HVACSystemRootFindingAlgorithmFields::NumberofIterationsBeforeAlgorithmSwitch, ""));
    }

    std::vector<std::string> HVACSystemRootFindingAlgorithm_Impl::algorithmValues() const {
      return openstudio::epmodel::HVACSystemRootFindingAlgorithm::algorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
