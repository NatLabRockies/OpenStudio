/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_ZONECONTROLTHERMOSTATSTAGEDDUALSETPOINT_IMPL_HPP
#define EPMODEL_THERMOSTAT_ZONECONTROLTHERMOSTATSTAGEDDUALSETPOINT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneControlThermostatStagedDualSetpoint_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneControlThermostatStagedDualSetpoint_Impl() override = default;

      int numberofHeatingStages() const;
      double heatingThrottlingTemperatureRange() const;
      double stage1HeatingTemperatureOffset() const;
      double stage2HeatingTemperatureOffset() const;
      double stage3HeatingTemperatureOffset() const;
      double stage4HeatingTemperatureOffset() const;

      int numberofCoolingStages() const;
      double coolingThrottlingTemperatureRange() const;
      double stage1CoolingTemperatureOffset() const;
      double stage2CoolingTemperatureOffset() const;
      double stage3CoolingTemperatureOffset() const;
      double stage4CoolingTemperatureOffset() const;

      bool setNumberofHeatingStages(int numberofHeatingStages);
      bool setHeatingThrottlingTemperatureRange(double heatingThrottlingTemperatureRange);
      bool setStage1HeatingTemperatureOffset(double stage1HeatingTemperatureOffset);
      bool setStage2HeatingTemperatureOffset(double stage2HeatingTemperatureOffset);
      bool setStage3HeatingTemperatureOffset(double stage3HeatingTemperatureOffset);
      bool setStage4HeatingTemperatureOffset(double stage4HeatingTemperatureOffset);

      bool setNumberofCoolingStages(int numberofCoolingStages);
      bool setCoolingThrottlingTemperatureRange(double coolingThrottlingTemperatureRange);
      bool setStage1CoolingTemperatureOffset(double stage1CoolingTemperatureOffset);
      bool setStage2CoolingTemperatureOffset(double stage2CoolingTemperatureOffset);
      bool setStage3CoolingTemperatureOffset(double stage3CoolingTemperatureOffset);
      bool setStage4CoolingTemperatureOffset(double stage4CoolingTemperatureOffset);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
