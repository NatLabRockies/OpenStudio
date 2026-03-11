/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertyIncidentSolarMultiplier.hpp"
#include "SurfacePropertyIncidentSolarMultiplier_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SurfaceProperty_IncidentSolarMultiplier_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyIncidentSolarMultiplier::SurfacePropertyIncidentSolarMultiplier(const Model& model)
    : ModelObject(SurfacePropertyIncidentSolarMultiplier::iddObjectType(), model) {
    OS_ASSERT(setIncidentSolarMultiplier(1.0));
  }

  SurfacePropertyIncidentSolarMultiplier::SurfacePropertyIncidentSolarMultiplier(
    std::shared_ptr<detail::SurfacePropertyIncidentSolarMultiplier_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyIncidentSolarMultiplier::iddObjectType() {
    return IddObjectType::SurfaceProperty_IncidentSolarMultiplier;
  }

  double SurfacePropertyIncidentSolarMultiplier::incidentSolarMultiplier() const {
    return getImpl<detail::SurfacePropertyIncidentSolarMultiplier_Impl>()->incidentSolarMultiplier();
  }

  bool SurfacePropertyIncidentSolarMultiplier::setIncidentSolarMultiplier(double incidentSolarMultiplier) {
    return getImpl<detail::SurfacePropertyIncidentSolarMultiplier_Impl>()->setIncidentSolarMultiplier(incidentSolarMultiplier);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SurfacePropertyIncidentSolarMultiplier_Impl::incidentSolarMultiplier() const {
      const auto value = getDouble(SurfaceProperty_IncidentSolarMultiplierFields::IncidentSolarMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyIncidentSolarMultiplier_Impl::setIncidentSolarMultiplier(double incidentSolarMultiplier) {
      return setDouble(SurfaceProperty_IncidentSolarMultiplierFields::IncidentSolarMultiplier, incidentSolarMultiplier);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
