/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DemandManagerAssignmentList.hpp"
#include "DemandManagerAssignmentList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DemandManagerAssignmentList_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  DemandManagerAssignmentList::DemandManagerAssignmentList(const Model& model) : ModelObject(DemandManagerAssignmentList::iddObjectType(), model) {}

  DemandManagerAssignmentList::DemandManagerAssignmentList(std::shared_ptr<detail::DemandManagerAssignmentList_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType DemandManagerAssignmentList::iddObjectType() {
    return IddObjectType::DemandManagerAssignmentList;
  }

  std::vector<std::string> DemandManagerAssignmentList::demandManagerPriorityValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::DemandManagerAssignmentListFields::DemandManagerPriority);
  }

  std::string DemandManagerAssignmentList::meterName() const {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->meterName();
  }

  bool DemandManagerAssignmentList::setMeterName(const std::string& meterName) {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->setMeterName(meterName);
  }

  double DemandManagerAssignmentList::demandLimitSafetyFraction() const {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->demandLimitSafetyFraction();
  }

  bool DemandManagerAssignmentList::setDemandLimitSafetyFraction(double demandLimitSafetyFraction) {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->setDemandLimitSafetyFraction(demandLimitSafetyFraction);
  }

  int DemandManagerAssignmentList::demandWindowLength() const {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->demandWindowLength();
  }

  bool DemandManagerAssignmentList::setDemandWindowLength(int demandWindowLength) {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->setDemandWindowLength(demandWindowLength);
  }

  std::string DemandManagerAssignmentList::demandManagerPriority() const {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->demandManagerPriority();
  }

  bool DemandManagerAssignmentList::setDemandManagerPriority(const std::string& demandManagerPriority) {
    return getImpl<detail::DemandManagerAssignmentList_Impl>()->setDemandManagerPriority(demandManagerPriority);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string DemandManagerAssignmentList_Impl::meterName() const {
      const auto value = getString(openstudio::DemandManagerAssignmentListFields::MeterName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DemandManagerAssignmentList_Impl::setMeterName(const std::string& meterName) {
      return setString(openstudio::DemandManagerAssignmentListFields::MeterName, meterName);
    }

    double DemandManagerAssignmentList_Impl::demandLimitSafetyFraction() const {
      const auto value = getDouble(openstudio::DemandManagerAssignmentListFields::DemandLimitSafetyFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DemandManagerAssignmentList_Impl::setDemandLimitSafetyFraction(double demandLimitSafetyFraction) {
      return setDouble(openstudio::DemandManagerAssignmentListFields::DemandLimitSafetyFraction, demandLimitSafetyFraction);
    }

    int DemandManagerAssignmentList_Impl::demandWindowLength() const {
      const auto value = getInt(openstudio::DemandManagerAssignmentListFields::DemandWindowLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DemandManagerAssignmentList_Impl::setDemandWindowLength(int demandWindowLength) {
      return setInt(openstudio::DemandManagerAssignmentListFields::DemandWindowLength, demandWindowLength);
    }

    std::string DemandManagerAssignmentList_Impl::demandManagerPriority() const {
      const auto value = getString(openstudio::DemandManagerAssignmentListFields::DemandManagerPriority, true);
      OS_ASSERT(value);
      return *value;
    }

    bool DemandManagerAssignmentList_Impl::setDemandManagerPriority(const std::string& demandManagerPriority) {
      return setString(openstudio::DemandManagerAssignmentListFields::DemandManagerPriority, demandManagerPriority);
    }

    std::vector<std::string> DemandManagerAssignmentList_Impl::demandManagerPriorityValues() const {
      return openstudio::epmodel::DemandManagerAssignmentList::demandManagerPriorityValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
