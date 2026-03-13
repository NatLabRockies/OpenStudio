/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PipeOutdoor.hpp"
#include "StraightComponent/PipeOutdoor_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Pipe_Outdoor_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PipeOutdoor::PipeOutdoor(const Model& model) : StraightComponent(PipeOutdoor::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::PipeOutdoor_Impl>());

    bool ok = true;
    ok = setPipeInsideDiameter(0.05);
    OS_ASSERT(ok);
    ok = setPipeLength(100.0);
    OS_ASSERT(ok);
  }

  PipeOutdoor::PipeOutdoor(std::shared_ptr<detail::PipeOutdoor_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType PipeOutdoor::iddObjectType() {
    return IddObjectType::Pipe_Outdoor;
  }

  // Pipe:Outdoor PipeInsideDiameter
  double PipeOutdoor::pipeInsideDiameter() const {
    return getImpl<detail::PipeOutdoor_Impl>()->pipeInsideDiameter();
  }

  bool PipeOutdoor::setPipeInsideDiameter(double pipeInsideDiameter) {
    return getImpl<detail::PipeOutdoor_Impl>()->setPipeInsideDiameter(pipeInsideDiameter);
  }

  // Pipe:Outdoor PipeLength
  double PipeOutdoor::pipeLength() const {
    return getImpl<detail::PipeOutdoor_Impl>()->pipeLength();
  }

  bool PipeOutdoor::setPipeLength(double pipeLength) {
    return getImpl<detail::PipeOutdoor_Impl>()->setPipeLength(pipeLength);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Pipe:Outdoor PipeInsideDiameter
    double PipeOutdoor_Impl::pipeInsideDiameter() const {
      const auto value = getDouble(openstudio::Pipe_OutdoorFields::PipeInsideDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipeOutdoor_Impl::setPipeInsideDiameter(double pipeInsideDiameter) {
      return setDouble(openstudio::Pipe_OutdoorFields::PipeInsideDiameter, pipeInsideDiameter);
    }

    // Pipe:Outdoor PipeLength
    double PipeOutdoor_Impl::pipeLength() const {
      const auto value = getDouble(openstudio::Pipe_OutdoorFields::PipeLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipeOutdoor_Impl::setPipeLength(double pipeLength) {
      return setDouble(openstudio::Pipe_OutdoorFields::PipeLength, pipeLength);
    }

    unsigned PipeOutdoor_Impl::inletPort() const {
      // Relationship mapping only: Pipe:Outdoor Fluid Inlet Node Name
      return openstudio::Pipe_OutdoorFields::FluidInletNodeName;
    }

    unsigned PipeOutdoor_Impl::outletPort() const {
      // Relationship mapping only: Pipe:Outdoor Fluid Outlet Node Name
      return openstudio::Pipe_OutdoorFields::FluidOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
