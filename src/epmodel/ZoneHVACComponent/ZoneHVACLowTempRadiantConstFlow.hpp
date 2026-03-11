/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_HPP
#define EPMODEL_ZONEHVACLOWTEMPRADIANTCONSTFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACLowTempRadiantConstFlow_Impl;
  }

  class EPMODEL_API ZoneHVACLowTempRadiantConstFlow : public ModelObject
  {
   public:
    explicit ZoneHVACLowTempRadiantConstFlow(const Model& model);

    virtual ~ZoneHVACLowTempRadiantConstFlow() override = default;
    ZoneHVACLowTempRadiantConstFlow(const ZoneHVACLowTempRadiantConstFlow& other) = default;
    ZoneHVACLowTempRadiantConstFlow(ZoneHVACLowTempRadiantConstFlow&& other) = default;
    ZoneHVACLowTempRadiantConstFlow& operator=(const ZoneHVACLowTempRadiantConstFlow&) = default;
    ZoneHVACLowTempRadiantConstFlow& operator=(ZoneHVACLowTempRadiantConstFlow&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> numberofCircuitsValues();
    static std::vector<std::string> fluidtoRadiantSurfaceHeatTransferModelValues();
    static std::vector<std::string> temperatureControlTypeValues();

    // Schema Alignment Notes:
    // - API: these scalar getters/setters map directly to the EnergyPlus ZoneHVAC:LowTemperatureRadiant:ConstantFlow
    //   fields enumerated by ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields as well as the auxiliary
    //   ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields; ForwardTranslateZoneHVACLowTempRadiantConstFlow.cpp
    //   routes coils/nodes/schedules/relationships separately while storing the hydronic and control-design scalars via
    //   the design object.
    // - Field Mapping: the same translator also writes the companion ZoneHVAC:LowTemperatureRadiant:SurfaceGroup
    //   object. It derives the group name via radiantSurfaceType()/name() and emits the extensible Surface Name plus
    //   Surface Area Fraction of Surface Group entries there while this API remains scalar-only.

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

   protected:
    using ImplType = detail::ZoneHVACLowTempRadiantConstFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACLowTempRadiantConstFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
