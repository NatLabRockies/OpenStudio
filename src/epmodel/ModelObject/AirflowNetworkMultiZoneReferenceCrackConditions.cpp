/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneReferenceCrackConditions.hpp"
#include "AirflowNetworkMultiZoneReferenceCrackConditions_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_ReferenceCrackConditions_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkMultiZoneReferenceCrackConditions::AirflowNetworkMultiZoneReferenceCrackConditions(const Model& model)
    : ModelObject(AirflowNetworkMultiZoneReferenceCrackConditions::iddObjectType(), model) {}

  AirflowNetworkMultiZoneReferenceCrackConditions::AirflowNetworkMultiZoneReferenceCrackConditions(
    std::shared_ptr<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkMultiZoneReferenceCrackConditions::iddObjectType() {
    return IddObjectType::AirflowNetwork_MultiZone_ReferenceCrackConditions;
  }

  double AirflowNetworkMultiZoneReferenceCrackConditions::referenceTemperature() const {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->referenceTemperature();
  }

  bool AirflowNetworkMultiZoneReferenceCrackConditions::setReferenceTemperature(double referenceTemperature) {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->setReferenceTemperature(referenceTemperature);
  }

  double AirflowNetworkMultiZoneReferenceCrackConditions::referenceBarometricPressure() const {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->referenceBarometricPressure();
  }

  bool AirflowNetworkMultiZoneReferenceCrackConditions::isReferenceBarometricPressureDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->isReferenceBarometricPressureDefaulted();
  }

  bool AirflowNetworkMultiZoneReferenceCrackConditions::setReferenceBarometricPressure(double referenceBarometricPressure) {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->setReferenceBarometricPressure(referenceBarometricPressure);
  }

  void AirflowNetworkMultiZoneReferenceCrackConditions::resetReferenceBarometricPressure() {
    getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->resetReferenceBarometricPressure();
  }

  double AirflowNetworkMultiZoneReferenceCrackConditions::referenceHumidityRatio() const {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->referenceHumidityRatio();
  }

  bool AirflowNetworkMultiZoneReferenceCrackConditions::isReferenceHumidityRatioDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->isReferenceHumidityRatioDefaulted();
  }

  bool AirflowNetworkMultiZoneReferenceCrackConditions::setReferenceHumidityRatio(double referenceHumidityRatio) {
    return getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->setReferenceHumidityRatio(referenceHumidityRatio);
  }

  void AirflowNetworkMultiZoneReferenceCrackConditions::resetReferenceHumidityRatio() {
    getImpl<detail::AirflowNetworkMultiZoneReferenceCrackConditions_Impl>()->resetReferenceHumidityRatio();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkMultiZoneReferenceCrackConditions_Impl::referenceTemperature() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneReferenceCrackConditions_Impl::setReferenceTemperature(double referenceTemperature) {
      const bool result = setDouble(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceTemperature, referenceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double AirflowNetworkMultiZoneReferenceCrackConditions_Impl::referenceBarometricPressure() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceBarometricPressure, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneReferenceCrackConditions_Impl::isReferenceBarometricPressureDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceBarometricPressure);
    }

    bool AirflowNetworkMultiZoneReferenceCrackConditions_Impl::setReferenceBarometricPressure(double referenceBarometricPressure) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceBarometricPressure, referenceBarometricPressure);
    }

    void AirflowNetworkMultiZoneReferenceCrackConditions_Impl::resetReferenceBarometricPressure() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceBarometricPressure, ""));
    }

    double AirflowNetworkMultiZoneReferenceCrackConditions_Impl::referenceHumidityRatio() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneReferenceCrackConditions_Impl::isReferenceHumidityRatioDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceHumidityRatio);
    }

    bool AirflowNetworkMultiZoneReferenceCrackConditions_Impl::setReferenceHumidityRatio(double referenceHumidityRatio) {
      const bool result =
        setDouble(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceHumidityRatio, referenceHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void AirflowNetworkMultiZoneReferenceCrackConditions_Impl::resetReferenceHumidityRatio() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_ReferenceCrackConditionsFields::ReferenceHumidityRatio, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
