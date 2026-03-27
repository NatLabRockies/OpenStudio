/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_HPP
#define EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatExchangerHorizontalTrench_Impl;
  }

  class EPMODEL_API GroundHeatExchangerHorizontalTrench : public StraightComponent
  {
   public:
    explicit GroundHeatExchangerHorizontalTrench(const Model& model);

    virtual ~GroundHeatExchangerHorizontalTrench() override = default;
    GroundHeatExchangerHorizontalTrench(const GroundHeatExchangerHorizontalTrench& other) = default;
    GroundHeatExchangerHorizontalTrench(GroundHeatExchangerHorizontalTrench&& other) = default;
    GroundHeatExchangerHorizontalTrench& operator=(const GroundHeatExchangerHorizontalTrench&) = default;
    GroundHeatExchangerHorizontalTrench& operator=(GroundHeatExchangerHorizontalTrench&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical horizontal-trench ground-heat-exchanger scalar surface is present, while linked ground-model and node helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::GroundHeatExchangerHorizontalTrench.
    // - Implemented Parity: The preserved scalar API matches the design-flow and material-property accessors with matching scalar behavior.
    // - Documented Delta: Undisturbed-ground-model fields and inlet/outlet node helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `GroundHeatExchanger:HorizontalTrench` scalar fields used by the forward translator.
    // - Evidence: `src/model/GroundHeatExchangerHorizontalTrench.hpp`, `src/model/GroundHeatExchangerHorizontalTrench.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateGroundHeatExchangerHorizontalTrench.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    double designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    double trenchLengthinPipeAxialDirection() const;
    bool setTrenchLengthinPipeAxialDirection(double trenchLengthinPipeAxialDirection);

    int numberofTrenches() const;
    bool setNumberofTrenches(int numberofTrenches);

    double horizontalSpacingBetweenPipes() const;
    bool setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes);

    double pipeInnerDiameter() const;
    bool setPipeInnerDiameter(double pipeInnerDiameter);

    double pipeOuterDiameter() const;
    bool setPipeOuterDiameter(double pipeOuterDiameter);

    double burialDepth() const;
    bool setBurialDepth(double burialDepth);

    double soilThermalConductivity() const;
    bool setSoilThermalConductivity(double soilThermalConductivity);

    double soilDensity() const;
    bool setSoilDensity(double soilDensity);

    double soilSpecificHeat() const;
    bool setSoilSpecificHeat(double soilSpecificHeat);

    double pipeThermalConductivity() const;
    bool setPipeThermalConductivity(double pipeThermalConductivity);

    double pipeDensity() const;
    bool setPipeDensity(double pipeDensity);

    double pipeSpecificHeat() const;
    bool setPipeSpecificHeat(double pipeSpecificHeat);

    double soilMoistureContentPercent() const;
    bool setSoilMoistureContentPercent(double soilMoistureContentPercent);

    double soilMoistureContentPercentatSaturation() const;
    bool setSoilMoistureContentPercentatSaturation(double soilMoistureContentPercentatSaturation);

    double evapotranspirationGroundCoverParameter() const;
    bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);

   protected:
    using ImplType = detail::GroundHeatExchangerHorizontalTrench_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerHorizontalTrench(std::shared_ptr<detail::GroundHeatExchangerHorizontalTrench_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
