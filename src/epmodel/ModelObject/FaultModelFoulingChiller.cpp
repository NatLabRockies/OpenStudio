/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelFoulingChiller.hpp"
#include "FaultModelFoulingChiller_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_Fouling_Chiller_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FaultModelFoulingChiller::FaultModelFoulingChiller(const Model& model) : ModelObject(FaultModelFoulingChiller::iddObjectType(), model) {}

  FaultModelFoulingChiller::FaultModelFoulingChiller(std::shared_ptr<detail::FaultModelFoulingChiller_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelFoulingChiller::iddObjectType() {
    return IddObjectType::FaultModel_Fouling_Chiller;
  }

  std::vector<std::string> FaultModelFoulingChiller::chillerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FaultModel_Fouling_ChillerFields::ChillerObjectType);
  }

  std::string FaultModelFoulingChiller::chillerObjectType() const {
    return getImpl<detail::FaultModelFoulingChiller_Impl>()->chillerObjectType();
  }

  bool FaultModelFoulingChiller::setChillerObjectType(const std::string& chillerObjectType) {
    return getImpl<detail::FaultModelFoulingChiller_Impl>()->setChillerObjectType(chillerObjectType);
  }

  double FaultModelFoulingChiller::foulingFactor() const {
    return getImpl<detail::FaultModelFoulingChiller_Impl>()->foulingFactor();
  }

  bool FaultModelFoulingChiller::isFoulingFactorDefaulted() const {
    return getImpl<detail::FaultModelFoulingChiller_Impl>()->isFoulingFactorDefaulted();
  }

  bool FaultModelFoulingChiller::setFoulingFactor(double foulingFactor) {
    return getImpl<detail::FaultModelFoulingChiller_Impl>()->setFoulingFactor(foulingFactor);
  }

  void FaultModelFoulingChiller::resetFoulingFactor() {
    getImpl<detail::FaultModelFoulingChiller_Impl>()->resetFoulingFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> FaultModelFoulingChiller_Impl::chillerObjectTypeValues() const {
      return openstudio::epmodel::FaultModelFoulingChiller::chillerObjectTypeValues();
    }

    std::string FaultModelFoulingChiller_Impl::chillerObjectType() const {
      const auto value = getString(openstudio::FaultModel_Fouling_ChillerFields::ChillerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingChiller_Impl::setChillerObjectType(const std::string& chillerObjectType) {
      return setString(openstudio::FaultModel_Fouling_ChillerFields::ChillerObjectType, chillerObjectType);
    }

    double FaultModelFoulingChiller_Impl::foulingFactor() const {
      const auto value = getDouble(openstudio::FaultModel_Fouling_ChillerFields::FoulingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingChiller_Impl::isFoulingFactorDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_ChillerFields::FoulingFactor);
    }

    bool FaultModelFoulingChiller_Impl::setFoulingFactor(double foulingFactor) {
      return setDouble(openstudio::FaultModel_Fouling_ChillerFields::FoulingFactor, foulingFactor);
    }

    void FaultModelFoulingChiller_Impl::resetFoulingFactor() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_ChillerFields::FoulingFactor, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
