/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/ThermochromicGlazing.hpp"
#include "../../model/StandardGlazing.hpp"
#include "../../model/StandardGlazing_Impl.hpp"

#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

#include <utilities/idd/WindowMaterial_GlazingGroup_Thermochromic_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<ModelObject> ReverseTranslator::translateWindowMaterialGlazingGroupThermochromic(const WorkspaceObject& workspaceObject) {

    openstudio::model::ThermochromicGlazing modelObject(m_model);

    // Name
    if (boost::optional<std::string> name_ = workspaceObject.name()) {
      modelObject.setName(name_.get());
    }

    // Extensible groups
    for (const IdfExtensibleGroup& eg : workspaceObject.extensibleGroups()) {
      auto weg = eg.cast<WorkspaceExtensibleGroup>();

      double opticalDataTemperature = 0.0;
      if (auto opticalDataTemperature_ = weg.getDouble(WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::OpticalDataTemperature)) {
        opticalDataTemperature = *opticalDataTemperature_;
      } else {
        LOG(Warn, "Extensible group " << eg.groupIndex() << "(0-indexed) has an opticalDataTemperature, but it's a required field. Assuming zero");
      }

      if (boost::optional<WorkspaceObject> wo_ =
            weg.getTarget(WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::WindowMaterialGlazingName)) {
        if (boost::optional<ModelObject> mo_ = translateAndMapWorkspaceObject(*wo_)) {
          if (boost::optional<StandardGlazing> standardGlazing_ = mo_->optionalCast<StandardGlazing>()) {
            modelObject.addThermochromicGroup(*standardGlazing_, opticalDataTemperature);
          } else {
            LOG(Warn, "Extensible group " << eg.groupIndex()
                                          << "(0-indexed) has a wrong type for WindowMaterialGlazingName, expected StandardGlazing, got "
                                          << mo_->briefDescription());
          }
        } else {
          LOG(Warn, "Could not translate WindowMaterialGlazingName for Extensible group " << eg.groupIndex());
        }
      } else {
        LOG(Warn, "Extensible group " << eg.groupIndex() << "(0-indexed) is missed the WindowMaterialGlazingName field, skipping group");
      }
    }

    return modelObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
