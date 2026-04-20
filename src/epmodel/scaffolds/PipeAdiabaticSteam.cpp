/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PipeAdiabaticSteam.hpp"
#include "PipeAdiabaticSteam_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

PipeAdiabaticSteam::PipeAdiabaticSteam(const Model& model) : ModelObject(PipeAdiabaticSteam::iddObjectType(), model) {}

PipeAdiabaticSteam::PipeAdiabaticSteam(std::shared_ptr<detail::PipeAdiabaticSteam_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType PipeAdiabaticSteam::iddObjectType() {
  return IddObjectType::Pipe_Adiabatic_Steam;
}

}  // namespace epmodel
}  // namespace openstudio
