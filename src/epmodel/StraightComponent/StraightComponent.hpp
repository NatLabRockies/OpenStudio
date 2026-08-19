/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STRAIGHTCOMPONENT_HPP
#define EPMODEL_STRAIGHTCOMPONENT_HPP

#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "Loop/AirLoopHVAC.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class StraightComponent_Impl;
  }

/** \brief The shared base for one-inlet/one-outlet HVAC components.
 *
 * \par EnergyPlus object
 * No single EnergyPlus object. This abstract base represents HVAC object types
 * with one inlet node field and one outlet node field.
 *
 * \par Important behavior
 * Inlet and outlet ports, model objects, and loop removal are resolved from EnergyPlus-backed topology rather than OpenStudio connection objects.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::StraightComponent</code>.
 *
 * - <b>Not yet available:</b> The base-class
 *   <code>airLoopHVAC()</code> convenience method. Concrete EPModel components
 *   can still be reached through their loop topology.
 *
 * \par Known limitations
 * No additional EPModel-specific limitations are known at this base level.
 */
  class EPMODEL_API StraightComponent : public HVACComponent
  {
   public:
    virtual ~StraightComponent() override = default;
    StraightComponent() = delete;
    StraightComponent(const StraightComponent& other) = default;
    StraightComponent(StraightComponent&& other) = default;
    StraightComponent& operator=(const StraightComponent&) = default;
    StraightComponent& operator=(StraightComponent&&) = default;

    bool removeFromLoop();

    unsigned inletPort() const;
    boost::optional<ModelObject> inletModelObject() const;

    unsigned outletPort() const;
    boost::optional<ModelObject> outletModelObject() const;

   protected:
    friend class Model;
    friend class openstudio::IdfObject;

    using ImplType = detail::StraightComponent_Impl;

    StraightComponent(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    explicit StraightComponent(std::shared_ptr<detail::StraightComponent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
