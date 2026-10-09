/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/DefaultConstructionSet.hpp"

#include "../../model/DefaultSurfaceConstructions.hpp"
#include "../../model/DefaultSubSurfaceConstructions.hpp"
#include "../../model/ConstructionBase.hpp"

#include <utilities/idd/ConstructionAssignmentSet_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  boost::optional<IdfObject> ForwardTranslator::translateDefaultConstructionSet(model::DefaultConstructionSet& modelObject) {

    // Instantiate an IdfObject of the class to store the values
    IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::ConstructionAssignmentSet, modelObject);
    // Name
    idfObject.setName(modelObject.nameString());

    // Exterior Surface Construction Assignments Name: Optional Object
    if (boost::optional<DefaultSurfaceConstructions> exteriorSurfaceConstructionAssignments_ = modelObject.defaultExteriorSurfaceConstructions()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*exteriorSurfaceConstructionAssignments_)) {
        idfObject.setString(ConstructionAssignmentSetFields::ExteriorSurfaceConstructionAssignmentsName, wo_->nameString());
      }
    }

    // Interior Surface Construction Assignments Name: Optional Object
    if (boost::optional<DefaultSurfaceConstructions> interiorSurfaceConstructionAssignments_ = modelObject.defaultInteriorSurfaceConstructions()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*interiorSurfaceConstructionAssignments_)) {
        idfObject.setString(ConstructionAssignmentSetFields::InteriorSurfaceConstructionAssignmentsName, wo_->nameString());
      }
    }

    // Ground Contact Surface Construction Assignments Name: Optional Object
    if (boost::optional<DefaultSurfaceConstructions> groundContactSurfaceConstructionAssignments_ =
          modelObject.defaultGroundContactSurfaceConstructions()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*groundContactSurfaceConstructionAssignments_)) {
        idfObject.setString(ConstructionAssignmentSetFields::GroundContactSurfaceConstructionAssignmentsName, wo_->nameString());
      }
    }

    // Exterior SubSurface Construction Assignments Name: Optional Object
    if (boost::optional<DefaultSubSurfaceConstructions> exteriorSubSurfaceConstructionAssignments_ =
          modelObject.defaultExteriorSubSurfaceConstructions()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*exteriorSubSurfaceConstructionAssignments_)) {
        idfObject.setString(ConstructionAssignmentSetFields::ExteriorSubSurfaceConstructionAssignmentsName, wo_->nameString());
      }
    }

    // Interior SubSurface Construction Assignments Name: Optional Object
    if (boost::optional<DefaultSubSurfaceConstructions> interiorSubSurfaceConstructionAssignments_ =
          modelObject.defaultInteriorSubSurfaceConstructions()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*interiorSubSurfaceConstructionAssignments_)) {
        idfObject.setString(ConstructionAssignmentSetFields::InteriorSubSurfaceConstructionAssignmentsName, wo_->nameString());
      }
    }

    // Interior Partition Construction Name: Optional Object
    if (boost::optional<ConstructionBase> interiorPartitionConstruction_ = modelObject.interiorPartitionConstruction()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*interiorPartitionConstruction_)) {
        idfObject.setString(ConstructionAssignmentSetFields::InteriorPartitionConstructionName, wo_->nameString());
      }
    }

    // Adiabatic Surface Construction Name: Optional Object
    if (boost::optional<ConstructionBase> adiabaticSurfaceConstruction_ = modelObject.adiabaticSurfaceConstruction()) {
      if (boost::optional<IdfObject> wo_ = translateAndMapModelObject(*adiabaticSurfaceConstruction_)) {
        idfObject.setString(ConstructionAssignmentSetFields::AdiabaticSurfaceConstructionName, wo_->nameString());
      }
    }

    // NOTE: spaceShadingConstruction, buildingShadingConstruction, and siteShadingConstruction are not in the E+ object

    return idfObject;
  }  // End of translate function

}  // end namespace energyplus
}  // end namespace openstudio
