/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl;
  }

  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToSchedule : public Schedule
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitImportToSchedule(const Model& model);

    virtual ~ExternalInterfaceFunctionalMockupUnitImportToSchedule() override = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule(const ExternalInterfaceFunctionalMockupUnitImportToSchedule& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule(ExternalInterfaceFunctionalMockupUnitImportToSchedule&& other) = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule& operator=(const ExternalInterfaceFunctionalMockupUnitImportToSchedule&) = default;
    ExternalInterfaceFunctionalMockupUnitImportToSchedule& operator=(ExternalInterfaceFunctionalMockupUnitImportToSchedule&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitImportToSchedule scalar accessor names/signatures.
    // - Field Mapping: fMUInstanceName -> ExternalInterface:FunctionalMockupUnitImport:To:Schedule, FMU Instance Name.
    // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitImport:To:Schedule, FMU Variable Name.
    // - Field Mapping: initialValue -> ExternalInterface:FunctionalMockupUnitImport:To:Schedule, Initial Value.
    // - Field Mapping: fMUFile / scheduleTypeLimits are relationship APIs and excluded from scalar scaffold.
    // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitImportToSchedule.cpp writes
    //   FMU File Name from modelObject.fMUFile().fMUFileName(), and writes scalar fields from these APIs.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.

    // FMU Instance Name accessors
    std::string fMUInstanceName() const;
    bool setFMUInstanceName(const std::string& fMUInstanceName);

    // FMU Variable Name accessors
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);

    // Initial Value accessors
    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitImportToSchedule(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
