/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LayeredConstruction/Construction.hpp"
#include "LayeredConstruction/Construction_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  Construction::Construction(const Model& model) : ModelObject(Construction::iddObjectType(), model) {}

  Construction::Construction(std::shared_ptr<detail::Construction_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Construction::iddObjectType() {
    return IddObjectType::Construction;
  }

}  // namespace epmodel
}  // namespace openstudio
