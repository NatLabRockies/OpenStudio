/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ComplexFenestrationPropertySolarAbsorbedLayers.hpp"
#include "ComplexFenestrationPropertySolarAbsorbedLayers_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ComplexFenestrationPropertySolarAbsorbedLayers::ComplexFenestrationPropertySolarAbsorbedLayers(const Model& model)
    : ModelObject(ComplexFenestrationPropertySolarAbsorbedLayers::iddObjectType(), model) {}

  ComplexFenestrationPropertySolarAbsorbedLayers::ComplexFenestrationPropertySolarAbsorbedLayers(
    std::shared_ptr<detail::ComplexFenestrationPropertySolarAbsorbedLayers_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ComplexFenestrationPropertySolarAbsorbedLayers::iddObjectType() {
    return IddObjectType::ComplexFenestrationProperty_SolarAbsorbedLayers;
  }

}  // namespace epmodel
}  // namespace openstudio
