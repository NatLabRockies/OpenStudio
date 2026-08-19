/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOVARIABLE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl;
  }

  /** \brief Represents <code>ExternalInterface:FunctionalMockupUnitExport:To:Variable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfacefunctionalmockupunitexporttovariable,ExternalInterface:FunctionalMockupUnitExport:To:Variable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExternalInterfaceFunctionalMockupUnitExportToVariable</code>.
   * **Not yet available:** Model typed FMU/component relationships and OpenStudio-only export controls are not exposed unless represented by an EnergyPlus field here.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToVariable : public ModelObject
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitExportToVariable(const Model& model, const std::string& fMUVariableName, double initialValue);

    virtual ~ExternalInterfaceFunctionalMockupUnitExportToVariable() override = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable(const ExternalInterfaceFunctionalMockupUnitExportToVariable& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable(ExternalInterfaceFunctionalMockupUnitExportToVariable&& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable& operator=(const ExternalInterfaceFunctionalMockupUnitExportToVariable&) = default;
    ExternalInterfaceFunctionalMockupUnitExportToVariable& operator=(ExternalInterfaceFunctionalMockupUnitExportToVariable&&) = default;

    static IddObjectType iddObjectType();
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitExportToVariable(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
