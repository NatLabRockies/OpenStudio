/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilCoolingDXSingleSpeed.hpp"
#include "CoilCoolingDXSingleSpeed_Impl.hpp"

#include "AirLoopHVAC.hpp"
#include "AirLoopHVACOutdoorAirSystem.hpp"
#include "CoilSystemCoolingDX.hpp"
#include "CoilSystemCoolingDX_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilCoolingDXSingleSpeed::CoilCoolingDXSingleSpeed(const Model& model) : StraightComponent(CoilCoolingDXSingleSpeed::iddObjectType(), model) {
  auto impl = getImpl<detail::CoilCoolingDXSingleSpeed_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

CoilCoolingDXSingleSpeed::CoilCoolingDXSingleSpeed(std::shared_ptr<detail::CoilCoolingDXSingleSpeed_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXSingleSpeed::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_SingleSpeed;
}

bool CoilCoolingDXSingleSpeed::addToNode(Node& node) {
  return getImpl<detail::CoilCoolingDXSingleSpeed_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilCoolingDXSingleSpeed_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_SingleSpeedFields::AirInletNodeName;
}

unsigned CoilCoolingDXSingleSpeed_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_SingleSpeedFields::AirOutletNodeName;
}

bool CoilCoolingDXSingleSpeed_Impl::addToNode(Node& node) {
  if (auto airLoop = node.airLoopHVAC()) {
    if (!airLoop->demandComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
    return false;
  }

  if (node.airLoopHVACOutdoorAirSystem()) {
    // openstudio::model allows some OA-system contexts only when the OA system
    // is attached to an AirLoopHVACDedicatedOutdoorAirSystem. epmodel does not
    // yet model that object, so keep this unsupported and explicit.
    return false;
  }

  return false;
}

boost::optional<CoilSystemCoolingDX> CoilCoolingDXSingleSpeed_Impl::coilSystemCoolingDX() const {
  const auto thisHandle = handle();

  for (const auto& system : model().getConcreteModelObjects<CoilSystemCoolingDX>()) {
    auto systemImpl = system.getImpl<openstudio::epmodel::detail::CoilSystemCoolingDX_Impl>();
    OS_ASSERT(systemImpl);
    auto coolingCoil = systemImpl->coolingCoil();
    if (coolingCoil && (coolingCoil->handle() == thisHandle)) {
      return system;
    }
  }

  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
