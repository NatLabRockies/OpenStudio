/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACHYBRIDUNITARYHVAC_HPP
#define EPMODEL_ZONEHVACHYBRIDUNITARYHVAC_HPP

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
    class ZoneHVACHybridUnitaryHVAC_Impl;
  }

  class EPMODEL_API ZoneHVACHybridUnitaryHVAC : public ModelObject
  {
   public:
    explicit ZoneHVACHybridUnitaryHVAC(const Model& model);

    virtual ~ZoneHVACHybridUnitaryHVAC() override = default;
    ZoneHVACHybridUnitaryHVAC(const ZoneHVACHybridUnitaryHVAC& other) = default;
    ZoneHVACHybridUnitaryHVAC(ZoneHVACHybridUnitaryHVAC&& other) = default;
    ZoneHVACHybridUnitaryHVAC& operator=(const ZoneHVACHybridUnitaryHVAC&) = default;
    ZoneHVACHybridUnitaryHVAC& operator=(ZoneHVACHybridUnitaryHVAC&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Field Mapping: Simple scalars (Method to Choose Controlled Inputs and Part Runtime Fraction, system maximum supply air flow rate, external static pressure, fan heat flags, scaling factor, minimum time between mode change, fuel/objective choices, and Mode 0 fractions) map directly to the ZoneHVAC:HybridUnitaryHVAC IDD fields.
    // - Field Mapping: Schedule/object-list references, node/air-path targets, DesignSpecification:OutdoorAir, lookup table names, and the extensible Mode descriptors are relationship-like and excluded from this scalar API.
    // - TODO(parity): Add extensible mode-specific scalars when the Ruby generator supports per-mode lookups.
    static std::vector<std::string> methodToChooseControlledInputsAndPartRuntimeFractionValues();
    std::string methodToChooseControlledInputsAndPartRuntimeFraction() const;
    bool setMethodToChooseControlledInputsAndPartRuntimeFraction(const std::string& methodToChooseControlledInputsAndPartRuntimeFraction);
    bool isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted() const;
    void resetMethodToChooseControlledInputsAndPartRuntimeFraction();

    boost::optional<double> systemMaximumSupplyAirFlowRate() const;
    bool setSystemMaximumSupplyAirFlowRate(double systemMaximumSupplyAirFlowRate);
    void resetSystemMaximumSupplyAirFlowRate();

    boost::optional<double> externalStaticPressureAtSystemMaximumSupplyAirFlowRate() const;
    bool setExternalStaticPressureAtSystemMaximumSupplyAirFlowRate(double externalStaticPressureAtSystemMaximumSupplyAirFlowRate);
    void resetExternalStaticPressureAtSystemMaximumSupplyAirFlowRate();

    static std::vector<std::string> fanHeatIncludedInLookupTablesValues();
    std::string fanHeatIncludedInLookupTables() const;
    bool setFanHeatIncludedInLookupTables(const std::string& fanHeatIncludedInLookupTables);
    bool isFanHeatIncludedInLookupTablesDefaulted() const;
    void resetFanHeatIncludedInLookupTables();

    static std::vector<std::string> fanHeatGainLocationValues();
    std::string fanHeatGainLocation() const;
    bool setFanHeatGainLocation(const std::string& fanHeatGainLocation);
    bool isFanHeatGainLocationDefaulted() const;
    void resetFanHeatGainLocation();

    double fanHeatInAirStreamFraction() const;
    bool setFanHeatInAirStreamFraction(double fanHeatInAirStreamFraction);
    bool isFanHeatInAirStreamFractionDefaulted() const;
    void resetFanHeatInAirStreamFraction();

    double scalingFactor() const;
    bool setScalingFactor(double scalingFactor);
    bool isScalingFactorDefaulted() const;
    void resetScalingFactor();

    double minimumTimeBetweenModeChange() const;
    bool setMinimumTimeBetweenModeChange(double minimumTimeBetweenModeChange);
    bool isMinimumTimeBetweenModeChangeDefaulted() const;
    void resetMinimumTimeBetweenModeChange();

    static std::vector<std::string> firstFuelTypeValues();
    std::string firstFuelType() const;
    bool setFirstFuelType(const std::string& firstFuelType);
    bool isFirstFuelTypeDefaulted() const;
    void resetFirstFuelType();

    static std::vector<std::string> secondFuelTypeValues();
    std::string secondFuelType() const;
    bool setSecondFuelType(const std::string& secondFuelType);
    bool isSecondFuelTypeDefaulted() const;
    void resetSecondFuelType();

    static std::vector<std::string> thirdFuelTypeValues();
    std::string thirdFuelType() const;
    bool setThirdFuelType(const std::string& thirdFuelType);
    bool isThirdFuelTypeDefaulted() const;
    void resetThirdFuelType();

    static std::vector<std::string> objectiveFunctionToMinimizeValues();
    std::string objectiveFunctionToMinimize() const;
    bool setObjectiveFunctionToMinimize(const std::string& objectiveFunctionToMinimize);
    bool isObjectiveFunctionToMinimizeDefaulted() const;
    void resetObjectiveFunctionToMinimize();

    double mode0OutdoorAirFraction() const;
    bool setMode0OutdoorAirFraction(double mode0OutdoorAirFraction);
    bool isMode0OutdoorAirFractionDefaulted() const;
    void resetMode0OutdoorAirFraction();

    double mode0SupplyAirMassFlowRateRatio() const;
    bool setMode0SupplyAirMassFlowRateRatio(double mode0SupplyAirMassFlowRateRatio);
    bool isMode0SupplyAirMassFlowRateRatioDefaulted() const;
    void resetMode0SupplyAirMassFlowRateRatio();

   protected:
    using ImplType = detail::ZoneHVACHybridUnitaryHVAC_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACHybridUnitaryHVAC(std::shared_ptr<detail::ZoneHVACHybridUnitaryHVAC_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
