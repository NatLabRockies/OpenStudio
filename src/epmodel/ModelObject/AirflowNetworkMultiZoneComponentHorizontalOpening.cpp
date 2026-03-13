/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneComponentHorizontalOpening.hpp"
#include "AirflowNetworkMultiZoneComponentHorizontalOpening_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Component_HorizontalOpening_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkMultiZoneComponentHorizontalOpening::AirflowNetworkMultiZoneComponentHorizontalOpening(const Model& model)
    : ModelObject(AirflowNetworkMultiZoneComponentHorizontalOpening::iddObjectType(), model) {}

  AirflowNetworkMultiZoneComponentHorizontalOpening::AirflowNetworkMultiZoneComponentHorizontalOpening(
    std::shared_ptr<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkMultiZoneComponentHorizontalOpening::iddObjectType() {
    return IddObjectType::AirflowNetwork_MultiZone_Component_HorizontalOpening;
  }

  double AirflowNetworkMultiZoneComponentHorizontalOpening::airMassFlowCoefficientWhenOpeningisClosed() const {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->airMassFlowCoefficientWhenOpeningisClosed();
  }

  bool AirflowNetworkMultiZoneComponentHorizontalOpening::setAirMassFlowCoefficientWhenOpeningisClosed(
    double airMassFlowCoefficientWhenOpeningisClosed) {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->setAirMassFlowCoefficientWhenOpeningisClosed(
      airMassFlowCoefficientWhenOpeningisClosed);
  }

  double AirflowNetworkMultiZoneComponentHorizontalOpening::airMassFlowExponentWhenOpeningisClosed() const {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->airMassFlowExponentWhenOpeningisClosed();
  }

  bool AirflowNetworkMultiZoneComponentHorizontalOpening::setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed) {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->setAirMassFlowExponentWhenOpeningisClosed(
      airMassFlowExponentWhenOpeningisClosed);
  }

  bool AirflowNetworkMultiZoneComponentHorizontalOpening::isAirMassFlowExponentWhenOpeningisClosedDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->isAirMassFlowExponentWhenOpeningisClosedDefaulted();
  }

  void AirflowNetworkMultiZoneComponentHorizontalOpening::resetAirMassFlowExponentWhenOpeningisClosed() {
    getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->resetAirMassFlowExponentWhenOpeningisClosed();
  }

  double AirflowNetworkMultiZoneComponentHorizontalOpening::slopingPlaneAngle() const {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->slopingPlaneAngle();
  }

  bool AirflowNetworkMultiZoneComponentHorizontalOpening::setSlopingPlaneAngle(double slopingPlaneAngle) {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->setSlopingPlaneAngle(slopingPlaneAngle);
  }

  bool AirflowNetworkMultiZoneComponentHorizontalOpening::isSlopingPlaneAngleDefaulted() const {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->isSlopingPlaneAngleDefaulted();
  }

  void AirflowNetworkMultiZoneComponentHorizontalOpening::resetSlopingPlaneAngle() {
    getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->resetSlopingPlaneAngle();
  }

  double AirflowNetworkMultiZoneComponentHorizontalOpening::dischargeCoefficient() const {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->dischargeCoefficient();
  }

  bool AirflowNetworkMultiZoneComponentHorizontalOpening::setDischargeCoefficient(double dischargeCoefficient) {
    return getImpl<detail::AirflowNetworkMultiZoneComponentHorizontalOpening_Impl>()->setDischargeCoefficient(dischargeCoefficient);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::airMassFlowCoefficientWhenOpeningisClosed() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::setAirMassFlowCoefficientWhenOpeningisClosed(
      double airMassFlowCoefficientWhenOpeningisClosed) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed,
                       airMassFlowCoefficientWhenOpeningisClosed);
    }

    double AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::airMassFlowExponentWhenOpeningisClosed() const {
      const auto value =
        getDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowExponentWhenOpeningisClosed, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::setAirMassFlowExponentWhenOpeningisClosed(
      double airMassFlowExponentWhenOpeningisClosed) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowExponentWhenOpeningisClosed,
                       airMassFlowExponentWhenOpeningisClosed);
    }

    bool AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::isAirMassFlowExponentWhenOpeningisClosedDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowExponentWhenOpeningisClosed);
    }

    void AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::resetAirMassFlowExponentWhenOpeningisClosed() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowExponentWhenOpeningisClosed, ""));
    }

    double AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::slopingPlaneAngle() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::SlopingPlaneAngle, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::setSlopingPlaneAngle(double slopingPlaneAngle) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::SlopingPlaneAngle, slopingPlaneAngle);
    }

    bool AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::isSlopingPlaneAngleDefaulted() const {
      return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::SlopingPlaneAngle);
    }

    void AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::resetSlopingPlaneAngle() {
      OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::SlopingPlaneAngle, ""));
    }

    double AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::dischargeCoefficient() const {
      const auto value = getDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::DischargeCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirflowNetworkMultiZoneComponentHorizontalOpening_Impl::setDischargeCoefficient(double dischargeCoefficient) {
      return setDouble(openstudio::AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::DischargeCoefficient, dischargeCoefficient);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
