/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LayeredConstruction/Construction.hpp"
#include "LayeredConstruction/Construction_Impl.hpp"

#include "Model.hpp"
#include "Material/Material.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  Construction::Construction(const Model& model) : LayeredConstruction(Construction::iddObjectType(), model) {}

  Construction::Construction(std::shared_ptr<detail::Construction_Impl> impl) : LayeredConstruction(std::move(impl)) {}

  IddObjectType Construction::iddObjectType() {
    return IddObjectType::Construction;
  }

  Construction Construction::reverseConstruction() const {
    return getImpl<detail::Construction_Impl>()->reverseConstruction();
  }

  namespace detail {

    Construction Construction_Impl::reverseConstruction() const {
      if (this->isSymmetric()) {
        return this->getObject<Construction>();
      }

      // Functionally equivalent to the following, but we want to build vector layers only once
      // for (const auto& other : model().getConcreteModelObjects<Construction>()) {
      //   if (this->reverseEqualLayers(other)) {
      //     return other;
      //   }
      // }

      std::vector<Material> reverseLayers(this->layers());
      std::ranges::reverse(reverseLayers);

      Model model = this->model();
      for (const auto& other : model.getConcreteModelObjects<Construction>()) {
        if (std::ranges::equal(reverseLayers, other.layers(), [](const Material& a, const Material& b) { return a.handle() == b.handle(); })) {
          return other;
        }
      }

      // TODO: this should also copy (and modify) standards information object

      // no match, make one
      Construction result(model);
      result.setName(this->name().get() + " Reversed");
      result.setLayers(reverseLayers);

      return result;
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
