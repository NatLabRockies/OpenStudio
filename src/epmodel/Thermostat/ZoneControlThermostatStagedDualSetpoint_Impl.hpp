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
      bool setNumberofHeatingStages(int numberofHeatingStages);

      double heatingThrottlingTemperatureRange() const;
      bool setHeatingThrottlingTemperatureRange(double heatingThrottlingTemperatureRange);

      double stage1HeatingTemperatureOffset() const;
      bool setStage1HeatingTemperatureOffset(double stage1HeatingTemperatureOffset);

      double stage2HeatingTemperatureOffset() const;
      bool setStage2HeatingTemperatureOffset(double stage2HeatingTemperatureOffset);

      double stage3HeatingTemperatureOffset() const;
      bool setStage3HeatingTemperatureOffset(double stage3HeatingTemperatureOffset);

      double stage4HeatingTemperatureOffset() const;
      bool setStage4HeatingTemperatureOffset(double stage4HeatingTemperatureOffset);

      int numberofCoolingStages() const;
      bool setNumberofCoolingStages(int numberofCoolingStages);

      double coolingThrottlingTemperatureRange() const;
      bool setCoolingThrottlingTemperatureRange(double coolingThrottlingTemperatureRange);

      double stage1CoolingTemperatureOffset() const;
      bool setStage1CoolingTemperatureOffset(double stage1CoolingTemperatureOffset);

      double stage2CoolingTemperatureOffset() const;
      bool setStage2CoolingTemperatureOffset(double stage2CoolingTemperatureOffset);

      double stage3CoolingTemperatureOffset() const;
      bool setStage3CoolingTemperatureOffset(double stage3CoolingTemperatureOffset);

      double stage4CoolingTemperatureOffset() const;
      bool setStage4CoolingTemperatureOffset(double stage4CoolingTemperatureOffset);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
