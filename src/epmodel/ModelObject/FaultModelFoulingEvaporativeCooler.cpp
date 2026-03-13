/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelFoulingEvaporativeCooler.hpp"
#include "FaultModelFoulingEvaporativeCooler_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_Fouling_EvaporativeCooler_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FaultModelFoulingEvaporativeCooler::FaultModelFoulingEvaporativeCooler(const Model& model)
    : ModelObject(FaultModelFoulingEvaporativeCooler::iddObjectType(), model) {}

  FaultModelFoulingEvaporativeCooler::FaultModelFoulingEvaporativeCooler(std::shared_ptr<detail::FaultModelFoulingEvaporativeCooler_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelFoulingEvaporativeCooler::iddObjectType() {
    return IddObjectType::FaultModel_Fouling_EvaporativeCooler;
  }

  std::vector<std::string> FaultModelFoulingEvaporativeCooler::evaporativeCoolerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::FaultModel_Fouling_EvaporativeCoolerFields::EvaporativeCoolerObjectType);
  }

  std::string FaultModelFoulingEvaporativeCooler::evaporativeCoolerObjectType() const {
    return getImpl<detail::FaultModelFoulingEvaporativeCooler_Impl>()->evaporativeCoolerObjectType();
  }

  bool FaultModelFoulingEvaporativeCooler::setEvaporativeCoolerObjectType(const std::string& evaporativeCoolerObjectType) {
    return getImpl<detail::FaultModelFoulingEvaporativeCooler_Impl>()->setEvaporativeCoolerObjectType(evaporativeCoolerObjectType);
  }

  double FaultModelFoulingEvaporativeCooler::foulingFactor() const {
    return getImpl<detail::FaultModelFoulingEvaporativeCooler_Impl>()->foulingFactor();
  }

  bool FaultModelFoulingEvaporativeCooler::setFoulingFactor(double foulingFactor) {
    return getImpl<detail::FaultModelFoulingEvaporativeCooler_Impl>()->setFoulingFactor(foulingFactor);
  }

  bool FaultModelFoulingEvaporativeCooler::isFoulingFactorDefaulted() const {
    return getImpl<detail::FaultModelFoulingEvaporativeCooler_Impl>()->isFoulingFactorDefaulted();
  }

  void FaultModelFoulingEvaporativeCooler::resetFoulingFactor() {
    getImpl<detail::FaultModelFoulingEvaporativeCooler_Impl>()->resetFoulingFactor();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string FaultModelFoulingEvaporativeCooler_Impl::evaporativeCoolerObjectType() const {
      const auto value = getString(openstudio::FaultModel_Fouling_EvaporativeCoolerFields::EvaporativeCoolerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingEvaporativeCooler_Impl::setEvaporativeCoolerObjectType(const std::string& evaporativeCoolerObjectType) {
      return setString(openstudio::FaultModel_Fouling_EvaporativeCoolerFields::EvaporativeCoolerObjectType, evaporativeCoolerObjectType);
    }

    double FaultModelFoulingEvaporativeCooler_Impl::foulingFactor() const {
      const auto value = getDouble(openstudio::FaultModel_Fouling_EvaporativeCoolerFields::FoulingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelFoulingEvaporativeCooler_Impl::setFoulingFactor(double foulingFactor) {
      return setDouble(openstudio::FaultModel_Fouling_EvaporativeCoolerFields::FoulingFactor, foulingFactor);
    }

    bool FaultModelFoulingEvaporativeCooler_Impl::isFoulingFactorDefaulted() const {
      return isEmpty(openstudio::FaultModel_Fouling_EvaporativeCoolerFields::FoulingFactor);
    }

    void FaultModelFoulingEvaporativeCooler_Impl::resetFoulingFactor() {
      OS_ASSERT(setString(openstudio::FaultModel_Fouling_EvaporativeCoolerFields::FoulingFactor, ""));
    }

    std::vector<std::string> FaultModelFoulingEvaporativeCooler_Impl::evaporativeCoolerObjectTypeValues() const {
      return openstudio::epmodel::FaultModelFoulingEvaporativeCooler::evaporativeCoolerObjectTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
