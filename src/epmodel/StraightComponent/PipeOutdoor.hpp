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

/** \brief An outdoor plant pipe.
 *
 * \par EnergyPlus object
 * \epobject{group-node-branch-management.html#pipeoutdoor,Pipe:Outdoor}
 *
 * \par Important behavior
 * The inherited straight-component inlet/outlet topology and pipe scalars map to Pipe:Outdoor.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::PipeOutdoor</code>.
 *
 * \par Known limitations
 * No additional type-specific limitation is known beyond shared straight-component topology.
 */
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
