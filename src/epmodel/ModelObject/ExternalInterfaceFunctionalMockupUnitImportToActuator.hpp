/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOACTUATOR_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOACTUATOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl;
  }

  /** \brief Represents <code>ExternalInterface:FunctionalMockupUnitImport:To:Actuator</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitimporttoactuator,ExternalInterface:FunctionalMockupUnitImport:To:Actuator}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitImportToActuator</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToActuator : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportToActuator(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportToActuator() override = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator(const ExternalInterfaceFunctionalMockupUnitImportToActuator& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator(ExternalInterfaceFunctionalMockupUnitImportToActuator&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator& operator=(const ExternalInterfaceFunctionalMockupUnitImportToActuator&) = default;
    ExternalInterfaceFunctionalMockupUnitImportToActuator& operator=(ExternalInterfaceFunctionalMockupUnitImportToActuator&&) = default;

    static IddObjectType iddObjectType();
    std::string actuatedComponentType() const;
    bool setActuatedComponentType(const std::string& actuatedComponentType);

    std::string actuatedComponentControlType() const;
    bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportToActuator(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToActuator_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
