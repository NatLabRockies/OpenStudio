/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTCOMPONENTUSERDEFINED_HPP
#define EPMODEL_PLANTCOMPONENTUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PlantComponentUserDefined_Impl;
  }

  class EPMODEL_API PlantComponentUserDefined : public StraightComponent
  {
   public:
    explicit PlantComponentUserDefined(const Model& model);

    virtual ~PlantComponentUserDefined() override = default;
    PlantComponentUserDefined(const PlantComponentUserDefined& other) = default;
    PlantComponentUserDefined(PlantComponentUserDefined&& other) = default;
    PlantComponentUserDefined& operator=(const PlantComponentUserDefined&) = default;
    PlantComponentUserDefined& operator=(PlantComponentUserDefined&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> plantConnection1LoadingModeValues();
    static std::vector<std::string> plantConnection1LoopFlowRequestModeValues();
    static std::vector<std::string> plantConnection2LoadingModeValues();
    static std::vector<std::string> plantConnection2LoopFlowRequestModeValues();
    static std::vector<std::string> plantConnection3LoadingModeValues();
    static std::vector<std::string> plantConnection3LoopFlowRequestModeValues();
    static std::vector<std::string> plantConnection4LoadingModeValues();
    static std::vector<std::string> plantConnection4LoopFlowRequestModeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The EnergyPlus-backed wrapper currently preserves the direct scalar surface and inherited straight-component
    //   plant-loop placement behavior, but it does not project the canonical OpenStudio-only EMS companion-object API.
    // - Canonical Counterpart: openstudio::model::PlantComponentUserDefined.
    // - Implemented Parity: The preserved API covers the canonical one-connection straight-component contract, constructor defaults for the required
    //   Plant Connection 1 fields, the canonical Plant Connection 1 loading/flow-request modes, and inherited straight-component plant-loop
    //   insertion/removal behavior. The wrapper also preserves the underlying EnergyPlus Number of Plant Loop Connections and Plant Connection 2-4
    //   loading/flow-request scalar fields as direct pass-through accessors, while restricting new writes to the canonical one-connection value.
    // - Documented Delta: The canonical wrapper's EMS program, actuator, and ambient-zone relationships live on the OpenStudio `OS:PlantComponent:UserDefined`
    //   schema, not directly on the EnergyPlus `PlantComponent:UserDefined` object, so that companion-object surface is intentionally not exposed here.
    //   The Number of Plant Loop Connections and additional Plant Connection 2-4 scalar accessors are EnergyPlus-facing pass-through fields, not
    //   canonical `openstudio::model` relationship projections.
    // - Field/Storage Mapping: These accessors map directly to the EnergyPlus `PlantComponent:UserDefined` scalar fields used by the forward translator.
    // - Evidence: `src/model/PlantComponentUserDefined.hpp`, `src/model/PlantComponentUserDefined.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslatePlantComponentUserDefined.cpp`.
    // - Remaining Parity Work: Add any future user-defined companion-object API only if epmodel adopts an explicit projection strategy over the EnergyPlus
    //   object, similar to other wrappers that preserve OpenStudio-only child relationships.
    int numberOfPlantLoopConnections() const;
    bool setNumberOfPlantLoopConnections(int numberOfPlantLoopConnections);

    std::string plantConnection1LoadingMode() const;
    bool setPlantConnection1LoadingMode(const std::string& plantConnection1LoadingMode);

    std::string plantConnection1LoopFlowRequestMode() const;
    bool setPlantConnection1LoopFlowRequestMode(const std::string& plantConnection1LoopFlowRequestMode);

    boost::optional<std::string> plantConnection2LoadingMode() const;
    bool setPlantConnection2LoadingMode(const std::string& plantConnection2LoadingMode);
    void resetPlantConnection2LoadingMode();

    boost::optional<std::string> plantConnection2LoopFlowRequestMode() const;
    bool setPlantConnection2LoopFlowRequestMode(const std::string& plantConnection2LoopFlowRequestMode);
    void resetPlantConnection2LoopFlowRequestMode();

    boost::optional<std::string> plantConnection3LoadingMode() const;
    bool setPlantConnection3LoadingMode(const std::string& plantConnection3LoadingMode);
    void resetPlantConnection3LoadingMode();

    boost::optional<std::string> plantConnection3LoopFlowRequestMode() const;
    bool setPlantConnection3LoopFlowRequestMode(const std::string& plantConnection3LoopFlowRequestMode);
    void resetPlantConnection3LoopFlowRequestMode();

    boost::optional<std::string> plantConnection4LoadingMode() const;
    bool setPlantConnection4LoadingMode(const std::string& plantConnection4LoadingMode);
    void resetPlantConnection4LoadingMode();

    boost::optional<std::string> plantConnection4LoopFlowRequestMode() const;
    bool setPlantConnection4LoopFlowRequestMode(const std::string& plantConnection4LoopFlowRequestMode);
    void resetPlantConnection4LoopFlowRequestMode();

   protected:
    using ImplType = detail::PlantComponentUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantComponentUserDefined(std::shared_ptr<detail::PlantComponentUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
