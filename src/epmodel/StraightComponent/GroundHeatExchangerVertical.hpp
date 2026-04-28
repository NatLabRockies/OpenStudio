/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;

  namespace detail {
    class GroundHeatExchangerVertical_Impl;
  }

  class EPMODEL_API GFunction
  {
   public:
    GFunction(double lnValue, double gValue);
    double lnValue() const;
    double gValue() const;

   private:
    double m_lnValue;
    double m_gValue;
  };

  class EPMODEL_API GroundHeatExchangerVertical : public StraightComponent
  {
   public:
    explicit GroundHeatExchangerVertical(const Model& model);
    explicit GroundHeatExchangerVertical(const Model& model, const ModelObject& undisturbedGroundTemperatureModel);

    virtual ~GroundHeatExchangerVertical() override = default;
    GroundHeatExchangerVertical(const GroundHeatExchangerVertical& other) = default;
    GroundHeatExchangerVertical(GroundHeatExchangerVertical&& other) = default;
    GroundHeatExchangerVertical& operator=(const GroundHeatExchangerVertical&) = default;
    GroundHeatExchangerVertical& operator=(GroundHeatExchangerVertical&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas.
    // - Canonical Counterpart: openstudio::model::GroundHeatExchangerVertical.
    // - Implemented Parity: The canonical constructors, undisturbed-ground-model relationship, g-function extensible helpers, plant-side non-demand
    //   `addToNode(...)` behavior, and the scalar accessors that map cleanly onto EnergyPlus `GroundHeatExchanger:System`,
    //   `GroundHeatExchanger:Vertical:Properties`, and `GroundHeatExchanger:ResponseFactors` storage are preserved.
    // - Documented Delta: Canonical `groundTemperature()` and `maximumLengthofSimulation()` helpers remain intentionally omitted because the EnergyPlus
    //   persisted schema has no direct fields for that OpenStudio-only state and epmodel does not yet add surrogate storage for them.
    // - Documented Delta: The undisturbed-ground-model relationship is still constrained by the EnergyPlus object-list on
    //   `GroundHeatExchanger:System`, so epmodel can only persist the supported undisturbed-ground model families instead of every
    //   arbitrary `ModelObject` the canonical OSM wrapper can temporarily point at before translation.
    // - Field/Storage Mapping: Design-flow, ground-property, and undisturbed-ground-model helpers write through the linked
    //   `GroundHeatExchanger:System`; borehole and pipe geometry write through the linked `GroundHeatExchanger:Vertical:Properties`; g-function
    //   extensibles and response-factor scalars live on the wrapped `GroundHeatExchanger:ResponseFactors` object itself.
    // - Evidence: `src/model/GroundHeatExchangerVertical.hpp`, `src/model/GroundHeatExchangerVertical.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateGroundHeatExchangerVertical.cpp`, and
    //   `src/epmodel/test/GroundHeatExchangerVertical_GTest.cpp`.
    // - Remaining Parity Work: Add the documented-delta OpenStudio-only scalar helpers only if epmodel later adopts a justified storage strategy for them.

    bool addGFunction(double gFunctionLN, double gFunctionGValue);
    bool addGFunction(GFunction gFunc);
    void removeGFunction(int groupIndex);
    void removeAllGFunctions();
    std::vector<GFunction> gFunctions();

    boost::optional<double> designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    boost::optional<double> groundThermalConductivity() const;
    bool setGroundThermalConductivity(double groundThermalConductivity);
    void resetGroundThermalConductivity();

    boost::optional<double> groundThermalHeatCapacity() const;
    bool setGroundThermalHeatCapacity(double groundThermalHeatCapacity);
    void resetGroundThermalHeatCapacity();

    double boreHoleTopDepth() const;
    bool setBoreHoleTopDepth(double boreHoleTopDepth);

    boost::optional<double> boreHoleLength() const;
    bool setBoreHoleLength(double boreHoleLength);
    void resetBoreHoleLength();

    boost::optional<double> boreHoleRadius() const;
    bool setBoreHoleRadius(double boreHoleRadius);
    void resetBoreHoleRadius();

    boost::optional<double> groutThermalConductivity() const;
    bool setGroutThermalConductivity(double groutThermalConductivity);
    void resetGroutThermalConductivity();

    boost::optional<double> pipeThermalConductivity() const;
    bool setPipeThermalConductivity(double pipeThermalConductivity);
    void resetPipeThermalConductivity();

    boost::optional<double> pipeOutDiameter() const;
    bool setPipeOutDiameter(double pipeOutDiameter);
    void resetPipeOutDiameter();

    boost::optional<double> uTubeDistance() const;
    bool setUTubeDistance(double uTubeDistance);
    void resetUTubeDistance();

    boost::optional<double> pipeThickness() const;
    bool setPipeThickness(double pipeThickness);
    void resetPipeThickness();

    boost::optional<int> numberofBoreHoles() const;
    bool setNumberofBoreHoles(int numberofBoreHoles);
    void resetNumberofBoreHoles();

    double gFunctionReferenceRatio() const;
    bool isGFunctionReferenceRatioDefaulted() const;
    bool setGFunctionReferenceRatio(double gFunctionReferenceRatio);
    void resetGFunctionReferenceRatio();

    ModelObject undisturbedGroundTemperatureModel() const;
    bool setUndisturbedGroundTemperatureModel(const ModelObject& undisturbedGroundTemperatureModel);

   protected:
    using ImplType = detail::GroundHeatExchangerVertical_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerVertical(std::shared_ptr<detail::GroundHeatExchangerVertical_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.GroundHeatExchangerVertical");
  };

  using OptionalGroundHeatExchangerVertical = boost::optional<GroundHeatExchangerVertical>;
  using GroundHeatExchangerVerticalVector = std::vector<GroundHeatExchangerVertical>;

}  // namespace epmodel
}  // namespace openstudio

#endif
