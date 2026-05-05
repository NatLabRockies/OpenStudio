/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SolarCollectorUnglazedTranspiredMultisystem.hpp"
#include "SolarCollectorUnglazedTranspiredMultisystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SolarCollectorUnglazedTranspiredMultisystem::SolarCollectorUnglazedTranspiredMultisystem(const Model& model)
    : ModelObject(SolarCollectorUnglazedTranspiredMultisystem::iddObjectType(), model) {}

  SolarCollectorUnglazedTranspiredMultisystem::SolarCollectorUnglazedTranspiredMultisystem(
    std::shared_ptr<detail::SolarCollectorUnglazedTranspiredMultisystem_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SolarCollectorUnglazedTranspiredMultisystem::iddObjectType() {
    return IddObjectType::SolarCollector_UnglazedTranspired_Multisystem;
  }

}  // namespace epmodel
}  // namespace openstudio
