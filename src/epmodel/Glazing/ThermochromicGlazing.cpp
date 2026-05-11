/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Glazing/ThermochromicGlazing.hpp"
#include "Glazing/ThermochromicGlazing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermochromicGlazing::ThermochromicGlazing(const Model& model) : Material(ThermochromicGlazing::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ThermochromicGlazing_Impl>());
  }

  ThermochromicGlazing::ThermochromicGlazing(std::shared_ptr<detail::ThermochromicGlazing_Impl> impl) : Material(std::move(impl)) {}

  IddObjectType ThermochromicGlazing::iddObjectType() {
    return IddObjectType::WindowMaterial_GlazingGroup_Thermochromic;
  }

}  // namespace epmodel
}  // namespace openstudio
