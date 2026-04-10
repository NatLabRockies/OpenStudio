/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_IMPL_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class HVACComponent;
  class ModelObject;
  class Surface;
  class CoilHeatingLowTempRadiantConstFlow;
  class CoilCoolingLowTempRadiantConstFlow;
  class ZoneHVACLowTempRadiantConstFlowDesign;
  class ZoneHVACLowTemperatureRadiantSurfaceGroup;

  namespace detail {

    class CoilHeatingLowTempRadiantConstFlow_Impl;
    class CoilCoolingLowTempRadiantConstFlow_Impl;

    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow& parent);
    std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow& parent);

    class EPMODEL_API ZoneHVACLowTempRadiantConstFlow_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACLowTempRadiantConstFlow_Impl() override = default;

      unsigned inletPort() const;
      unsigned outletPort() const;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      boost::optional<std::string> radiantSurfaceType() const;
      bool setRadiantSurfaceType(const std::string& radiantSurfaceType);
      void resetRadiantSurfaceType();

      std::vector<Surface> surfaces() const;

      CoilHeatingLowTempRadiantConstFlow heatingCoil() const;
      bool setHeatingCoil(HVACComponent& heatingCoil);
      CoilCoolingLowTempRadiantConstFlow coolingCoil() const;
      bool setCoolingCoil(HVACComponent& coolingCoil);

      boost::optional<Schedule> pumpFlowRateSchedule() const;
      bool setPumpFlowRateSchedule(Schedule& schedule);
      void resetPumpFlowRateSchedule();

      boost::optional<Schedule> changeoverDelayTimePeriodSchedule() const;
      bool setChangeoverDelayTimePeriodSchedule(Schedule& schedule);
      void resetChangeoverDelayTimePeriodSchedule();

      std::vector<ModelObject> children() const override;
      void doCanonicalize(LoadContext& context) override;

      boost::optional<double> hydronicTubingLength() const;
      boost::optional<double> autosizedHydronicTubingLength() const;
      bool isHydronicTubingLengthAutosized() const;
      bool setHydronicTubingLength(double hydronicTubingLength);
      void autosizeHydronicTubingLength();

      boost::optional<double> ratedFlowRate() const;
      boost::optional<double> autosizedRatedFlowRate() const;
      bool isRatedFlowRateAutosized() const;
      bool setRatedFlowRate(double ratedFlowRate);
      void autosizeRatedFlowRate();

      double ratedPumpHead() const;
      bool isRatedPumpHeadDefaulted() const;
      bool setRatedPumpHead(double ratedPumpHead);
      void resetRatedPumpHead();

      boost::optional<double> ratedPowerConsumption() const;
      bool setRatedPowerConsumption(double ratedPowerConsumption);
      void resetRatedPowerConsumption();

      std::string numberofCircuits() const;
      bool isNumberofCircuitsDefaulted() const;
      bool setNumberofCircuits(const std::string& numberofCircuits);
      void resetNumberofCircuits();

      double circuitLength() const;
      bool isCircuitLengthDefaulted() const;
      bool setCircuitLength(double circuitLength);
      void resetCircuitLength();

      std::string fluidtoRadiantSurfaceHeatTransferModel() const;
      bool isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const;
      bool setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel);
      void resetFluidtoRadiantSurfaceHeatTransferModel();

      double hydronicTubingInsideDiameter() const;
      bool isHydronicTubingInsideDiameterDefaulted() const;
      bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);
      void resetHydronicTubingInsideDiameter();

      double hydronicTubingOutsideDiameter() const;
      bool isHydronicTubingOutsideDiameterDefaulted() const;
      bool setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter);
      void resetHydronicTubingOutsideDiameter();

      double hydronicTubingConductivity() const;
      bool isHydronicTubingConductivityDefaulted() const;
      bool setHydronicTubingConductivity(double hydronicTubingConductivity);
      void resetHydronicTubingConductivity();

      std::string temperatureControlType() const;
      bool isTemperatureControlTypeDefaulted() const;
      bool setTemperatureControlType(const std::string& temperatureControlType);
      void resetTemperatureControlType();

      double runningMeanOutdoorDryBulbTemperatureWeightingFactor() const;
      bool isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const;
      bool setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(double runningMeanOutdoorDryBulbTemperatureWeightingFactor);
      void resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;
      bool setMotorEfficiency(double motorEfficiency);
      void resetMotorEfficiency();

      double fractionofMotorInefficienciestoFluidStream() const;
      bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
      bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
      void resetFractionofMotorInefficienciestoFluidStream();

     private:
      friend class openstudio::epmodel::ZoneHVACLowTempRadiantConstFlow;
      friend class CoilHeatingLowTempRadiantConstFlow_Impl;
      friend class CoilCoolingLowTempRadiantConstFlow_Impl;

      boost::optional<ZoneHVACLowTempRadiantConstFlowDesign> designObject() const;
      ZoneHVACLowTempRadiantConstFlowDesign ensureDesignObject();

      boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> surfaceGroup() const;
      ZoneHVACLowTemperatureRadiantSurfaceGroup ensureSurfaceGroup();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
