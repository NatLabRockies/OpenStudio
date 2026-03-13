/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirConditionerVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlow : public ModelObject
  {
   public:
    explicit AirConditionerVariableRefrigerantFlow(const Model& model);

    virtual ~AirConditionerVariableRefrigerantFlow() override = default;
    AirConditionerVariableRefrigerantFlow(const AirConditionerVariableRefrigerantFlow& other) = default;
    AirConditionerVariableRefrigerantFlow(AirConditionerVariableRefrigerantFlow&& other) = default;
    AirConditionerVariableRefrigerantFlow& operator=(const AirConditionerVariableRefrigerantFlow&) = default;
    AirConditionerVariableRefrigerantFlow& operator=(AirConditionerVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingPerformanceCurveOutdoorTemperatureTypeValues();
    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> condenserTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names for this model-counterpart class.
    // - Field Mapping: grossRated* and ratedHeatingCapacitySizingRatio map directly to same-named E+ fields.
    // - Field Mapping: heatingPerformanceCurveOutdoorTemperatureType, heatPumpWasteHeatRecovery,
    //   numberofCompressors, defrostStrategy, and condenserType map to the corresponding E+ fields.
    // - Field Mapping: condenserType preserves API semantics via explicit field value/default-reset behavior.
    // - TODO(parity): Extend scalar coverage beyond this initial scaffold while keeping relationship fields excluded.
    boost::optional<double> grossRatedTotalCoolingCapacity() const;
    bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
    bool isGrossRatedTotalCoolingCapacityAutosized() const;
    void autosizeGrossRatedTotalCoolingCapacity();

    double grossRatedCoolingCOP() const;
    bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

    boost::optional<double> grossRatedHeatingCapacity() const;
    bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
    bool isGrossRatedHeatingCapacityAutosized() const;
    void autosizeGrossRatedHeatingCapacity();

    double ratedHeatingCapacitySizingRatio() const;
    bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);

    std::string heatingPerformanceCurveOutdoorTemperatureType() const;
    bool setHeatingPerformanceCurveOutdoorTemperatureType(const std::string& heatingPerformanceCurveOutdoorTemperatureType);

    bool heatPumpWasteHeatRecovery() const;
    bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);

    int numberofCompressors() const;
    bool setNumberofCompressors(int numberofCompressors);

    std::string defrostStrategy() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);
    bool isCondenserTypeDefaulted() const;
    void resetCondenserType();

   protected:
    using ImplType = detail::AirConditionerVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirConditionerVariableRefrigerantFlow(std::shared_ptr<detail::AirConditionerVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
