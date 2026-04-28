/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEOUTDOOR_HPP
#define EPMODEL_PIPEOUTDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Construction;
  class Model;
  class Node;

  namespace detail {
    class PipeOutdoor_Impl;
  }

  class EPMODEL_API PipeOutdoor : public StraightComponent
  {
   public:
    explicit PipeOutdoor(const Model& model);

    virtual ~PipeOutdoor() override = default;
    PipeOutdoor(const PipeOutdoor& other) = default;
    PipeOutdoor(PipeOutdoor&& other) = default;
    PipeOutdoor& operator=(const PipeOutdoor&) = default;
    PipeOutdoor& operator=(PipeOutdoor&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Near Parity. The canonical PipeOutdoor scalar surface, object relationships, and plant-loop-only topology behavior are present.
    // - Canonical Counterpart: openstudio::model::PipeOutdoor.
    // - Implemented Parity: `construction`, `ambientTemperatureOutdoorAirNode`, `pipeInsideDiameter`, `pipeLength`, and plant-loop-only
    //   `addToNode(...)` preserve the canonical wrapper behavior that maps directly to `Pipe:Outdoor`.
    // - Documented Delta: PipeOutdoor still inherits the shared epmodel HVACComponent/StraightComponent base-surface gaps around the broader
    //   canonical component/fuel-type conveniences; this wrapper does not add a type-local workaround.
    // - Field/Storage Mapping: The wrapper maps directly to EnergyPlus `Pipe:Outdoor` construction, outdoor-air-node, and scalar fields.
    //   The canonical forward translator synthesizes an `OutdoorAir:NodeList` when no ambient outdoor-air node is assigned.
    // - Evidence: `src/model/PipeOutdoor.hpp`, `src/model/PipeOutdoor.cpp`, `src/model/test/PipeOutdoor_GTest.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslatePipeOutdoor.cpp`, and `src/energyplus/Test/PipeOutdoor_GTest.cpp`
    //   define and exercise the canonical behavior this wrapper preserves.
    // - Remaining Parity Work: Close the remaining shared HVACComponent base-surface gaps so PipeOutdoor can inherit the missing canonical
    //   component/fuel-type conveniences without adding type-local divergence.

    /** @name Topology */
    //@{
    bool addToNode(Node& node);
    //@}

    /** @name Construction */
    //@{
    boost::optional<Construction> construction() const;
    bool setConstruction(const Construction& construction);
    void resetConstruction();
    //@}

    /** @name Ambient Temperature Outdoor Air Node */
    //@{
    boost::optional<Node> ambientTemperatureOutdoorAirNode() const;
    bool setAmbientTemperatureOutdoorAirNode(const Node& node);
    void resetAmbientTemperatureOutdoorAirNode();
    //@}

    /** @name Pipe Inside Diameter */
    //@{
    double pipeInsideDiameter() const;
    bool setPipeInsideDiameter(double pipeInsideDiameter);
    //@}

    /** @name Pipe Length */
    //@{
    double pipeLength() const;
    bool setPipeLength(double pipeLength);
    //@}

   protected:
    using ImplType = detail::PipeOutdoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PipeOutdoor(std::shared_ptr<detail::PipeOutdoor_Impl> impl);
  };

  using OptionalPipeOutdoor = boost::optional<PipeOutdoor>;
  using PipeOutdoorVector = std::vector<PipeOutdoor>;

}  // namespace epmodel
}  // namespace openstudio

#endif
