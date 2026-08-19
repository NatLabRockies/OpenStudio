/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOACTUATOR_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl;
  }

  /** \brief Represents <code>ExternalInterface:FunctionalMockupUnitExport:To:Actuator</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitexporttoactuator,ExternalInterface:FunctionalMockupUnitExport:To:Actuator}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitExportToActuator</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToActuator : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitExportToActuator(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitExportToActuator() override = default;
    ExternalInterfaceFunctionalMockupUnitExportToActuator(const ExternalInterfaceFunctionalMockupUnitExportToActuator& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToActuator(ExternalInterfaceFunctionalMockupUnitExportToActuator&& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToActuator& operator=(const ExternalInterfaceFunctionalMockupUnitExportToActuator&) = default;
    ExternalInterfaceFunctionalMockupUnitExportToActuator& operator=(ExternalInterfaceFunctionalMockupUnitExportToActuator&&) = default;

    static IddObjectType iddObjectType();
    /** Actuated Component Type */
    //@{
    std::string actuatedComponentType() const;
    bool setActuatedComponentType(const std::string& actuatedComponentType);
    //@}

    /** Actuated Component Control Type */
    //@{
    std::string actuatedComponentControlType() const;
    bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);
    //@}

    /** FMU Variable Name */
    //@{
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);
    //@}

    /** Initial Value */
    //@{
    boost::optional<double> initialValue() const;
    bool setInitialValue(double initialValue);
    //@}

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitExportToActuator(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
