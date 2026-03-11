/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneComponentDetailedOpening.hpp"
#include "AirflowNetworkMultiZoneComponentDetailedOpening_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_MultiZone_Component_DetailedOpening_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirflowNetworkMultiZoneComponentDetailedOpening::AirflowNetworkMultiZoneComponentDetailedOpening(const Model& model)
  : ModelObject(AirflowNetworkMultiZoneComponentDetailedOpening::iddObjectType(), model) {}

AirflowNetworkMultiZoneComponentDetailedOpening::AirflowNetworkMultiZoneComponentDetailedOpening(
  std::shared_ptr<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkMultiZoneComponentDetailedOpening::iddObjectType() {
  return IddObjectType::AirflowNetwork_MultiZone_Component_DetailedOpening;
}

std::vector<std::string> AirflowNetworkMultiZoneComponentDetailedOpening::typeofRectangularLargeVerticalOpeningLVOValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::TypeofRectangularLargeVerticalOpening_LVO_);
}

double AirflowNetworkMultiZoneComponentDetailedOpening::airMassFlowCoefficientWhenOpeningisClosed() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->airMassFlowCoefficientWhenOpeningisClosed();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::setAirMassFlowCoefficientWhenOpeningisClosed(
  double airMassFlowCoefficientWhenOpeningisClosed) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->setAirMassFlowCoefficientWhenOpeningisClosed(
    airMassFlowCoefficientWhenOpeningisClosed);
}

double AirflowNetworkMultiZoneComponentDetailedOpening::airMassFlowExponentWhenOpeningisClosed() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->airMassFlowExponentWhenOpeningisClosed();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::isAirMassFlowExponentWhenOpeningisClosedDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->isAirMassFlowExponentWhenOpeningisClosedDefaulted();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->setAirMassFlowExponentWhenOpeningisClosed(
    airMassFlowExponentWhenOpeningisClosed);
}

void AirflowNetworkMultiZoneComponentDetailedOpening::resetAirMassFlowExponentWhenOpeningisClosed() {
  getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->resetAirMassFlowExponentWhenOpeningisClosed();
}

std::string AirflowNetworkMultiZoneComponentDetailedOpening::typeofRectangularLargeVerticalOpeningLVO() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->typeofRectangularLargeVerticalOpeningLVO();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::isTypeofRectangularLargeVerticalOpeningLVODefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->isTypeofRectangularLargeVerticalOpeningLVODefaulted();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::setTypeofRectangularLargeVerticalOpeningLVO(
  const std::string& typeofRectangularLargeVerticalOpeningLVO) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->setTypeofRectangularLargeVerticalOpeningLVO(
    typeofRectangularLargeVerticalOpeningLVO);
}

void AirflowNetworkMultiZoneComponentDetailedOpening::resetTypeofRectangularLargeVerticalOpeningLVO() {
  getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->resetTypeofRectangularLargeVerticalOpeningLVO();
}

double AirflowNetworkMultiZoneComponentDetailedOpening::extraCrackLengthorHeightofPivotingAxis() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->extraCrackLengthorHeightofPivotingAxis();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::isExtraCrackLengthorHeightofPivotingAxisDefaulted() const {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->isExtraCrackLengthorHeightofPivotingAxisDefaulted();
}

bool AirflowNetworkMultiZoneComponentDetailedOpening::setExtraCrackLengthorHeightofPivotingAxis(double extraCrackLengthorHeightofPivotingAxis) {
  return getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->setExtraCrackLengthorHeightofPivotingAxis(
    extraCrackLengthorHeightofPivotingAxis);
}

void AirflowNetworkMultiZoneComponentDetailedOpening::resetExtraCrackLengthorHeightofPivotingAxis() {
  getImpl<detail::AirflowNetworkMultiZoneComponentDetailedOpening_Impl>()->resetExtraCrackLengthorHeightofPivotingAxis();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double AirflowNetworkMultiZoneComponentDetailedOpening_Impl::airMassFlowCoefficientWhenOpeningisClosed() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::setAirMassFlowCoefficientWhenOpeningisClosed(
  double airMassFlowCoefficientWhenOpeningisClosed) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed,
                   airMassFlowCoefficientWhenOpeningisClosed);
}

double AirflowNetworkMultiZoneComponentDetailedOpening_Impl::airMassFlowExponentWhenOpeningisClosed() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowExponentWhenOpeningisClosed, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::isAirMassFlowExponentWhenOpeningisClosedDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowExponentWhenOpeningisClosed);
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowExponentWhenOpeningisClosed,
                   airMassFlowExponentWhenOpeningisClosed);
}

void AirflowNetworkMultiZoneComponentDetailedOpening_Impl::resetAirMassFlowExponentWhenOpeningisClosed() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowExponentWhenOpeningisClosed, ""));
}

std::string AirflowNetworkMultiZoneComponentDetailedOpening_Impl::typeofRectangularLargeVerticalOpeningLVO() const {
  const auto value =
    getString(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::TypeofRectangularLargeVerticalOpening_LVO_, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::isTypeofRectangularLargeVerticalOpeningLVODefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::TypeofRectangularLargeVerticalOpening_LVO_);
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::setTypeofRectangularLargeVerticalOpeningLVO(
  const std::string& typeofRectangularLargeVerticalOpeningLVO) {
  return setString(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::TypeofRectangularLargeVerticalOpening_LVO_,
                   typeofRectangularLargeVerticalOpeningLVO);
}

void AirflowNetworkMultiZoneComponentDetailedOpening_Impl::resetTypeofRectangularLargeVerticalOpeningLVO() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::TypeofRectangularLargeVerticalOpening_LVO_, ""));
}

double AirflowNetworkMultiZoneComponentDetailedOpening_Impl::extraCrackLengthorHeightofPivotingAxis() const {
  const auto value =
    getDouble(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::ExtraCrackLengthorHeightofPivotingAxis, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::isExtraCrackLengthorHeightofPivotingAxisDefaulted() const {
  return isEmpty(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::ExtraCrackLengthorHeightofPivotingAxis);
}

bool AirflowNetworkMultiZoneComponentDetailedOpening_Impl::setExtraCrackLengthorHeightofPivotingAxis(double extraCrackLengthorHeightofPivotingAxis) {
  return setDouble(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::ExtraCrackLengthorHeightofPivotingAxis,
                   extraCrackLengthorHeightofPivotingAxis);
}

void AirflowNetworkMultiZoneComponentDetailedOpening_Impl::resetExtraCrackLengthorHeightofPivotingAxis() {
  OS_ASSERT(setString(openstudio::AirflowNetwork_MultiZone_Component_DetailedOpeningFields::ExtraCrackLengthorHeightofPivotingAxis, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
