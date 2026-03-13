/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelHumidistatOffset.hpp"
#include "FaultModelHumidistatOffset_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_HumidistatOffset_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FaultModelHumidistatOffset::FaultModelHumidistatOffset(const Model& model) : ModelObject(FaultModelHumidistatOffset::iddObjectType(), model) {}

  FaultModelHumidistatOffset::FaultModelHumidistatOffset(std::shared_ptr<detail::FaultModelHumidistatOffset_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FaultModelHumidistatOffset::iddObjectType() {
    return IddObjectType::FaultModel_HumidistatOffset;
  }

  std::vector<std::string> FaultModelHumidistatOffset::humidistatOffsetTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::FaultModel_HumidistatOffsetFields::HumidistatOffsetType);
  }

  std::string FaultModelHumidistatOffset::humidistatOffsetType() const {
    return getImpl<detail::FaultModelHumidistatOffset_Impl>()->humidistatOffsetType();
  }

  bool FaultModelHumidistatOffset::isHumidistatOffsetTypeDefaulted() const {
    return getImpl<detail::FaultModelHumidistatOffset_Impl>()->isHumidistatOffsetTypeDefaulted();
  }

  bool FaultModelHumidistatOffset::setHumidistatOffsetType(const std::string& humidistatOffsetType) {
    return getImpl<detail::FaultModelHumidistatOffset_Impl>()->setHumidistatOffsetType(humidistatOffsetType);
  }

  void FaultModelHumidistatOffset::resetHumidistatOffsetType() {
    getImpl<detail::FaultModelHumidistatOffset_Impl>()->resetHumidistatOffsetType();
  }

  double FaultModelHumidistatOffset::referenceHumidistatOffset() const {
    return getImpl<detail::FaultModelHumidistatOffset_Impl>()->referenceHumidistatOffset();
  }

  bool FaultModelHumidistatOffset::isReferenceHumidistatOffsetDefaulted() const {
    return getImpl<detail::FaultModelHumidistatOffset_Impl>()->isReferenceHumidistatOffsetDefaulted();
  }

  bool FaultModelHumidistatOffset::setReferenceHumidistatOffset(double referenceHumidistatOffset) {
    return getImpl<detail::FaultModelHumidistatOffset_Impl>()->setReferenceHumidistatOffset(referenceHumidistatOffset);
  }

  void FaultModelHumidistatOffset::resetReferenceHumidistatOffset() {
    getImpl<detail::FaultModelHumidistatOffset_Impl>()->resetReferenceHumidistatOffset();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> FaultModelHumidistatOffset_Impl::humidistatOffsetTypeValues() const {
      return openstudio::epmodel::FaultModelHumidistatOffset::humidistatOffsetTypeValues();
    }

    std::string FaultModelHumidistatOffset_Impl::humidistatOffsetType() const {
      const auto value = getString(openstudio::FaultModel_HumidistatOffsetFields::HumidistatOffsetType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelHumidistatOffset_Impl::isHumidistatOffsetTypeDefaulted() const {
      return isEmpty(openstudio::FaultModel_HumidistatOffsetFields::HumidistatOffsetType);
    }

    bool FaultModelHumidistatOffset_Impl::setHumidistatOffsetType(const std::string& humidistatOffsetType) {
      return setString(openstudio::FaultModel_HumidistatOffsetFields::HumidistatOffsetType, humidistatOffsetType);
    }

    void FaultModelHumidistatOffset_Impl::resetHumidistatOffsetType() {
      OS_ASSERT(setString(openstudio::FaultModel_HumidistatOffsetFields::HumidistatOffsetType, ""));
    }

    double FaultModelHumidistatOffset_Impl::referenceHumidistatOffset() const {
      const auto value = getDouble(openstudio::FaultModel_HumidistatOffsetFields::ReferenceHumidistatOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FaultModelHumidistatOffset_Impl::isReferenceHumidistatOffsetDefaulted() const {
      return isEmpty(openstudio::FaultModel_HumidistatOffsetFields::ReferenceHumidistatOffset);
    }

    bool FaultModelHumidistatOffset_Impl::setReferenceHumidistatOffset(double referenceHumidistatOffset) {
      return setDouble(openstudio::FaultModel_HumidistatOffsetFields::ReferenceHumidistatOffset, referenceHumidistatOffset);
    }

    void FaultModelHumidistatOffset_Impl::resetReferenceHumidistatOffset() {
      OS_ASSERT(setString(openstudio::FaultModel_HumidistatOffsetFields::ReferenceHumidistatOffset, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
