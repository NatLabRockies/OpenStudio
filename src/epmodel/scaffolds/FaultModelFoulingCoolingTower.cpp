/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelFoulingCoolingTower.hpp"
#include "FaultModelFoulingCoolingTower_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_Fouling_CoolingTower_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FaultModelFoulingCoolingTower::FaultModelFoulingCoolingTower(const Model& model)
    : ModelObject(FaultModelFoulingCoolingTower::iddObjectType(), model) {}

  FaultModelFoulingCoolingTower::FaultModelFoulingCoolingTower(std::shared_ptr<detail::FaultModelFoulingCoolingTower_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelFoulingCoolingTower::iddObjectType() {
    return IddObjectType::FaultModel_Fouling_CoolingTower;
  }

  std::vector<std::string> FaultModelFoulingCoolingTower::coolingTowerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::FaultModel_Fouling_CoolingTowerFields::CoolingTowerObjectType);
  }

  std::string FaultModelFoulingCoolingTower::coolingTowerObjectType() const {
    return getImpl<detail::FaultModelFoulingCoolingTower_Impl>()->coolingTowerObjectType();
  }

  bool FaultModelFoulingCoolingTower::setCoolingTowerObjectType(const std::string& coolingTowerObjectType) {
    return getImpl<detail::FaultModelFoulingCoolingTower_Impl>()->setCoolingTowerObjectType(coolingTowerObjectType);
  }

  boost::optional<double> FaultModelFoulingCoolingTower::referenceUAReductionFactor() const {
    return getImpl<detail::FaultModelFoulingCoolingTower_Impl>()->referenceUAReductionFactor();
  }

  bool FaultModelFoulingCoolingTower::setReferenceUAReductionFactor(double referenceUAReductionFactor) {
    return getImpl<detail::FaultModelFoulingCoolingTower_Impl>()->setReferenceUAReductionFactor(referenceUAReductionFactor);
  }

  void FaultModelFoulingCoolingTower::resetReferenceUAReductionFactor() {
    getImpl<detail::FaultModelFoulingCoolingTower_Impl>()->resetReferenceUAReductionFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string FaultModelFoulingCoolingTower_Impl::coolingTowerObjectType() const {
      const auto value = getString(openstudio::FaultModel_Fouling_CoolingTowerFields::CoolingTowerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingCoolingTower_Impl::setCoolingTowerObjectType(const std::string& coolingTowerObjectType) {
      return setString(openstudio::FaultModel_Fouling_CoolingTowerFields::CoolingTowerObjectType, coolingTowerObjectType);
    }

    boost::optional<double> FaultModelFoulingCoolingTower_Impl::referenceUAReductionFactor() const {
      return getDouble(openstudio::FaultModel_Fouling_CoolingTowerFields::ReferenceUAReductionFactor, true);
    }

    bool FaultModelFoulingCoolingTower_Impl::setReferenceUAReductionFactor(double referenceUAReductionFactor) {
      return setDouble(openstudio::FaultModel_Fouling_CoolingTowerFields::ReferenceUAReductionFactor, referenceUAReductionFactor);
    }

    void FaultModelFoulingCoolingTower_Impl::resetReferenceUAReductionFactor() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_CoolingTowerFields::ReferenceUAReductionFactor, ""));
    }

    std::vector<std::string> FaultModelFoulingCoolingTower_Impl::coolingTowerObjectTypeValues() const {
      return openstudio::epmodel::FaultModelFoulingCoolingTower::coolingTowerObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
