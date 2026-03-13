/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_HPP
#define EPMODEL_EVAPORATIVECOOLERDIRECTRESEARCHSPECIAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EvaporativeCoolerDirectResearchSpecial_Impl;
  }

  class EPMODEL_API EvaporativeCoolerDirectResearchSpecial : public StraightComponent
  {
   public:
    explicit EvaporativeCoolerDirectResearchSpecial(const Model& model);

    virtual ~EvaporativeCoolerDirectResearchSpecial() override = default;
    EvaporativeCoolerDirectResearchSpecial(const EvaporativeCoolerDirectResearchSpecial& other) = default;
    EvaporativeCoolerDirectResearchSpecial(EvaporativeCoolerDirectResearchSpecial&& other) = default;
    EvaporativeCoolerDirectResearchSpecial& operator=(const EvaporativeCoolerDirectResearchSpecial&) = default;
    EvaporativeCoolerDirectResearchSpecial& operator=(EvaporativeCoolerDirectResearchSpecial&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::EvaporativeCoolerDirectResearchSpecial scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: coolerDesignEffectiveness/coolerEffectiveness map to E+ Cooler Design Effectiveness.
    // - Field Mapping: recirculatingWaterPumpPowerConsumption maps to E+ Recirculating Water Pump Design Power
    //   (ForwardTranslateEvaporativeCoolerDirectResearchSpecial.cpp).
    // - Field Mapping: primaryAirDesignFlowRate, driftLossFraction, blowdownConcentrationRatio, waterPumpPowerSizingFactor,
    //   and evaporativeOperation*Temperature accessors map directly to same E+ object fields.
    // - Field Mapping: Availability Schedule Name, Air Inlet/Outlet Node Name, Sensor Node Name, and curve-name fields are
    //   relationship-like and excluded from this scalar-only scaffold.
    // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
    double coolerDesignEffectiveness() const;
    double coolerEffectiveness() const;
    bool setCoolerDesignEffectiveness(double value);
    bool setCoolerEffectiveness(double value);

    boost::optional<double> recirculatingWaterPumpPowerConsumption() const;
    bool setRecirculatingWaterPumpPowerConsumption(double value);
    void autosizeRecirculatingWaterPumpPowerConsumption();
    bool isRecirculatingWaterPumpPowerConsumptionAutosized() const;
    boost::optional<double> autosizedRecirculatingWaterPumpPowerConsumption() const;

    boost::optional<double> primaryAirDesignFlowRate() const;
    bool setPrimaryAirDesignFlowRate(double value);
    void autosizePrimaryAirDesignFlowRate();
    bool isPrimaryAirDesignFlowRateAutosized() const;
    boost::optional<double> autosizedPrimaryAirDesignFlowRate() const;

    double driftLossFraction() const;
    bool setDriftLossFraction(double value);

    double blowdownConcentrationRatio() const;
    bool setBlowdownConcentrationRatio(double value);

    double waterPumpPowerSizingFactor() const;
    bool setWaterPumpPowerSizingFactor(double waterPumpPowerSizingFactor);

    double evaporativeOperationMinimumDrybulbTemperature() const;
    bool setEvaporativeOperationMinimumDrybulbTemperature(double evaporativeOperationMinimumDrybulbTemperature);

    double evaporativeOperationMaximumLimitWetbulbTemperature() const;
    bool setEvaporativeOperationMaximumLimitWetbulbTemperature(double evaporativeOperationMaximumLimitWetbulbTemperature);

    double evaporativeOperationMaximumLimitDrybulbTemperature() const;
    bool setEvaporativeOperationMaximumLimitDrybulbTemperature(double evaporativeOperationMaximumLimitDrybulbTemperature);

   protected:
    using ImplType = detail::EvaporativeCoolerDirectResearchSpecial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EvaporativeCoolerDirectResearchSpecial(std::shared_ptr<detail::EvaporativeCoolerDirectResearchSpecial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
