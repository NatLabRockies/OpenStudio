/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDX.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingDX::CoilCoolingDX(const Model& model) : StraightComponent(CoilCoolingDX::iddObjectType(), model) {}

CoilCoolingDX::CoilCoolingDX(std::shared_ptr<detail::CoilCoolingDX_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDX::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX;
}

std::string CoilCoolingDX::condenserInletNodeName() const {
  return getImpl<detail::CoilCoolingDX_Impl>()->condenserInletNodeName();
}

bool CoilCoolingDX::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
  return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserInletNodeName(condenserInletNodeName);
}

std::string CoilCoolingDX::condenserOutletNodeName() const {
  return getImpl<detail::CoilCoolingDX_Impl>()->condenserOutletNodeName();
}

bool CoilCoolingDX::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
  return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserOutletNodeName(condenserOutletNodeName);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingDX_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DXFields::EvaporatorInletNodeName;
}

unsigned CoilCoolingDX_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DXFields::EvaporatorOutletNodeName;
}

std::string CoilCoolingDX_Impl::condenserInletNodeName() const {
  const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDX_Impl::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
  const bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, condenserInletNodeName);
  OS_ASSERT(result);
  return result;
}

std::string CoilCoolingDX_Impl::condenserOutletNodeName() const {
  const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDX_Impl::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
  const bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, condenserOutletNodeName);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
