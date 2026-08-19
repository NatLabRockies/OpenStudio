/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEACTUATOR_HPP
#define EPMODEL_EXTERNALINTERFACEACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceActuator_Impl;
  }

  /** \brief Represents <code>ExternalInterface:Actuator</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfaceactuator,ExternalInterface:Actuator}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceActuator</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceActuator : public ModelObject
  {
   public:
    explicit ExternalInterfaceActuator(const Model& model);

    virtual ~ExternalInterfaceActuator() override = default;
    ExternalInterfaceActuator(const ExternalInterfaceActuator& other) = default;
    ExternalInterfaceActuator(ExternalInterfaceActuator&& other) = default;
    ExternalInterfaceActuator& operator=(const ExternalInterfaceActuator&) = default;
    ExternalInterfaceActuator& operator=(ExternalInterfaceActuator&&) = default;

    static IddObjectType iddObjectType();
    std::string actuatedComponentControlType() const;
    bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

    // Actuated Component Type
    std::string actuatedComponentType() const;
    bool setActuatedComponentType(const std::string& actuatedComponentType);

    // Optional Initial Value
    boost::optional<double> optionalInitialValue() const;
    bool setOptionalInitialValue(double optionalInitialValue);
    void resetOptionalInitialValue();

   protected:
    using ImplType = detail::ExternalInterfaceActuator_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceActuator(std::shared_ptr<detail::ExternalInterfaceActuator_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
