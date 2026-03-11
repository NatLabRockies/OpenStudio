/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilSystemCoolingDX.hpp"
#include "CoilSystemCoolingDX_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilSystemCoolingDX::CoilSystemCoolingDX(const Model& model) : StraightComponent(CoilSystemCoolingDX::iddObjectType(), model) {
  auto impl = getImpl<detail::CoilSystemCoolingDX_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

CoilSystemCoolingDX::CoilSystemCoolingDX(std::shared_ptr<detail::CoilSystemCoolingDX_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType CoilSystemCoolingDX::iddObjectType() {
  return IddObjectType::CoilSystem_Cooling_DX;
}

bool CoilSystemCoolingDX::addToNode(Node& node) {
  return getImpl<detail::CoilSystemCoolingDX_Impl>()->addToNode(node);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilSystemCoolingDX_Impl::inletPort() const {
  return openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemInletNodeName;
}

unsigned CoilSystemCoolingDX_Impl::outletPort() const {
  return openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemOutletNodeName;
}

bool CoilSystemCoolingDX_Impl::addToNode(Node& node) {
  return StraightComponent_Impl::addToNode(node);
}

boost::optional<ModelObject> CoilSystemCoolingDX_Impl::coolingCoil() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
