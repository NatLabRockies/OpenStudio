/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementSimParameters.hpp"
#include "GroundHeatTransferBasementSimParameters_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_SimParameters_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferBasementSimParameters::GroundHeatTransferBasementSimParameters(const Model& model)
  : ModelObject(GroundHeatTransferBasementSimParameters::iddObjectType(), model) {}

GroundHeatTransferBasementSimParameters::GroundHeatTransferBasementSimParameters(
  std::shared_ptr<detail::GroundHeatTransferBasementSimParameters_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferBasementSimParameters::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Basement_SimParameters;
}

boost::optional<double> GroundHeatTransferBasementSimParameters::fMultiplierfortheADIsolution() const {
  return getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->fMultiplierfortheADIsolution();
}

bool GroundHeatTransferBasementSimParameters::setFMultiplierfortheADIsolution(double fMultiplierfortheADIsolution) {
  return getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->setFMultiplierfortheADIsolution(fMultiplierfortheADIsolution);
}

void GroundHeatTransferBasementSimParameters::resetFMultiplierfortheADIsolution() {
  getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->resetFMultiplierfortheADIsolution();
}

int GroundHeatTransferBasementSimParameters::iYRSMaximumnumberofyearlyiterations() const {
  return getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->iYRSMaximumnumberofyearlyiterations();
}

bool GroundHeatTransferBasementSimParameters::isIYRSMaximumnumberofyearlyiterationsDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->isIYRSMaximumnumberofyearlyiterationsDefaulted();
}

bool GroundHeatTransferBasementSimParameters::setIYRSMaximumnumberofyearlyiterations(int iYRSMaximumnumberofyearlyiterations) {
  return getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->setIYRSMaximumnumberofyearlyiterations(
    iYRSMaximumnumberofyearlyiterations);
}

void GroundHeatTransferBasementSimParameters::resetIYRSMaximumnumberofyearlyiterations() {
  getImpl<detail::GroundHeatTransferBasementSimParameters_Impl>()->resetIYRSMaximumnumberofyearlyiterations();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> GroundHeatTransferBasementSimParameters_Impl::fMultiplierfortheADIsolution() const {
  return getDouble(openstudio::GroundHeatTransfer_Basement_SimParametersFields::F_MultiplierfortheADIsolution, true);
}

bool GroundHeatTransferBasementSimParameters_Impl::setFMultiplierfortheADIsolution(double fMultiplierfortheADIsolution) {
  return setDouble(openstudio::GroundHeatTransfer_Basement_SimParametersFields::F_MultiplierfortheADIsolution, fMultiplierfortheADIsolution);
}

void GroundHeatTransferBasementSimParameters_Impl::resetFMultiplierfortheADIsolution() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SimParametersFields::F_MultiplierfortheADIsolution, ""));
}

int GroundHeatTransferBasementSimParameters_Impl::iYRSMaximumnumberofyearlyiterations() const {
  const auto value = getInt(openstudio::GroundHeatTransfer_Basement_SimParametersFields::IYRS_Maximumnumberofyearlyiterations_, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferBasementSimParameters_Impl::isIYRSMaximumnumberofyearlyiterationsDefaulted() const {
  return isEmpty(openstudio::GroundHeatTransfer_Basement_SimParametersFields::IYRS_Maximumnumberofyearlyiterations_);
}

bool GroundHeatTransferBasementSimParameters_Impl::setIYRSMaximumnumberofyearlyiterations(int iYRSMaximumnumberofyearlyiterations) {
  return setInt(openstudio::GroundHeatTransfer_Basement_SimParametersFields::IYRS_Maximumnumberofyearlyiterations_,
                iYRSMaximumnumberofyearlyiterations);
}

void GroundHeatTransferBasementSimParameters_Impl::resetIYRSMaximumnumberofyearlyiterations() {
  OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_SimParametersFields::IYRS_Maximumnumberofyearlyiterations_, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
