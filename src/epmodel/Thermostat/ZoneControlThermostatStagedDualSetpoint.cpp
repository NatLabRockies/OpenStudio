/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Thermostat/ZoneControlThermostatStagedDualSetpoint.hpp"
#include "Thermostat/ZoneControlThermostatStagedDualSetpoint_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneControl_Thermostat_StagedDualSetpoint_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneControlThermostatStagedDualSetpoint::ZoneControlThermostatStagedDualSetpoint(const Model& model)
    : ModelObject(ZoneControlThermostatStagedDualSetpoint::iddObjectType(), model) {}

  ZoneControlThermostatStagedDualSetpoint::ZoneControlThermostatStagedDualSetpoint(
    std::shared_ptr<detail::ZoneControlThermostatStagedDualSetpoint_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlThermostatStagedDualSetpoint::iddObjectType() {
    return IddObjectType::ZoneControl_Thermostat_StagedDualSetpoint;
  }

  int ZoneControlThermostatStagedDualSetpoint::numberofHeatingStages() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->numberofHeatingStages();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setNumberofHeatingStages(int numberofHeatingStages) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setNumberofHeatingStages(numberofHeatingStages);
  }

  double ZoneControlThermostatStagedDualSetpoint::heatingThrottlingTemperatureRange() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->heatingThrottlingTemperatureRange();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setHeatingThrottlingTemperatureRange(double heatingThrottlingTemperatureRange) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setHeatingThrottlingTemperatureRange(heatingThrottlingTemperatureRange);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage1HeatingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage1HeatingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage1HeatingTemperatureOffset(double stage1HeatingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage1HeatingTemperatureOffset(stage1HeatingTemperatureOffset);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage2HeatingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage2HeatingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage2HeatingTemperatureOffset(double stage2HeatingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage2HeatingTemperatureOffset(stage2HeatingTemperatureOffset);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage3HeatingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage3HeatingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage3HeatingTemperatureOffset(double stage3HeatingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage3HeatingTemperatureOffset(stage3HeatingTemperatureOffset);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage4HeatingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage4HeatingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage4HeatingTemperatureOffset(double stage4HeatingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage4HeatingTemperatureOffset(stage4HeatingTemperatureOffset);
  }

  int ZoneControlThermostatStagedDualSetpoint::numberofCoolingStages() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->numberofCoolingStages();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setNumberofCoolingStages(int numberofCoolingStages) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setNumberofCoolingStages(numberofCoolingStages);
  }

  double ZoneControlThermostatStagedDualSetpoint::coolingThrottlingTemperatureRange() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->coolingThrottlingTemperatureRange();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setCoolingThrottlingTemperatureRange(double coolingThrottlingTemperatureRange) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setCoolingThrottlingTemperatureRange(coolingThrottlingTemperatureRange);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage1CoolingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage1CoolingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage1CoolingTemperatureOffset(double stage1CoolingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage1CoolingTemperatureOffset(stage1CoolingTemperatureOffset);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage2CoolingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage2CoolingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage2CoolingTemperatureOffset(double stage2CoolingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage2CoolingTemperatureOffset(stage2CoolingTemperatureOffset);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage3CoolingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage3CoolingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage3CoolingTemperatureOffset(double stage3CoolingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage3CoolingTemperatureOffset(stage3CoolingTemperatureOffset);
  }

  double ZoneControlThermostatStagedDualSetpoint::stage4CoolingTemperatureOffset() const {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->stage4CoolingTemperatureOffset();
  }

  bool ZoneControlThermostatStagedDualSetpoint::setStage4CoolingTemperatureOffset(double stage4CoolingTemperatureOffset) {
    return getImpl<detail::ZoneControlThermostatStagedDualSetpoint_Impl>()->setStage4CoolingTemperatureOffset(stage4CoolingTemperatureOffset);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int ZoneControlThermostatStagedDualSetpoint_Impl::numberofHeatingStages() const {
      const auto value = getInt(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::NumberofHeatingStages, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setNumberofHeatingStages(int numberofHeatingStages) {
      return setInt(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::NumberofHeatingStages, numberofHeatingStages);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::heatingThrottlingTemperatureRange() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::HeatingThrottlingTemperatureRange, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setHeatingThrottlingTemperatureRange(double heatingThrottlingTemperatureRange) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::HeatingThrottlingTemperatureRange,
                       heatingThrottlingTemperatureRange);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage1HeatingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage1HeatingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage1HeatingTemperatureOffset(double stage1HeatingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage1HeatingTemperatureOffset, stage1HeatingTemperatureOffset);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage2HeatingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage2HeatingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage2HeatingTemperatureOffset(double stage2HeatingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage2HeatingTemperatureOffset, stage2HeatingTemperatureOffset);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage3HeatingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage3HeatingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage3HeatingTemperatureOffset(double stage3HeatingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage3HeatingTemperatureOffset, stage3HeatingTemperatureOffset);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage4HeatingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage4HeatingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage4HeatingTemperatureOffset(double stage4HeatingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage4HeatingTemperatureOffset, stage4HeatingTemperatureOffset);
    }

    int ZoneControlThermostatStagedDualSetpoint_Impl::numberofCoolingStages() const {
      const auto value = getInt(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::NumberofCoolingStages, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setNumberofCoolingStages(int numberofCoolingStages) {
      return setInt(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::NumberofCoolingStages, numberofCoolingStages);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::coolingThrottlingTemperatureRange() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::CoolingThrottlingTemperatureRange, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setCoolingThrottlingTemperatureRange(double coolingThrottlingTemperatureRange) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::CoolingThrottlingTemperatureRange,
                       coolingThrottlingTemperatureRange);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage1CoolingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage1CoolingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage1CoolingTemperatureOffset(double stage1CoolingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage1CoolingTemperatureOffset, stage1CoolingTemperatureOffset);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage2CoolingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage2CoolingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage2CoolingTemperatureOffset(double stage2CoolingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage2CoolingTemperatureOffset, stage2CoolingTemperatureOffset);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage3CoolingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage3CoolingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage3CoolingTemperatureOffset(double stage3CoolingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage3CoolingTemperatureOffset, stage3CoolingTemperatureOffset);
    }

    double ZoneControlThermostatStagedDualSetpoint_Impl::stage4CoolingTemperatureOffset() const {
      const auto value = getDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage4CoolingTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneControlThermostatStagedDualSetpoint_Impl::setStage4CoolingTemperatureOffset(double stage4CoolingTemperatureOffset) {
      return setDouble(openstudio::ZoneControl_Thermostat_StagedDualSetpointFields::Stage4CoolingTemperatureOffset, stage4CoolingTemperatureOffset);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
