/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"

#include "../../model/DefaultConstructionSet.hpp"
#include "../../model/DefaultConstructionSet_Impl.hpp"

#include "../../model/DefaultSurfaceConstructions.hpp"
#include "../../model/DefaultSubSurfaceConstructions.hpp"
#include "../../model/ConstructionBase.hpp"
#include "../../model/Building.hpp"
#include "../../model/BuildingStory.hpp"
#include "../../model/Space.hpp"
#include "../../model/Space_Impl.hpp"
#include "../../model/SpaceType.hpp"
#include "../../model/PlanarSurface.hpp"
#include "../../model/Surface.hpp"
#include "../../model/SubSurface.hpp"
#include "../../model/InteriorPartitionSurfaceGroup.hpp"
#include "../../model/InteriorPartitionSurface.hpp"

#include <utilities/idd/ConstructionAssignmentSet_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

  // Building Group: Building and Building SpaceType DefaultConstructionSets are merged and referenced by the E+ Building.
  void ForwardTranslator::mergeBuildingGroup(model::Model& model) {
    boost::optional<model::Building> building_ = model.building();
    if (!building_) {
      return;
    }

    if (auto defaultConstructionSet_ = building_->defaultConstructionSet()) {
      // E+ allows only setting the ConstructionAssignmentSet on Space or Building
      // OS has the following inheritance order:
      // Space -> SpaceType -> BuildingStory -|-> Building -> Building SpaceType
      // So we merge Building and Building SpaceType DefaultConstructionSets so we don't loose any information when translating to E+.
      if (boost::optional<SpaceType> buildingSpaceType_ = building_->spaceType()) {
        if (auto buildingSpaceTypeDefaultConstructionSet = buildingSpaceType_->defaultConstructionSet()) {
          LOG(Info, "Merging Building DefaultConstructionSet '" << defaultConstructionSet_->nameString()
                                                                << "' with its Building SpaceType DefaultConstructionSet '"
                                                                << buildingSpaceTypeDefaultConstructionSet->nameString() << "'");
          defaultConstructionSet_->merge(*buildingSpaceTypeDefaultConstructionSet);
        }
      }
    }
  }

  enum class ConstructionDistance
  {
    Space = 1,
    SpaceType = 2,
    BuildingStory = 3,
    Building = 4,
    BuildingSpaceType = 5
  };

  // Space Group: here, the Space, SpaceType and BuildingStory DefaultConstructionSets are merged (in that priority order)
  // and referenced by the E+ Space.
  // Rules:
  // - We merge by priority order, so the Space DefaultConstructionSet has the highest priority, then SpaceType, then BuildingStory.
  // - We shouldn't do anything if a higher inheritance level has a DefaultConstructionSet but it contributes nothing to the merged set
  // - TODO: should we consider a cutoff logic, where if a higher inheritance levels only set 1 or 2 surfaces, we should hard-assigned the
  // construction for these surfaces.
  void ForwardTranslator::resolveSpaceDefaultConstructionSetInheritance(model::Model& model) {
    for (auto& space : model.getConcreteModelObjects<model::Space>()) {

      // NOTE: I'm going to brute force it now, just to wrap my head around it, but it should probably either calling model/ functions or be
      // implemented there

      // Step 1: Collect PlanarSurfaces with defaulted constructions (Surface, SubSurface, InteriorPartitionSurface)
      std::vector<PlanarSurface> planar_surfaces;
      auto surfaces = space.surfaces();
      planar_surfaces.reserve(2 * surfaces.size());  // Initial guess
      for (Surface& surface : space.surfaces()) {
        if (surface.isConstructionDefaulted()) {
          planar_surfaces.push_back(surface);
        }
        for (SubSurface& subSurface : surface.subSurfaces()) {
          if (subSurface.isConstructionDefaulted()) {
            planar_surfaces.push_back(subSurface);
          }
        }
      }

      for (const InteriorPartitionSurfaceGroup& interiorPartitionSurfaceGroup : space.interiorPartitionSurfaceGroups()) {
        for (InteriorPartitionSurface& interiorPartitionSurface : interiorPartitionSurfaceGroup.interiorPartitionSurfaces()) {
          if (interiorPartitionSurface.isConstructionDefaulted()) {
            planar_surfaces.push_back(interiorPartitionSurface);
          }
        }
      }

      if (planar_surfaces.empty()) {
        LOG(Trace, "Space '" << space.nameString() << "' has no surfaces, subsurfaces or interior partitions with defaulted constructions, skipping");
        continue;
      }

      size_t n_space = 0;           // Space
      size_t n_space_type = 0;      // Space Type
      size_t n_building_story = 0;  // Building Story
      for (const PlanarSurface& planar_surface : planar_surfaces) {
        if (boost::optional<std::pair<ConstructionBase, int>> cwsd_ = space.getDefaultConstructionWithSearchDistance()) {
          auto distance = static_cast<ConstructionDistance>(cwsd_->second);
          if (distance == ConstructionDistance::Space) {
            ++n_space;
          } else if (distance == ConstructionDistance::SpaceType) {
            ++n_space_type;
          } else if (distance == ConstructionDistance::BuildingStory) {
            ++n_building_story;
          }
        }
      }

      if (n_space + n_space_type + n_building_story == 0) {
        LOG(Trace, "Space '" << space.nameString() << "' has no surfaces, subsurfaces or interior partitions with Constructions coming from the Space/SpaceType/BuildingStory level, skipping");
        continue;
      }

      // TODO: here I think I need to check if there's more than one distance type...
      const int nContributing = static_cast<int>(n_space > 0) + static_cast<int>(n_space_type > 0) + static_cast<int>(n_building_story > 0);
      if (nContributing == 1) {
        if (n_space_type > 0) {
          auto dcs = *space.spaceType()->defaultConstructionSet();
          LOG(Trace, "Space '" << space.nameString() << "': all constructions coming from the SpaceType Level, assigning its DefaultConstructionSet '" << dcs.nameString() << "'");
          space.setDefaultConstructionSet(dcs);
        } else if (n_building_story > 0) {
          auto dcs = *space.buildingStory()->defaultConstructionSet();
          LOG(Trace, "Space '" << space.nameString() << "': all constructions coming from the BuildingStory Level, assigning its DefaultConstructionSet '" << dcs.nameString() << "'");
          space.setDefaultConstructionSet(dcs);
        }
        continue;
      }

      auto [starting_dcs, start_name] = [&]() -> std::pair<DefaultConstructionSet, std::string> {
        if (n_space > 0) {
          return {*space.defaultConstructionSet(), "Space " + space.nameString()};
        } else if (n_space_type > 0) {
          return {*space.spaceType()->defaultConstructionSet(), "SpaceType " + space.spaceType()->nameString()};
        }
        // else if (n_building_story > 0) {
        return {*space.buildingStory()->defaultConstructionSet(), "BuildingStory " + space.buildingStory()->nameString()};
      }();


      auto directUseCount = starting_dcs.directUseCount();
      if (directUseCount > 1) {
        LOG(Trace, "Space '" << space.nameString() << "' has a shared DefaultConstructionSet coming from " << start_name << " named '" << starting_dcs.nameString()
            << "' that is used by " << directUseCount << " Objects. Cloning it to avoid mutating a real object.");
        starting_dcs = starting_dcs.clone(space.model()).cast<DefaultConstructionSet>();
        starting_dcs.setName(space.nameString() + " " + starting_dcs.nameString());
        space.setDefaultConstructionSet(starting_dcs);
      }
      if (n_space > 0){
        if (n_space_type > 0) {
          LOG(Info, "Merging Space DefaultConstructionSet '" << space.nameString() << "' with its SpaceType DefaultConstructionSet");
          // We KNOW it exists
          starting_dcs.merge(*space.spaceType()->defaultConstructionSet());
        }
        if (n_building_story > 0) {
          LOG(Info, "Merging Space DefaultConstructionSet '" << space.nameString() << "' with its BuildingStory DefaultConstructionSet");
          // We KNOW it exists
          starting_dcs.merge(*space.buildingStory()->defaultConstructionSet());
        }
      } else { // n_space_type is > 0 and n_building_story is > 0
        LOG(Info, "Merging Space DefaultConstructionSet '" << space.nameString() << "' with its SpaceType and BuildingStory DefaultConstructionSets");
        // We KNOW they exist
        starting_dcs.merge(*space.spaceType()->defaultConstructionSet());
        starting_dcs.merge(*space.buildingStory()->defaultConstructionSet());
      }
    }
  }

  void ForwardTranslator::resolveDefaultConstructionSetInheritance(model::Model& model) {

    if (m_forwardTranslatorOptions.excludeConstructionAssignmentSets()) {
      return;
    }

    // E+ allows only setting the ConstructionAssignmentSet on Space or Building
    // OS has the following inheritance order:
    //
    // Space -> SpaceType -> BuildingStory -> Building -> Building SpaceType
    // \_______________ _________________/    \______________ _____________/
    //                 V                                     V
    //            Space Group                         Building Group
    //
    // To avoid losing any information when translating to E+, we collapse each group into a single set:
    mergeBuildingGroup(model);
    resolveSpaceDefaultConstructionSetInheritance(model);
  }

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
