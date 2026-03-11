/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilHeatingGas.hpp"
#include "CoilHeatingGas_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingGas::CoilHeatingGas(const Model& model) : StraightComponent(CoilHeatingGas::iddObjectType(), model) {
  auto impl = getImpl<detail::CoilHeatingGas_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

CoilHeatingGas::CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingGas::iddObjectType() {
  return IddObjectType::Coil_Heating_Fuel;
}

bool CoilHeatingGas::addToNode(Node& node) {
  return getImpl<detail::CoilHeatingGas_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingGas_Impl::inletPort() const {
  return openstudio::Coil_Heating_FuelFields::AirInletNodeName;
}

unsigned CoilHeatingGas_Impl::outletPort() const {
  return openstudio::Coil_Heating_FuelFields::AirOutletNodeName;
}

bool CoilHeatingGas_Impl::addToNode(Node& node) {
  if (auto airLoop = node.airLoopHVAC()) {
    if (!airLoop->demandComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
    return false;
  }

  // For current epmodel scope, OA-system insertion is allowed only when the
  // target node participates in modeled OA-system topology.
  if (node.airLoopHVACOutdoorAirSystem()) {
    return StraightComponent_Impl::addToNode(node);
  }

  return false;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
