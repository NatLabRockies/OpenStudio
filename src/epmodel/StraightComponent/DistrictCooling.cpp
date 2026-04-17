/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/DistrictCooling.hpp"
#include "StraightComponent/DistrictCooling_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/DistrictCooling_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  DistrictCooling::DistrictCooling(const Model& model) : StraightComponent(DistrictCooling::iddObjectType(), model) {
    autosizeNominalCapacity();

    auto capacityFractionSchedule = model.alwaysOnContinuousSchedule();
    OS_ASSERT(getImpl<detail::DistrictCooling_Impl>()->setCapacityFractionSchedule(capacityFractionSchedule));
  }

  DistrictCooling::DistrictCooling(std::shared_ptr<detail::DistrictCooling_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType DistrictCooling::iddObjectType() {
    return IddObjectType::DistrictCooling;
  }

  boost::optional<double> DistrictCooling::nominalCapacity() const {
    return getImpl<detail::DistrictCooling_Impl>()->nominalCapacity();
  }

  Schedule DistrictCooling::capacityFractionSchedule() const {
    return getImpl<detail::DistrictCooling_Impl>()->capacityFractionSchedule();
  }

  bool DistrictCooling::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::DistrictCooling_Impl>()->setNominalCapacity(nominalCapacity);
  }

  bool DistrictCooling::setCapacityFractionSchedule(Schedule& schedule) {
    return getImpl<detail::DistrictCooling_Impl>()->setCapacityFractionSchedule(schedule);
  }

  bool DistrictCooling::isNominalCapacityAutosized() const {
    return getImpl<detail::DistrictCooling_Impl>()->isNominalCapacityAutosized();
  }

  void DistrictCooling::autosizeNominalCapacity() {
    getImpl<detail::DistrictCooling_Impl>()->autosizeNominalCapacity();
  }

  boost::optional<double> DistrictCooling::autosizedNominalCapacity() const {
    return getImpl<detail::DistrictCooling_Impl>()->autosizedNominalCapacity();
  }

  bool DistrictCooling::addToNode(Node& node) {
    return getImpl<detail::DistrictCooling_Impl>()->addToNode(node);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned DistrictCooling_Impl::inletPort() const {
      return openstudio::DistrictCoolingFields::ChilledWaterInletNodeName;
    }

    unsigned DistrictCooling_Impl::outletPort() const {
      return openstudio::DistrictCoolingFields::ChilledWaterOutletNodeName;
    }

    bool DistrictCooling_Impl::addToNode(Node& node) {
      if (auto plant = node.plantLoop()) {
        if (plant->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    boost::optional<double> DistrictCooling_Impl::nominalCapacity() const {
      return getDouble(openstudio::DistrictCoolingFields::NominalCapacity, true);
    }

    Schedule DistrictCooling_Impl::capacityFractionSchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::DistrictCoolingFields::CapacityFractionScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool DistrictCooling_Impl::setCapacityFractionSchedule(Schedule& schedule) {
      return setSchedule(openstudio::DistrictCoolingFields::CapacityFractionScheduleName, "DistrictCooling", "Capacity Fraction", schedule);
    }

    bool DistrictCooling_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::DistrictCoolingFields::NominalCapacity, nominalCapacity);
    }

    bool DistrictCooling_Impl::isNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::DistrictCoolingFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void DistrictCooling_Impl::autosizeNominalCapacity() {
      OS_ASSERT(setString(openstudio::DistrictCoolingFields::NominalCapacity, "Autosize"));
    }

    boost::optional<double> DistrictCooling_Impl::autosizedNominalCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
