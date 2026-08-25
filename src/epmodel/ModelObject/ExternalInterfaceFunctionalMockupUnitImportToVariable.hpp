/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl;
  }

  /** \brief Represents <code>ExternalInterface:FunctionalMockupUnitImport:To:Variable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitimporttovariable,ExternalInterface:FunctionalMockupUnitImport:To:Variable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitImportToVariable</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportToVariable(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportToVariable() override = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable(const ExternalInterfaceFunctionalMockupUnitImportToVariable& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable(ExternalInterfaceFunctionalMockupUnitImportToVariable&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable& operator=(const ExternalInterfaceFunctionalMockupUnitImportToVariable&) = default;
    ExternalInterfaceFunctionalMockupUnitImportToVariable& operator=(ExternalInterfaceFunctionalMockupUnitImportToVariable&&) = default;

    static IddObjectType iddObjectType();
    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportToVariable(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
