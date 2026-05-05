/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/MaterialPropertyGlazingSpectralData.hpp"
#include "ResourceObject/MaterialPropertyGlazingSpectralData_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyGlazingSpectralData::MaterialPropertyGlazingSpectralData(const Model& model)
    : ModelObject(MaterialPropertyGlazingSpectralData::iddObjectType(), model) {}

  MaterialPropertyGlazingSpectralData::MaterialPropertyGlazingSpectralData(std::shared_ptr<detail::MaterialPropertyGlazingSpectralData_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyGlazingSpectralData::iddObjectType() {
    return IddObjectType::MaterialProperty_GlazingSpectralData;
  }

}  // namespace epmodel
}  // namespace openstudio
