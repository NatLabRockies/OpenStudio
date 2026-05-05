/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/DistrictHeatingSteam.hpp"
#include "StraightComponent/DistrictHeatingSteam_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/DistrictHeating_Steam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  DistrictHeatingSteam::DistrictHeatingSteam(const Model& model) : StraightComponent(DistrictHeatingSteam::iddObjectType(), model) {
    autosizeNominalCapacity();

    auto capacityFractionSchedule = model.alwaysOnContinuousSchedule();
    OS_ASSERT(getImpl<detail::DistrictHeatingSteam_Impl>()->setCapacityFractionSchedule(capacityFractionSchedule));
  }

  DistrictHeatingSteam::DistrictHeatingSteam(std::shared_ptr<detail::DistrictHeatingSteam_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType DistrictHeatingSteam::iddObjectType() {
    return IddObjectType::DistrictHeating_Steam;
  }

  boost::optional<double> DistrictHeatingSteam::nominalCapacity() const {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->nominalCapacity();
  }

  Schedule DistrictHeatingSteam::capacityFractionSchedule() const {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->capacityFractionSchedule();
  }

  bool DistrictHeatingSteam::isNominalCapacityAutosized() const {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->isNominalCapacityAutosized();
  }

  boost::optional<double> DistrictHeatingSteam::autosizedNominalCapacity() const {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->autosizedNominalCapacity();
  }

  bool DistrictHeatingSteam::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->setNominalCapacity(nominalCapacity);
  }

  bool DistrictHeatingSteam::setCapacityFractionSchedule(Schedule& schedule) {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->setCapacityFractionSchedule(schedule);
  }

  void DistrictHeatingSteam::autosizeNominalCapacity() {
    getImpl<detail::DistrictHeatingSteam_Impl>()->autosizeNominalCapacity();
  }

  bool DistrictHeatingSteam::addToNode(Node& node) {
    return getImpl<detail::DistrictHeatingSteam_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool DistrictHeatingSteam_Impl::addToNode(Node& node) {
      if (auto plant = node.plantLoop()) {
        if (plant->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    unsigned DistrictHeatingSteam_Impl::inletPort() const {
      return openstudio::DistrictHeating_SteamFields::SteamInletNodeName;
    }

    unsigned DistrictHeatingSteam_Impl::outletPort() const {
      return openstudio::DistrictHeating_SteamFields::SteamOutletNodeName;
    }

    boost::optional<double> DistrictHeatingSteam_Impl::nominalCapacity() const {
      return getDouble(openstudio::DistrictHeating_SteamFields::NominalCapacity, true);
    }

    Schedule DistrictHeatingSteam_Impl::capacityFractionSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::DistrictHeating_SteamFields::CapacityFractionScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool DistrictHeatingSteam_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::DistrictHeating_SteamFields::NominalCapacity, nominalCapacity);
    }

    bool DistrictHeatingSteam_Impl::setCapacityFractionSchedule(Schedule& schedule) {
      return setSchedule(openstudio::DistrictHeating_SteamFields::CapacityFractionScheduleName, "DistrictHeatingSteam", "Capacity Fraction",
                         schedule);
    }

    bool DistrictHeatingSteam_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::DistrictHeating_SteamFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> DistrictHeatingSteam_Impl::autosizedNominalCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    void DistrictHeatingSteam_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::DistrictHeating_SteamFields::NominalCapacity, "Autosize"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
