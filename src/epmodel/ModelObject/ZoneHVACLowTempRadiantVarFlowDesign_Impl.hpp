/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOWDESIGN_IMPL_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTVARFLOWDESIGN_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class Schedule;

  namespace detail {

    class EPMODEL_API ZoneHVACLowTempRadiantVarFlowDesign_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACLowTempRadiantVarFlowDesign_Impl() override = default;

      boost::optional<Schedule> heatingControlTemperatureSchedule() const;
      bool setHeatingControlTemperatureSchedule(Schedule& schedule);
      void resetHeatingControlTemperatureSchedule();

      boost::optional<Schedule> coolingControlTemperatureSchedule() const;
      bool setCoolingControlTemperatureSchedule(Schedule& schedule);
      void resetCoolingControlTemperatureSchedule();

      boost::optional<Schedule> changeoverDelayTimePeriodSchedule() const;
      bool setChangeoverDelayTimePeriodSchedule(Schedule& schedule);
      void resetChangeoverDelayTimePeriodSchedule();

      std::string fluidtoRadiantSurfaceHeatTransferModel() const;
      bool isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const;
      bool setFluidtoRadiantSurfaceHeatTransferModel(const std::string& value);
      void resetFluidtoRadiantSurfaceHeatTransferModel();

      double hydronicTubingInsideDiameter() const;
      bool isHydronicTubingInsideDiameterDefaulted() const;
      bool setHydronicTubingInsideDiameter(double value);
      void resetHydronicTubingInsideDiameter();

      double hydronicTubingOutsideDiameter() const;
      bool isHydronicTubingOutsideDiameterDefaulted() const;
      bool setHydronicTubingOutsideDiameter(double value);
      void resetHydronicTubingOutsideDiameter();

      double hydronicTubingConductivity() const;
      bool isHydronicTubingConductivityDefaulted() const;
      bool setHydronicTubingConductivity(double value);
      void resetHydronicTubingConductivity();

      std::string temperatureControlType() const;
      bool isTemperatureControlTypeDefaulted() const;
      bool setTemperatureControlType(const std::string& value);
      void resetTemperatureControlType();

      std::string setpointControlType() const;
      bool isSetpointControlTypeDefaulted() const;
      bool setSetpointControlType(const std::string& value);
      void resetSetpointControlType();

      std::string heatingDesignCapacityMethod() const;
      bool isHeatingDesignCapacityMethodDefaulted() const;
      bool setHeatingDesignCapacityMethod(const std::string& value);
      void resetHeatingDesignCapacityMethod();

      boost::optional<double> heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double value);
      void resetHeatingDesignCapacityPerFloorArea();

      double fractionofAutosizedHeatingDesignCapacity() const;
      bool isFractionofAutosizedHeatingDesignCapacityDefaulted() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double value);
      void resetFractionofAutosizedHeatingDesignCapacity();

      double heatingControlThrottlingRange() const;
      bool isHeatingControlThrottlingRangeDefaulted() const;
      bool setHeatingControlThrottlingRange(double value);
      void resetHeatingControlThrottlingRange();

      std::string coolingDesignCapacityMethod() const;
      bool isCoolingDesignCapacityMethodDefaulted() const;
      bool setCoolingDesignCapacityMethod(const std::string& value);
      void resetCoolingDesignCapacityMethod();

      boost::optional<double> coolingDesignCapacityPerFloorArea() const;
      bool setCoolingDesignCapacityPerFloorArea(double value);
      void resetCoolingDesignCapacityPerFloorArea();

      boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;
      bool setFractionofAutosizedCoolingDesignCapacity(double value);
      void resetFractionofAutosizedCoolingDesignCapacity();

      double coolingControlThrottlingRange() const;
      bool isCoolingControlThrottlingRangeDefaulted() const;
      bool setCoolingControlThrottlingRange(double value);
      void resetCoolingControlThrottlingRange();

      std::string condensationControlType() const;
      bool isCondensationControlTypeDefaulted() const;
      bool setCondensationControlType(const std::string& value);
      void resetCondensationControlType();

      double condensationControlDewpointOffset() const;
      bool isCondensationControlDewpointOffsetDefaulted() const;
      bool setCondensationControlDewpointOffset(double value);
      void resetCondensationControlDewpointOffset();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
