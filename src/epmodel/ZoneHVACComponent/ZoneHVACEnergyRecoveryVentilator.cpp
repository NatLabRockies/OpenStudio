/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"
#include "ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_FieldEnums.hxx>
#include <utilities/core/StringHelpers.hpp>

namespace openstudio {
namespace epmodel {

  ZoneHVACEnergyRecoveryVentilator::ZoneHVACEnergyRecoveryVentilator(const Model& model)
    : ZoneHVACComponent(ZoneHVACEnergyRecoveryVentilator::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>());
    autosizeSupplyAirFlowRate();
    autosizeExhaustAirFlowRate();
    OS_ASSERT(setVentilationRateperUnitFloorArea(0.000508));
    OS_ASSERT(setVentilationRateperOccupant(0.00236));
  }

  ZoneHVACEnergyRecoveryVentilator::ZoneHVACEnergyRecoveryVentilator(std::shared_ptr<detail::ZoneHVACEnergyRecoveryVentilator_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACEnergyRecoveryVentilator::iddObjectType() {
    return IddObjectType::ZoneHVAC_EnergyRecoveryVentilator;
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilator::supplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->supplyAirFlowRate();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setSupplyAirFlowRate(double supplyAirFlowRate) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setSupplyAirFlowRate(supplyAirFlowRate);
  }

  bool ZoneHVACEnergyRecoveryVentilator::isSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->isSupplyAirFlowRateAutosized();
  }

  void ZoneHVACEnergyRecoveryVentilator::autosizeSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->autosizeSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACEnergyRecoveryVentilator::exhaustAirFlowRate() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->exhaustAirFlowRate();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setExhaustAirFlowRate(double exhaustAirFlowRate) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setExhaustAirFlowRate(exhaustAirFlowRate);
  }

  bool ZoneHVACEnergyRecoveryVentilator::isExhaustAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->isExhaustAirFlowRateAutosized();
  }

  void ZoneHVACEnergyRecoveryVentilator::autosizeExhaustAirFlowRate() {
    getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->autosizeExhaustAirFlowRate();
  }

  double ZoneHVACEnergyRecoveryVentilator::ventilationRateperUnitFloorArea() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->ventilationRateperUnitFloorArea();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setVentilationRateperUnitFloorArea(ventilationRateperUnitFloorArea);
  }

  double ZoneHVACEnergyRecoveryVentilator::ventilationRateperOccupant() const {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->ventilationRateperOccupant();
  }

  bool ZoneHVACEnergyRecoveryVentilator::setVentilationRateperOccupant(double ventilationRateperOccupant) {
    return getImpl<detail::ZoneHVACEnergyRecoveryVentilator_Impl>()->setVentilationRateperOccupant(ventilationRateperOccupant);
  }

  namespace detail {

    boost::optional<double> ZoneHVACEnergyRecoveryVentilator_Impl::supplyAirFlowRate() const {
      return getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, true);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setSupplyAirFlowRate(double supplyAirFlowRate) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, supplyAirFlowRate);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::isSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::autosizeSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_EnergyRecoveryVentilatorFields::SupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACEnergyRecoveryVentilator_Impl::exhaustAirFlowRate() const {
      return getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, true);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setExhaustAirFlowRate(double exhaustAirFlowRate) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, exhaustAirFlowRate);
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::isExhaustAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    void ZoneHVACEnergyRecoveryVentilator_Impl::autosizeExhaustAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_EnergyRecoveryVentilatorFields::ExhaustAirFlowRate, "autosize"));
    }

    double ZoneHVACEnergyRecoveryVentilator_Impl::ventilationRateperUnitFloorArea() const {
      const auto value = getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setVentilationRateperUnitFloorArea(double ventilationRateperUnitFloorArea) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperUnitFloorArea, ventilationRateperUnitFloorArea);
    }

    double ZoneHVACEnergyRecoveryVentilator_Impl::ventilationRateperOccupant() const {
      const auto value = getDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACEnergyRecoveryVentilator_Impl::setVentilationRateperOccupant(double ventilationRateperOccupant) {
      return setDouble(ZoneHVAC_EnergyRecoveryVentilatorFields::VentilationRateperOccupant, ventilationRateperOccupant);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
