/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/ThermochromicGlazing.hpp"

#include "../../utilities/math/FloatCompare.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/Workspace.hpp"

#include <utilities/idd/WindowMaterial_GlazingGroup_Thermochromic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <algorithm>  // For sort

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateThermochromicGlazing(model::ThermochromicGlazing& modelObject) {

    auto groups = modelObject.thermochromicGroups();
    if (groups.empty()) {
      LOG(Warn, "ThermochromicGlazing '" << modelObject.nameString() << "' has no ThermochromicGroups. Cannot translate.");
      return boost::none;
    }
    // Instantiate an IdfObject of the class to store the values
    IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::WindowMaterial_GlazingGroup_Thermochromic, modelObject);

    // Sort by optical data temperature (ThermochromicGroup already has the operator< for this, but I'm making it clearer by using a lambda)
    std::sort(groups.begin(), groups.end(),
              [](const ThermochromicGroup& a, const ThermochromicGroup& b) { return a.opticalDataTemperature() < b.opticalDataTemperature(); });

    auto first_thickness = groups.front().standardGlazing().thickness();

    for (const auto& group : groups) {

      IdfExtensibleGroup eg = idfObject.pushExtensibleGroup();
      eg.setDouble(WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::OpticalDataTemperature, group.opticalDataTemperature());
      auto standardGlazing = group.standardGlazing();
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(standardGlazing)) {
        eg.setString(WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::WindowMaterialGlazingName, wo_->nameString());
      }

      // Check if the thickness is consistent across all groups
      if (!openstudio::equal(group.standardGlazing().thickness(), first_thickness)) {
        LOG(Warn, "ThermochromicGlazing '" << modelObject.nameString() << "' has inconsistent thicknesses across ThermochromicGroups. "
                                           << "Expected: " << first_thickness << ", found: " << group.standardGlazing().thickness());
      }
    }

    return idfObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
