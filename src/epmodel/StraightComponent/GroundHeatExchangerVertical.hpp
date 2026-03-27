/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatExchangerVertical_Impl;
  }

  class EPMODEL_API GroundHeatExchangerVertical : public StraightComponent
  {
   public:
    explicit GroundHeatExchangerVertical(const Model& model);

    virtual ~GroundHeatExchangerVertical() override = default;
    GroundHeatExchangerVertical(const GroundHeatExchangerVertical& other) = default;
    GroundHeatExchangerVertical(GroundHeatExchangerVertical&& other) = default;
    GroundHeatExchangerVertical& operator=(const GroundHeatExchangerVertical&) = default;
    GroundHeatExchangerVertical& operator=(GroundHeatExchangerVertical&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical vertical ground-heat-exchanger scalar surface is present, while linked-object and extensible helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::GroundHeatExchangerVertical.
    // - Implemented Parity: The preserved scalar API matches the borehole, pipe, thermal-property, and g-function reference accessors with matching scalar behavior.
    // - Documented Delta: Undisturbed-ground-model helpers and the GFunction extensible entries remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `GroundHeatExchanger:Vertical`/linked `GroundHeatExchanger:*` scalar fields used by the forward translator.
    // - Evidence: `src/model/GroundHeatExchangerVertical.hpp`, `src/model/GroundHeatExchangerVertical.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateGroundHeatExchangerVertical.cpp`.
    // - Remaining Parity Work: Add the omitted relationship and extensible helpers without changing the preserved scalar signatures.

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

   protected:
    using ImplType = detail::GroundHeatExchangerVertical_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerVertical(std::shared_ptr<detail::GroundHeatExchangerVertical_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
