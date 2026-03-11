/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementEquivAutoGrid.hpp"
#include "GroundHeatTransferBasementEquivAutoGrid_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_EquivAutoGrid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatTransferBasementEquivAutoGrid::GroundHeatTransferBasementEquivAutoGrid(const Model& model)
  : ModelObject(GroundHeatTransferBasementEquivAutoGrid::iddObjectType(), model) {}

GroundHeatTransferBasementEquivAutoGrid::GroundHeatTransferBasementEquivAutoGrid(
  std::shared_ptr<detail::GroundHeatTransferBasementEquivAutoGrid_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatTransferBasementEquivAutoGrid::iddObjectType() {
  return IddObjectType::GroundHeatTransfer_Basement_EquivAutoGrid;
}

double GroundHeatTransferBasementEquivAutoGrid::clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain() const {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain();
}

double GroundHeatTransferBasementEquivAutoGrid::slabDepthThicknessofthefloorslab() const {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->slabDepthThicknessofthefloorslab();
}

double GroundHeatTransferBasementEquivAutoGrid::baseDepthDepthofthebasementwallbelowgrade() const {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->baseDepthDepthofthebasementwallbelowgrade();
}

bool GroundHeatTransferBasementEquivAutoGrid::isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted();
}

bool GroundHeatTransferBasementEquivAutoGrid::isSlabDepthThicknessofthefloorslabDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->isSlabDepthThicknessofthefloorslabDefaulted();
}

bool GroundHeatTransferBasementEquivAutoGrid::isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->isBaseDepthDepthofthebasementwallbelowgradeDefaulted();
}

bool GroundHeatTransferBasementEquivAutoGrid::setClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain(
  double clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain) {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->setClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain(
    clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain);
}

bool GroundHeatTransferBasementEquivAutoGrid::setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab) {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->setSlabDepthThicknessofthefloorslab(slabDepthThicknessofthefloorslab);
}

bool GroundHeatTransferBasementEquivAutoGrid::setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade) {
  return getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->setBaseDepthDepthofthebasementwallbelowgrade(
    baseDepthDepthofthebasementwallbelowgrade);
}

void GroundHeatTransferBasementEquivAutoGrid::resetClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain() {
  getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->resetClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain();
}

void GroundHeatTransferBasementEquivAutoGrid::resetSlabDepthThicknessofthefloorslab() {
  getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->resetSlabDepthThicknessofthefloorslab();
}

void GroundHeatTransferBasementEquivAutoGrid::resetBaseDepthDepthofthebasementwallbelowgrade() {
  getImpl<detail::GroundHeatTransferBasementEquivAutoGrid_Impl>()->resetBaseDepthDepthofthebasementwallbelowgrade();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {
constexpr unsigned kClearanceFieldIndex = 0u;
constexpr unsigned kSlabDepthFieldIndex = 1u;
constexpr unsigned kBaseDepthFieldIndex = 2u;
}  // namespace

double GroundHeatTransferBasementEquivAutoGrid_Impl::clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain() const {
  const auto value = getDouble(kClearanceFieldIndex, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementEquivAutoGrid_Impl::slabDepthThicknessofthefloorslab() const {
  const auto value = getDouble(kSlabDepthFieldIndex, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatTransferBasementEquivAutoGrid_Impl::baseDepthDepthofthebasementwallbelowgrade() const {
  const auto value = getDouble(kBaseDepthFieldIndex, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatTransferBasementEquivAutoGrid_Impl::isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted() const {
  return isEmpty(kClearanceFieldIndex);
}

bool GroundHeatTransferBasementEquivAutoGrid_Impl::isSlabDepthThicknessofthefloorslabDefaulted() const {
  return isEmpty(kSlabDepthFieldIndex);
}

bool GroundHeatTransferBasementEquivAutoGrid_Impl::isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const {
  return isEmpty(kBaseDepthFieldIndex);
}

bool GroundHeatTransferBasementEquivAutoGrid_Impl::setClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain(
  double clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain) {
  return setDouble(kClearanceFieldIndex, clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain);
}

bool GroundHeatTransferBasementEquivAutoGrid_Impl::setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab) {
  return setDouble(kSlabDepthFieldIndex, slabDepthThicknessofthefloorslab);
}

bool GroundHeatTransferBasementEquivAutoGrid_Impl::setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade) {
  return setDouble(kBaseDepthFieldIndex, baseDepthDepthofthebasementwallbelowgrade);
}

void GroundHeatTransferBasementEquivAutoGrid_Impl::resetClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain() {
  OS_ASSERT(setString(kClearanceFieldIndex, ""));
}

void GroundHeatTransferBasementEquivAutoGrid_Impl::resetSlabDepthThicknessofthefloorslab() {
  OS_ASSERT(setString(kSlabDepthFieldIndex, ""));
}

void GroundHeatTransferBasementEquivAutoGrid_Impl::resetBaseDepthDepthofthebasementwallbelowgrade() {
  OS_ASSERT(setString(kBaseDepthFieldIndex, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
