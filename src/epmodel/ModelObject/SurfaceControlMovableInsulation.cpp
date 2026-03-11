/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceControlMovableInsulation.hpp"
#include "SurfaceControlMovableInsulation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceControl_MovableInsulation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceControlMovableInsulation::SurfaceControlMovableInsulation(const Model& model)
    : ModelObject(SurfaceControlMovableInsulation::iddObjectType(), model) {
    OS_ASSERT(setInsulationType("Outside"));
  }

  SurfaceControlMovableInsulation::SurfaceControlMovableInsulation(std::shared_ptr<detail::SurfaceControlMovableInsulation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceControlMovableInsulation::iddObjectType() {
    return IddObjectType::SurfaceControl_MovableInsulation;
  }

  std::vector<std::string> SurfaceControlMovableInsulation::insulationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceControl_MovableInsulationFields::InsulationType);
  }

  std::string SurfaceControlMovableInsulation::insulationType() const {
    return getImpl<detail::SurfaceControlMovableInsulation_Impl>()->insulationType();
  }

  bool SurfaceControlMovableInsulation::setInsulationType(const std::string& insulationType) {
    return getImpl<detail::SurfaceControlMovableInsulation_Impl>()->setInsulationType(insulationType);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SurfaceControlMovableInsulation_Impl::insulationType() const {
      const auto value = getString(openstudio::SurfaceControl_MovableInsulationFields::InsulationType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfaceControlMovableInsulation_Impl::setInsulationType(const std::string& insulationType) {
      return setString(openstudio::SurfaceControl_MovableInsulationFields::InsulationType, insulationType);
    }

    std::vector<std::string> SurfaceControlMovableInsulation_Impl::insulationTypeValues() const {
      return openstudio::epmodel::SurfaceControlMovableInsulation::insulationTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
