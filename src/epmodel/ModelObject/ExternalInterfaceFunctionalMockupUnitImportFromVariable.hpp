/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTFROMVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTFROMVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl;
  }

  /** \brief Represents <code>ExternalInterface:FunctionalMockupUnitImport:From:Variable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitimportfromvariable,ExternalInterface:FunctionalMockupUnitImport:From:Variable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitImportFromVariable</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportFromVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportFromVariable(const Model& model, const std::string& outputVariableIndexKeyName,
                                                                     const std::string& outputVariableName, const std::string& fMUInstanceName,
                                                                     const std::string& fMUVariableName);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportFromVariable() override = default;
    ExternalInterfaceFunctionalMockupUnitImportFromVariable(const ExternalInterfaceFunctionalMockupUnitImportFromVariable& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportFromVariable(ExternalInterfaceFunctionalMockupUnitImportFromVariable&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportFromVariable& operator=(const ExternalInterfaceFunctionalMockupUnitImportFromVariable&) = default;
    ExternalInterfaceFunctionalMockupUnitImportFromVariable& operator=(ExternalInterfaceFunctionalMockupUnitImportFromVariable&&) = default;

    static IddObjectType iddObjectType();
    std::string outputVariableIndexKeyName() const;
    bool setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName);

    std::string outputVariableName() const;
    bool setOutputVariableName(const std::string& outputVariableName);

    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportFromVariable(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
