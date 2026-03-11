/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACZoneSplitter.hpp"
#include "AirLoopHVACZoneSplitter_Impl.hpp"

#include "AirLoopHVAC.hpp"
#include "AirLoopHVACSupplyPath.hpp"
#include "AirLoopHVACSupplyPath_Impl.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_ZoneSplitter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACZoneSplitter::AirLoopHVACZoneSplitter(const Model& model) : Splitter(AirLoopHVACZoneSplitter::iddObjectType(), model) {
    auto impl = getImpl<detail::AirLoopHVACZoneSplitter_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  AirLoopHVACZoneSplitter::AirLoopHVACZoneSplitter(std::shared_ptr<detail::AirLoopHVACZoneSplitter_Impl> impl) : Splitter(std::move(impl)) {}

  IddObjectType AirLoopHVACZoneSplitter::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ZoneSplitter;
  }

  boost::optional<AirLoopHVAC> AirLoopHVACZoneSplitter::airLoopHVAC() const {
    const auto self = cast<ModelObject>();
    const auto airLoops = model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>();
    const auto it = std::ranges::find_if(airLoops, [&](const openstudio::epmodel::AirLoopHVAC& airLoop) {
      auto impl = airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
      const auto supplyPath = impl->airLoopHVACSupplyPath();
      const auto components = supplyPath.components();
      return std::ranges::find(components, self) != components.end();
    });
    if (it != airLoops.end()) {
      return *it;
    }
    return boost::none;
  }

  unsigned AirLoopHVACZoneSplitter::inletPort() const {
    return static_cast<unsigned>(openstudio::AirLoopHVAC_ZoneSplitterFields::InletNodeName);
  }

unsigned AirLoopHVACZoneSplitter::outletPort(unsigned branchIndex) const {
  return numNonextensibleFields() + branchIndex;
}

  unsigned AirLoopHVACZoneSplitter::nextOutletPort() const {
    return outletPort(nextBranchIndex());
  }

std::vector<ModelObject> AirLoopHVACZoneSplitter::outletModelObjects() const {
  return Splitter::outletModelObjects();
}

  unsigned AirLoopHVACZoneSplitter::nextBranchIndex() const {
    return static_cast<unsigned>(outletModelObjects().size());
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<openstudio::epmodel::Node> AirLoopHVACZoneSplitter_Impl::inletNode() const {
  if (auto node = getObject<openstudio::epmodel::AirLoopHVACZoneSplitter>().getModelObjectTarget<openstudio::epmodel::Node>(
        openstudio::AirLoopHVAC_ZoneSplitterFields::InletNodeName)) {
    return node;
  }

  return boost::none;
}

bool AirLoopHVACZoneSplitter_Impl::setInletNode(const openstudio::epmodel::Node& node) {
  return setPointer(openstudio::AirLoopHVAC_ZoneSplitterFields::InletNodeName, node.handle(), false);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
