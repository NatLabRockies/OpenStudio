/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirSettingsOneNodeDisplacementVentilation.hpp"
#include "RoomAirSettingsOneNodeDisplacementVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RoomAirSettings_OneNodeDisplacementVentilation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

RoomAirSettingsOneNodeDisplacementVentilation::RoomAirSettingsOneNodeDisplacementVentilation(const Model& model)
  : ModelObject(RoomAirSettingsOneNodeDisplacementVentilation::iddObjectType(), model) {}

RoomAirSettingsOneNodeDisplacementVentilation::RoomAirSettingsOneNodeDisplacementVentilation(
  std::shared_ptr<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RoomAirSettingsOneNodeDisplacementVentilation::iddObjectType() {
  return IddObjectType::RoomAirSettings_OneNodeDisplacementVentilation;
}

boost::optional<double> RoomAirSettingsOneNodeDisplacementVentilation::fractionofConvectiveInternalLoadsAddedtoFloorAir() const {
  return getImpl<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl>()->fractionofConvectiveInternalLoadsAddedtoFloorAir();
}

boost::optional<double> RoomAirSettingsOneNodeDisplacementVentilation::fractionofInfiltrationInternalLoadsAddedtoFloorAir() const {
  return getImpl<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl>()->fractionofInfiltrationInternalLoadsAddedtoFloorAir();
}

bool RoomAirSettingsOneNodeDisplacementVentilation::setFractionofConvectiveInternalLoadsAddedtoFloorAir(
  double fractionofConvectiveInternalLoadsAddedtoFloorAir) {
  return getImpl<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl>()->setFractionofConvectiveInternalLoadsAddedtoFloorAir(
    fractionofConvectiveInternalLoadsAddedtoFloorAir);
}

bool RoomAirSettingsOneNodeDisplacementVentilation::setFractionofInfiltrationInternalLoadsAddedtoFloorAir(
  double fractionofInfiltrationInternalLoadsAddedtoFloorAir) {
  return getImpl<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl>()->setFractionofInfiltrationInternalLoadsAddedtoFloorAir(
    fractionofInfiltrationInternalLoadsAddedtoFloorAir);
}

void RoomAirSettingsOneNodeDisplacementVentilation::resetFractionofConvectiveInternalLoadsAddedtoFloorAir() {
  getImpl<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl>()->resetFractionofConvectiveInternalLoadsAddedtoFloorAir();
}

void RoomAirSettingsOneNodeDisplacementVentilation::resetFractionofInfiltrationInternalLoadsAddedtoFloorAir() {
  getImpl<detail::RoomAirSettingsOneNodeDisplacementVentilation_Impl>()->resetFractionofInfiltrationInternalLoadsAddedtoFloorAir();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> RoomAirSettingsOneNodeDisplacementVentilation_Impl::fractionofConvectiveInternalLoadsAddedtoFloorAir() const {
  return getDouble(openstudio::RoomAirSettings_OneNodeDisplacementVentilationFields::FractionofConvectiveInternalLoadsAddedtoFloorAir, true);
}

boost::optional<double> RoomAirSettingsOneNodeDisplacementVentilation_Impl::fractionofInfiltrationInternalLoadsAddedtoFloorAir() const {
  return getDouble(openstudio::RoomAirSettings_OneNodeDisplacementVentilationFields::FractionofInfiltrationInternalLoadsAddedtoFloorAir, true);
}

bool RoomAirSettingsOneNodeDisplacementVentilation_Impl::setFractionofConvectiveInternalLoadsAddedtoFloorAir(
  double fractionofConvectiveInternalLoadsAddedtoFloorAir) {
  return setDouble(openstudio::RoomAirSettings_OneNodeDisplacementVentilationFields::FractionofConvectiveInternalLoadsAddedtoFloorAir,
                   fractionofConvectiveInternalLoadsAddedtoFloorAir);
}

bool RoomAirSettingsOneNodeDisplacementVentilation_Impl::setFractionofInfiltrationInternalLoadsAddedtoFloorAir(
  double fractionofInfiltrationInternalLoadsAddedtoFloorAir) {
  return setDouble(openstudio::RoomAirSettings_OneNodeDisplacementVentilationFields::FractionofInfiltrationInternalLoadsAddedtoFloorAir,
                   fractionofInfiltrationInternalLoadsAddedtoFloorAir);
}

void RoomAirSettingsOneNodeDisplacementVentilation_Impl::resetFractionofConvectiveInternalLoadsAddedtoFloorAir() {
  const bool result =
    setString(openstudio::RoomAirSettings_OneNodeDisplacementVentilationFields::FractionofConvectiveInternalLoadsAddedtoFloorAir, "");
  OS_ASSERT(result);
}

void RoomAirSettingsOneNodeDisplacementVentilation_Impl::resetFractionofInfiltrationInternalLoadsAddedtoFloorAir() {
  const bool result =
    setString(openstudio::RoomAirSettings_OneNodeDisplacementVentilationFields::FractionofInfiltrationInternalLoadsAddedtoFloorAir, "");
  OS_ASSERT(result);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
