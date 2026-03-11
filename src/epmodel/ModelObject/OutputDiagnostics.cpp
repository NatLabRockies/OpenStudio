/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputDiagnostics.hpp"
#include "ModelObject/OutputDiagnostics_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

OutputDiagnostics::OutputDiagnostics(const Model& model) : ModelObject(OutputDiagnostics::iddObjectType(), model) {}

OutputDiagnostics::OutputDiagnostics(std::shared_ptr<detail::OutputDiagnostics_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType OutputDiagnostics::iddObjectType() {
  return IddObjectType::Output_Diagnostics;
}

}  // namespace epmodel
}  // namespace openstudio
