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

  namespace detail {

    class EPMODEL_API ZoneHVACLowTempRadiantVarFlow_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACLowTempRadiantVarFlow_Impl() override = default;

      boost::optional<double> hydronicTubingLength() const;
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
      boost::optional<std::string> m_fluidtoRadiantSurfaceHeatTransferModel;
      boost::optional<double> m_hydronicTubingInsideDiameter;
      boost::optional<double> m_hydronicTubingOutsideDiameter;
      boost::optional<double> m_hydronicTubingConductivity;
      boost::optional<std::string> m_temperatureControlType;
      boost::optional<std::string> m_setpointControlType;
      boost::optional<std::string> m_heatingDesignCapacityMethod;
      boost::optional<double> m_heatingDesignCapacityPerFloorArea;
      boost::optional<double> m_fractionofAutosizedHeatingDesignCapacity;
      boost::optional<double> m_heatingControlThrottlingRange;
      boost::optional<std::string> m_coolingDesignCapacityMethod;
      boost::optional<double> m_coolingDesignCapacityPerFloorArea;
      boost::optional<double> m_fractionofAutosizedCoolingDesignCapacity;
      boost::optional<double> m_coolingControlThrottlingRange;
      boost::optional<std::string> m_condensationControlType;
      boost::optional<double> m_condensationControlDewpointOffset;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
