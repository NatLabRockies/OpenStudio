/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEINDOOR_HPP
#define EPMODEL_PIPEINDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Construction;
  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class PipeIndoor_Impl;
  }

/** \brief An indoor plant pipe.
 *
 * \par EnergyPlus object
 * \epobject{group-node-branch-management.html#pipeindoor,Pipe:Indoor}
 *
 * \par Important behavior
 * The inherited straight-component inlet/outlet topology and pipe scalars map to Pipe:Indoor.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::PipeIndoor</code>.
 *
 * \par Known limitations
 * No additional type-specific limitation is known beyond shared straight-component topology.
 */
  class EPMODEL_API PipeIndoor : public StraightComponent
  {
   public:
    explicit PipeIndoor(const Model& model);

    virtual ~PipeIndoor() override = default;
    PipeIndoor(const PipeIndoor& other) = default;
    PipeIndoor(PipeIndoor&& other) = default;
    PipeIndoor& operator=(const PipeIndoor&) = default;
    PipeIndoor& operator=(PipeIndoor&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> environmentTypeValues();


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

    /** @name Environment Type */
    //@{
    std::string environmentType() const;
    bool setEnvironmentType(const std::string& environmentType);
    //@}

    /** @name Ambient Temperature Zone */
    //@{
    boost::optional<ThermalZone> ambientTemperatureZone() const;
    bool setAmbientTemperatureZone(const ThermalZone& thermalZone);
    void resetAmbientTemperatureZone();
    //@}

    /** @name Ambient Temperature Schedule */
    //@{
    boost::optional<Schedule> ambientTemperatureSchedule() const;
    bool setAmbientTemperatureSchedule(Schedule& schedule);
    void resetAmbientTemperatureSchedule();
    //@}

    /** @name Ambient Air Velocity Schedule */
    //@{
    boost::optional<Schedule> ambientAirVelocitySchedule() const;
    bool setAmbientAirVelocitySchedule(Schedule& schedule);
    void resetAmbientAirVelocitySchedule();
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
    using ImplType = detail::PipeIndoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PipeIndoor(std::shared_ptr<detail::PipeIndoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
