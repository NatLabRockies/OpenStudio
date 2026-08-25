/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDX_HPP
#define EPMODEL_COILCOOLINGDX_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class ThermalZone;
  class CoilCoolingDXCurveFitPerformance;

  namespace detail {
    class CoilCoolingDX_Impl;
  }

  /** \brief Represents a single-speed direct-expansion cooling coil.
   *
   * \par EnergyPlus object
   * \epobject{group-coil-cooling-dx.html#coilcoolingdx,Coil:Cooling:DX}.
   *
   * \par Important behavior
   * Condenser node fields and the persisted DX adapter are maintained when the coil is inserted into or moved within a supply branch.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilCoolingDX</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code> and explicit condenser inlet/outlet node methods. <b>Not yet available:</b> AirflowNetwork equivalent-duct, condensate/evaporative tank-link, and dedicated-outdoor-air insertion helpers.
   * \par Known limitations
   * Broader outdoor-air and AirflowNetwork topologies are not exposed.
   */
  class EPMODEL_API CoilCoolingDX : public StraightComponent
  {
   public:
    explicit CoilCoolingDX(const Model& model);
    explicit CoilCoolingDX(const Model& model, const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance);

    virtual ~CoilCoolingDX() override = default;
    CoilCoolingDX(const CoilCoolingDX& other) = default;
    CoilCoolingDX(CoilCoolingDX&& other) = default;
    CoilCoolingDX& operator=(const CoilCoolingDX&) = default;
    CoilCoolingDX& operator=(CoilCoolingDX&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<ThermalZone> condenserZone() const;
    bool setCondenserZone(const ThermalZone& thermalZone);
    void resetCondenserZone();

    CoilCoolingDXCurveFitPerformance performanceObject() const;
    bool setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance);

    std::string condenserInletNodeName() const;
    bool setCondenserInletNodeName(const std::string& condenserInletNodeName);

    std::string condenserOutletNodeName() const;
    bool setCondenserOutletNodeName(const std::string& condenserOutletNodeName);

   protected:
    using ImplType = detail::CoilCoolingDX_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDX(std::shared_ptr<detail::CoilCoolingDX_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
