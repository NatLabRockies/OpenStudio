/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACCOMPONENT_HPP
#define EPMODEL_HVACCOMPONENT_HPP

#include "ParentObject/ParentObject.hpp"

#include "../utilities/idf/IdfObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <vector>

namespace openstudio {

class AppGFuelType;
class ComponentType;
class FuelType;

namespace epmodel {

  class AirLoopHVAC;
  class AirLoopHVACOutdoorAirSystem;
  class Loop;
  class Model;
  class Node;
  class PlantLoop;
  class Splitter;
  class StraightComponent;
  class ZoneHVACComponent;

  namespace detail {
    class HVACComponent_Impl;
  }

  /** \brief Base class for HVAC components that participate in loop topology.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. This interface covers concrete air-side and
   * plant-side HVAC objects.
   *
   * \par Important behavior
   * Loop and containment queries are resolved from EnergyPlus-backed branch and
   * node topology rather than OpenStudio Model connection objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::HVACComponent</code>.
   * <b>Not yet available:</b> <code>containingStraightComponent()</code>,
   * <code>autosize()</code>, and <code>applySizingValues()</code>.
   *
   * \par Known limitations
   * Containment is available only where the EnergyPlus topology provides an
   * unambiguous owner.
   */
  class EPMODEL_API HVACComponent : public ParentObject
  {
   public:
    virtual ~HVACComponent() override = default;
    HVACComponent(const HVACComponent& other) = default;
    HVACComponent(HVACComponent&& other) = default;
    HVACComponent& operator=(const HVACComponent&) = default;
    HVACComponent& operator=(HVACComponent&&) = default;

    boost::optional<Loop> loop() const;
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    boost::optional<PlantLoop> plantLoop() const;

    /** Returns the outdoor-air system containing this component, or boost::none
     *  if the component is not currently on an outdoor-air or relief stream. */
    boost::optional<AirLoopHVACOutdoorAirSystem> airLoopHVACOutdoorAirSystem() const;

    boost::optional<HVACComponent> containingHVACComponent() const;
    boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const;
    // TODO: Implement containingStraightComponent once containment tracking is ready.
    // boost::optional<StraightComponent> containingStraightComponent() const;

    bool addToNode(Node& node);
    bool addToSplitter(Splitter& splitter);
    void disconnect();
    bool isRemovable() const;
    std::vector<IdfObject> remove();
    // void autosize();
    // void applySizingValues();
    ComponentType componentType() const;
    std::vector<FuelType> coolingFuelTypes() const;
    std::vector<FuelType> heatingFuelTypes() const;
    std::vector<AppGFuelType> appGHeatingFuelTypes() const;

   protected:
    HVACComponent(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    using ImplType = detail::HVACComponent_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit HVACComponent(std::shared_ptr<detail::HVACComponent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
