/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_COILCOOLINGDXVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilCoolingDXVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API CoilCoolingDXVariableRefrigerantFlow : public HVACComponent
  {
   public:
    explicit CoilCoolingDXVariableRefrigerantFlow(const Model& model);

    virtual ~CoilCoolingDXVariableRefrigerantFlow() override = default;
    CoilCoolingDXVariableRefrigerantFlow(const CoilCoolingDXVariableRefrigerantFlow& other) = default;
    CoilCoolingDXVariableRefrigerantFlow(CoilCoolingDXVariableRefrigerantFlow&& other) = default;
    CoilCoolingDXVariableRefrigerantFlow& operator=(const CoilCoolingDXVariableRefrigerantFlow&) = default;
    CoilCoolingDXVariableRefrigerantFlow& operator=(CoilCoolingDXVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for model-counterpart compatibility.
    // - Field Mapping: ratedTotalCoolingCapacity and ratedSensibleHeatRatio map to E+ GrossRated* fields.
    // - Field Mapping: ratedAirFlowRate maps directly to E+ RatedAirFlowRate.
    // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDXVariableRefrigerantFlow.cpp writes these exact E+ fields.
    // - Field Mapping: Relationship fields (availability schedule, curves, node links) are intentionally excluded in this scalar scaffold phase.
    boost::optional<double> ratedTotalCoolingCapacity() const;
    bool setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity);
    bool isRatedTotalCoolingCapacityAutosized() const;
    void autosizeRatedTotalCoolingCapacity();

    boost::optional<double> ratedSensibleHeatRatio() const;
    bool setRatedSensibleHeatRatio(double ratedSensibleHeatRatio);
    bool isRatedSensibleHeatRatioAutosized() const;
    void autosizeRatedSensibleHeatRatio();

    boost::optional<double> ratedAirFlowRate() const;
    bool setRatedAirFlowRate(double ratedAirFlowRate);
    bool isRatedAirFlowRateAutosized() const;
    void autosizeRatedAirFlowRate();

   protected:
    using ImplType = detail::CoilCoolingDXVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
