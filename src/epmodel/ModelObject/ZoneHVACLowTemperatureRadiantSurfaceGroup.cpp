/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup.hpp"
#include "ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl.hpp"

#include "Model.hpp"
#include "PlanarSurface/Surface.hpp"
#include "PlanarSurface/Surface_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_SurfaceGroup_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  ZoneHVACLowTemperatureRadiantSurfaceGroup::ZoneHVACLowTemperatureRadiantSurfaceGroup(const Model& model)
    : ModelObject(ZoneHVACLowTemperatureRadiantSurfaceGroup::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>());
  }

  ZoneHVACLowTemperatureRadiantSurfaceGroup::ZoneHVACLowTemperatureRadiantSurfaceGroup(
    std::shared_ptr<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACLowTemperatureRadiantSurfaceGroup::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_SurfaceGroup;
  }

  std::vector<Surface> ZoneHVACLowTemperatureRadiantSurfaceGroup::surfaces() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->surfaces();
  }

  std::vector<double> ZoneHVACLowTemperatureRadiantSurfaceGroup::flowFractions() const {
    return getImpl<detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>()->flowFractions();
  }

  namespace detail {

    using SurfaceGroupFields = openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields;

    std::vector<Surface> ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl::surfaces() const {
      std::vector<Surface> result;
      for (const auto& group : extensibleGroups()) {
        if (auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>()) {
          if (auto object = workspaceGroup->getTarget(SurfaceGroupFields::SurfaceName)) {
            if (auto surface = object->optionalCast<Surface>()) {
              result.push_back(*surface);
            }
          }
        }
      }
      return result;
    }

    std::vector<double> ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl::flowFractions() const {
      std::vector<double> result;
      for (const auto& group : extensibleGroups()) {
        if (auto fraction = group.getDouble(SurfaceGroupFields::FlowFractionforSurface, true)) {
          result.push_back(*fraction);
        }
      }
      return result;
    }

    void ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl::clearSurfaces() {
      getObject<ModelObject>().clearExtensibleGroups();
    }

    bool ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl::addSurface(Surface& surface, double flowFraction) {
      auto group = getObject<ModelObject>().pushExtensibleGroup().cast<openstudio::WorkspaceExtensibleGroup>();
      if (!group.setPointer(SurfaceGroupFields::SurfaceName, surface.handle(), false)) {
        return false;
      }
      return group.setDouble(SurfaceGroupFields::FlowFractionforSurface, flowFraction);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
