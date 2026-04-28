/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelFoulingBoiler.hpp"
#include "FaultModelFoulingBoiler_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_Fouling_Boiler_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FaultModelFoulingBoiler::FaultModelFoulingBoiler(const Model& model) : ModelObject(FaultModelFoulingBoiler::iddObjectType(), model) {}

  FaultModelFoulingBoiler::FaultModelFoulingBoiler(std::shared_ptr<detail::FaultModelFoulingBoiler_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelFoulingBoiler::iddObjectType() {
    return IddObjectType::FaultModel_Fouling_Boiler;
  }

  std::vector<std::string> FaultModelFoulingBoiler::boilerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FaultModel_Fouling_BoilerFields::BoilerObjectType);
  }

  std::string FaultModelFoulingBoiler::boilerObjectType() const {
    return getImpl<detail::FaultModelFoulingBoiler_Impl>()->boilerObjectType();
  }

  bool FaultModelFoulingBoiler::setBoilerObjectType(const std::string& boilerObjectType) {
    return getImpl<detail::FaultModelFoulingBoiler_Impl>()->setBoilerObjectType(boilerObjectType);
  }

  double FaultModelFoulingBoiler::foulingFactor() const {
    return getImpl<detail::FaultModelFoulingBoiler_Impl>()->foulingFactor();
  }

  bool FaultModelFoulingBoiler::setFoulingFactor(double foulingFactor) {
    return getImpl<detail::FaultModelFoulingBoiler_Impl>()->setFoulingFactor(foulingFactor);
  }

  bool FaultModelFoulingBoiler::isFoulingFactorDefaulted() const {
    return getImpl<detail::FaultModelFoulingBoiler_Impl>()->isFoulingFactorDefaulted();
  }

  void FaultModelFoulingBoiler::resetFoulingFactor() {
    getImpl<detail::FaultModelFoulingBoiler_Impl>()->resetFoulingFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string FaultModelFoulingBoiler_Impl::boilerObjectType() const {
      const auto value = getString(openstudio::FaultModel_Fouling_BoilerFields::BoilerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingBoiler_Impl::setBoilerObjectType(const std::string& boilerObjectType) {
      return setString(openstudio::FaultModel_Fouling_BoilerFields::BoilerObjectType, boilerObjectType);
    }

    double FaultModelFoulingBoiler_Impl::foulingFactor() const {
      const auto value = getDouble(openstudio::FaultModel_Fouling_BoilerFields::FoulingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingBoiler_Impl::setFoulingFactor(double foulingFactor) {
      return setDouble(openstudio::FaultModel_Fouling_BoilerFields::FoulingFactor, foulingFactor);
    }

    bool FaultModelFoulingBoiler_Impl::isFoulingFactorDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_BoilerFields::FoulingFactor);
    }

    void FaultModelFoulingBoiler_Impl::resetFoulingFactor() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_BoilerFields::FoulingFactor, ""));
    }

    std::vector<std::string> FaultModelFoulingBoiler_Impl::boilerObjectTypeValues() const {
      return openstudio::epmodel::FaultModelFoulingBoiler::boilerObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
