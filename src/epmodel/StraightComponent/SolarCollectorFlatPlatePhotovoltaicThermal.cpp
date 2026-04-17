/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SolarCollectorFlatPlatePhotovoltaicThermal.hpp"
#include "StraightComponent/SolarCollectorFlatPlatePhotovoltaicThermal_Impl.hpp"

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SolarCollector_FlatPlate_PhotovoltaicThermal_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorFlatPlatePhotovoltaicThermal::SolarCollectorFlatPlatePhotovoltaicThermal(const Model& model)
  : StraightComponent(SolarCollectorFlatPlatePhotovoltaicThermal::iddObjectType(), model) {}

SolarCollectorFlatPlatePhotovoltaicThermal::SolarCollectorFlatPlatePhotovoltaicThermal(
  std::shared_ptr<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType SolarCollectorFlatPlatePhotovoltaicThermal::iddObjectType() {
  return IddObjectType::SolarCollector_FlatPlate_PhotovoltaicThermal;
}

boost::optional<double> SolarCollectorFlatPlatePhotovoltaicThermal::designFlowRate() const {
  return getImpl<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl>()->designFlowRate();
}

bool SolarCollectorFlatPlatePhotovoltaicThermal::isDesignFlowRateAutosized() const {
  return getImpl<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl>()->isDesignFlowRateAutosized();
}

boost::optional<double> SolarCollectorFlatPlatePhotovoltaicThermal::autosizedDesignFlowRate() const {
  return getImpl<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl>()->autosizedDesignFlowRate();
}

bool SolarCollectorFlatPlatePhotovoltaicThermal::setDesignFlowRate(double designFlowRate) {
  return getImpl<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl>()->setDesignFlowRate(designFlowRate);
}

void SolarCollectorFlatPlatePhotovoltaicThermal::resetDesignFlowRate() {
  getImpl<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl>()->resetDesignFlowRate();
}

void SolarCollectorFlatPlatePhotovoltaicThermal::autosizeDesignFlowRate() {
  getImpl<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl>()->autosizeDesignFlowRate();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

bool isAirWorkingFluid(const ModelObject_Impl& impl) {
  if (auto value =
        impl.getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, true)) {
    return openstudio::istringEqual(*value, "Air");
  }
  return false;
}

}  // namespace

unsigned SolarCollectorFlatPlatePhotovoltaicThermal_Impl::inletPort() const {
  if (isAirWorkingFluid(*this)) {
    return openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirInletNodeName;
  }
  return openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterInletNodeName;
}

unsigned SolarCollectorFlatPlatePhotovoltaicThermal_Impl::outletPort() const {
  if (isAirWorkingFluid(*this)) {
    return openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::AirOutletNodeName;
  }
  return openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::WaterOutletNodeName;
}

bool SolarCollectorFlatPlatePhotovoltaicThermal_Impl::addToNode(Node& node) {
  if (auto plantLoop = node.plantLoop()) {
    if (plantLoop->supplyComponent(node.handle())) {
      if (auto hvacComponent = getObject<openstudio::epmodel::HVACComponent>(); hvacComponent.loop()) {
        if (!removeFromLoop()) {
          return false;
        }
      }
      if (!setString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, "Water")) {
        return false;
      }
      return StraightComponent_Impl::addToNode(node);
    }
    return false;
  }

  if (auto oaSystem = node.airLoopHVACOutdoorAirSystem()) {
    if (oaSystem->oaComponent(node.handle())) {
      if (auto hvacComponent = getObject<openstudio::epmodel::HVACComponent>(); hvacComponent.loop()) {
        if (!removeFromLoop()) {
          return false;
        }
      }
      if (!setString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::ThermalWorkingFluidType, "Air")) {
        return false;
      }
      return StraightComponent_Impl::addToNode(node);
    }
  }

  return false;
}

boost::optional<double> SolarCollectorFlatPlatePhotovoltaicThermal_Impl::designFlowRate() const {

  return getDouble(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::DesignFlowRate, true);
}

bool SolarCollectorFlatPlatePhotovoltaicThermal_Impl::isDesignFlowRateAutosized() const {
  if (auto value = getString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::DesignFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

boost::optional<double> SolarCollectorFlatPlatePhotovoltaicThermal_Impl::autosizedDesignFlowRate() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

bool SolarCollectorFlatPlatePhotovoltaicThermal_Impl::setDesignFlowRate(double designFlowRate) {
  return setDouble(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::DesignFlowRate, designFlowRate);
}

void SolarCollectorFlatPlatePhotovoltaicThermal_Impl::resetDesignFlowRate() {
  OS_ASSERT(setString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::DesignFlowRate, ""));
}

void SolarCollectorFlatPlatePhotovoltaicThermal_Impl::autosizeDesignFlowRate() {
  OS_ASSERT(setString(openstudio::SolarCollector_FlatPlate_PhotovoltaicThermalFields::DesignFlowRate, "autosize"));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
