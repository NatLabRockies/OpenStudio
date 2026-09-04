/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ReverseTranslator.hpp"

#include "../../model/MasslessOpaqueMaterial.hpp"
#include "../../model/MasslessOpaqueMaterial_Impl.hpp"

#include <utilities/idd/Material_NoMass_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  OptionalModelObject ReverseTranslator::translateMaterialNoMass(const WorkspaceObject& workspaceObject) {
    OptionalModelObject result;
    if (workspaceObject.iddObject().type() != IddObjectType::Material_NoMass) {
      LOG(Error, "WorkspaceObject is not IddObjectType: Material:NoMass");
      return result;
    }

    openstudio::model::MasslessOpaqueMaterial MOMat(m_model);
    OptionalString optS = workspaceObject.name();
    if (optS) {
      MOMat.setName(*optS);
    }

    optS = workspaceObject.getString(Material_NoMassFields::Roughness);
    if (optS) {
      MOMat.setRoughness(*optS);
    }

    OptionalDouble d = workspaceObject.getDouble(Material_NoMassFields::ThermalResistance);
    if (d) {
      MOMat.setThermalResistance(*d);
    }

    d = workspaceObject.getDouble(Material_NoMassFields::ThermalAbsorptance);
    if (d) {
      MOMat.setThermalAbsorptance(*d);
    }

    d = workspaceObject.getDouble(Material_NoMassFields::SolarAbsorptance);
    if (d) {
      MOMat.setSolarAbsorptance(*d);
    }

    d = workspaceObject.getDouble(Material_NoMassFields::VisibleAbsorptance);
    if (d) {
      MOMat.setVisibleAbsorptance(*d);
    }

    // Inside-face absorptance fields have no IDD default and inherit the exterior value when blank.
    d = workspaceObject.getDouble(Material_NoMassFields::ThermalAbsorptanceInsideFace);
    if (d) {
      MOMat.setThermalAbsorptanceInsideFace(*d);
    }

    d = workspaceObject.getDouble(Material_NoMassFields::SolarAbsorptanceInsideFace);
    if (d) {
      MOMat.setSolarAbsorptanceInsideFace(*d);
    }

    d = workspaceObject.getDouble(Material_NoMassFields::VisibleAbsorptanceInsideFace);
    if (d) {
      MOMat.setVisibleAbsorptanceInsideFace(*d);
    }

    result = MOMat;
    return result;
  }

}  // namespace energyplus

}  // namespace openstudio
