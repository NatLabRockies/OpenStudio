/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP
#define EPMODEL_CONTROLLERMECHANICALVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ControllerOutdoorAir;

  namespace detail {
    class ControllerMechanicalVentilation_Impl;
  }

  /** \brief Represents <code>Controller:MechanicalVentilation</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-controllers.html#controllermechanicalventilation,Controller:MechanicalVentilation}
   *
   * \par Important behavior
   * Load repair restores a missing or incompatible availability schedule and can clone a valid shared controller so each outdoor-air controller has one managed relationship.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ControllerMechanicalVentilation</code>.
   * <b>Changed:</b> <code>controllerOutdoorAir()</code> returns an optional relationship and is limited to the supported managed outdoor-air chain.
   * <b>Not yet available:</b> <code>hasZonesWithDesignSpecificationOutdoorAir()</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ControllerMechanicalVentilation : public ModelObject
  {
   public:
    explicit ControllerMechanicalVentilation(const Model& model);

    virtual ~ControllerMechanicalVentilation() override = default;
    ControllerMechanicalVentilation(const ControllerMechanicalVentilation& other) = default;
    ControllerMechanicalVentilation(ControllerMechanicalVentilation&& other) = default;
    ControllerMechanicalVentilation& operator=(const ControllerMechanicalVentilation&) = default;
    ControllerMechanicalVentilation& operator=(ControllerMechanicalVentilation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> systemOutdoorAirMethodValues();
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    bool demandControlledVentilation() const;
    bool isDemandControlledVentilationDefaulted() const;
    bool setDemandControlledVentilation(bool value);
    void setDemandControlledVentilationNoFail(bool value);
    void resetDemandControlledVentilation();

    std::string systemOutdoorAirMethod() const;
    bool isSystemOutdoorAirMethodDefaulted() const;
    bool setSystemOutdoorAirMethod(const std::string& value);
    void resetSystemOutdoorAirMethod();

    boost::optional<ControllerOutdoorAir> controllerOutdoorAir() const;

   protected:
    using ImplType = detail::ControllerMechanicalVentilation_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ControllerMechanicalVentilation(std::shared_ptr<detail::ControllerMechanicalVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
