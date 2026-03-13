/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTLOOP_HPP
#define EPMODEL_PLANTLOOP_HPP

#include "EPModelAPI.hpp"
#include "Loop/Loop.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantLoop_Impl;
  }

  class EPMODEL_API PlantLoop : public Loop
  {
   public:
    explicit PlantLoop(const Model& model);

    virtual ~PlantLoop() override = default;
    PlantLoop(const PlantLoop& other) = default;
    PlantLoop(PlantLoop&& other) = default;
    PlantLoop& operator=(const PlantLoop&) = default;
    PlantLoop& operator=(PlantLoop&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model class naming for this model-counterpart type (PlantLoop).
    // - Field Mapping: ForwardTranslator evidence (ForwardTranslatePlantLoop.cpp) confirms these scalar fields map directly
    //   to the corresponding PlantLoop IDD fields, so we expose the same API names and signatures.
    // - Field Mapping: Fluid Type and Load Distribution Scheme represent operating-mode choices and are exposed with the
    //   same string accessors as the OS model, including Legacy Sequential/Uniform alias translations in the setter.
    // - Field Mapping: Maximum/Minimum Loop Temperature, Flow Rate, and Plant Loop Volume mirror their numeric IDD
    //   fields and carry over the autosize/autocalculate semantics through helper getters/setters.
    // - Field Mapping: Common Pipe Simulation is the scalar CommonPipeSimulation choice (default None) and may be
    //   reset via resetCommonPipeSimulation().
    // - Field Mapping: Connector:Mixer Outlet Branch Name / extensible Inlet Branch Name remain expressed through topology APIs
    //   such as supplyComponents/demandComponents rather than new scalar accessors.
    // - Field Mapping: Name remains available through the base ModelObject scalar API.
    // - TODO(parity): Broaden PlantLoop scalar coverage once additional translator evidence and IDD mappings stabilize.

    std::string loadDistributionScheme() const;
    bool setLoadDistributionScheme(const std::string& scheme);

    std::string fluidType() const;
    bool setFluidType(const std::string& value);

    int glycolConcentration() const;
    bool setGlycolConcentration(int glycolConcentration);

    double maximumLoopTemperature() const;
    bool setMaximumLoopTemperature(double value);

    double minimumLoopTemperature() const;
    bool setMinimumLoopTemperature(double value);

    boost::optional<double> maximumLoopFlowRate() const;
    bool setMaximumLoopFlowRate(double value);
    bool isMaximumLoopFlowRateAutosized() const;
    void autosizeMaximumLoopFlowRate();

    boost::optional<double> minimumLoopFlowRate() const;
    bool setMinimumLoopFlowRate(double value);
    bool isMinimumLoopFlowRateAutosized() const;
    void autosizeMinimumLoopFlowRate();

    boost::optional<double> plantLoopVolume() const;
    bool setPlantLoopVolume(double value);
    bool isPlantLoopVolumeAutocalculated() const;
    void autocalculatePlantLoopVolume();

    std::string commonPipeSimulation() const;
    bool setCommonPipeSimulation(const std::string& value);
    bool isCommonPipeSimulationDefaulted() const;
    void resetCommonPipeSimulation();

   protected:
    using ImplType = detail::PlantLoop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
