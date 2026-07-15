/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOW_IMPL_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOW_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class ModelObject;
  class Schedule;
  class Surface;
  class ZoneHVACLowTempRadiantVarFlow;
  class ZoneHVACLowTempRadiantVarFlowDesign;
  class ZoneHVACLowTemperatureRadiantSurfaceGroup;
  class CoilHeatingLowTempRadiantVarFlow;
  class CoilCoolingLowTempRadiantVarFlow;

  namespace detail {

    class CoilHeatingLowTempRadiantVarFlow_Impl;
    class CoilCoolingLowTempRadiantVarFlow_Impl;

    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow& parent);
    std::string transientCoolingCoilName(const openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow& parent);

    class EPMODEL_API ZoneHVACLowTempRadiantVarFlow_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACLowTempRadiantVarFlow_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      boost::optional<std::string> radiantSurfaceType() const;
      bool setRadiantSurfaceType(const std::string& radiantSurfaceType);
      void resetRadiantSurfaceType();

      std::vector<Surface> surfaces() const;

      boost::optional<HVACComponent> heatingCoil() const;
      bool setHeatingCoil(HVACComponent& heatingCoil);
      void resetHeatingCoil();

      boost::optional<HVACComponent> coolingCoil() const;
      bool setCoolingCoil(HVACComponent& coolingCoil);
      void resetCoolingCoil();

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

      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();

      boost::optional<double> maximumHotWaterFlow() const;
      bool isMaximumHotWaterFlowAutosized() const;
      bool setMaximumHotWaterFlow(double maximumHotWaterFlow);
      void autosizeMaximumHotWaterFlow();

      boost::optional<double> coolingDesignCapacity() const;
      bool isCoolingDesignCapacityAutosized() const;
      bool setCoolingDesignCapacity(double coolingDesignCapacity);
      void autosizeCoolingDesignCapacity();

      boost::optional<double> maximumColdWaterFlow() const;
      bool isMaximumColdWaterFlowAutosized() const;
      bool setMaximumColdWaterFlow(double maximumColdWaterFlow);
      void autosizeMaximumColdWaterFlow();

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

      std::string setpointControlType() const;
      bool isSetpointControlTypeDefaulted() const;
      bool setSetpointControlType(const std::string& setpointControlType);
      void resetSetpointControlType();

      std::string heatingDesignCapacityMethod() const;
      bool isHeatingDesignCapacityMethodDefaulted() const;
      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
      void resetHeatingDesignCapacityMethod();

      boost::optional<double> heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
      void resetHeatingDesignCapacityPerFloorArea();

      double fractionofAutosizedHeatingDesignCapacity() const;
      bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
      void resetFractionofAutosizedHeatingDesignCapacity();

      double heatingControlThrottlingRange() const;
      bool isHeatingControlThrottlingRangeDefaulted() const;
      bool setHeatingControlThrottlingRange(double heatingControlThrottlingRange);
      void resetHeatingControlThrottlingRange();

      std::string coolingDesignCapacityMethod() const;
      bool isCoolingDesignCapacityMethodDefaulted() const;
      bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
      void resetCoolingDesignCapacityMethod();

      boost::optional<double> coolingDesignCapacityPerFloorArea() const;
      bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
      void resetCoolingDesignCapacityPerFloorArea();

      boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;
      bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);
      void resetFractionofAutosizedCoolingDesignCapacity();

      double coolingControlThrottlingRange() const;
      bool isCoolingControlThrottlingRangeDefaulted() const;
      bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
      void resetCoolingControlThrottlingRange();

      std::string condensationControlType() const;
      bool isCondensationControlTypeDefaulted() const;
      bool setCondensationControlType(const std::string& condensationControlType);
      void resetCondensationControlType();

      double condensationControlDewpointOffset() const;
      bool isCondensationControlDewpointOffsetDefaulted() const;
      bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
      void resetCondensationControlDewpointOffset();

      std::string numberofCircuits() const;
      bool isNumberofCircuitsDefaulted() const;
      bool setNumberofCircuits(const std::string& numberofCircuits);
      void resetNumberofCircuits();

      double circuitLength() const;
      bool isCircuitLengthDefaulted() const;
      bool setCircuitLength(double circuitLength);
      void resetCircuitLength();

     private:
      friend class openstudio::epmodel::ZoneHVACLowTempRadiantVarFlow;
      friend class CoilHeatingLowTempRadiantVarFlow_Impl;
      friend class CoilCoolingLowTempRadiantVarFlow_Impl;

      boost::optional<ZoneHVACLowTempRadiantVarFlowDesign> designObject() const;
      ZoneHVACLowTempRadiantVarFlowDesign ensureDesignObject();

      boost::optional<ZoneHVACLowTemperatureRadiantSurfaceGroup> surfaceGroup() const;
      ZoneHVACLowTemperatureRadiantSurfaceGroup ensureSurfaceGroup();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
