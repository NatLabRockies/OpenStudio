/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_IMPL_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACLowTempRadiantConstFlow_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACLowTempRadiantConstFlow_Impl() override = default;

      boost::optional<double> hydronicTubingLength() const;
      bool isHydronicTubingLengthAutosized() const;
      bool setHydronicTubingLength(double hydronicTubingLength);
      void autosizeHydronicTubingLength();

      boost::optional<double> ratedFlowRate() const;
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
      boost::optional<std::string> m_fluidtoRadiantSurfaceHeatTransferModel;
      boost::optional<double> m_hydronicTubingInsideDiameter;
      boost::optional<double> m_hydronicTubingOutsideDiameter;
      boost::optional<double> m_hydronicTubingConductivity;
      boost::optional<std::string> m_temperatureControlType;
      boost::optional<double> m_runningMeanOutdoorDryBulbTemperatureWeightingFactor;
      boost::optional<double> m_motorEfficiency;
      boost::optional<double> m_fractionofMotorInefficienciestoFluidStream;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
