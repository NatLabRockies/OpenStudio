/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlHumidistat.hpp"
#include "ZoneControlHumidistat_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneControlHumidistat::ZoneControlHumidistat(const Model& model) : ModelObject(ZoneControlHumidistat::iddObjectType(), model) {}

  ZoneControlHumidistat::ZoneControlHumidistat(std::shared_ptr<detail::ZoneControlHumidistat_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlHumidistat::iddObjectType() {
    return {IddObjectType::ZoneControl_Humidistat};
  }

}  // namespace epmodel
}  // namespace openstudio
