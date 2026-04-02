/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl;
  }

  class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToSchedule : public Schedule
  {
   public:
    explicit ExternalInterfaceFunctionalMockupUnitExportToSchedule(const Model& model, const std::string& fMUVariableName);

    explicit ExternalInterfaceFunctionalMockupUnitExportToSchedule(const Model& model, const std::string& fMUVariableName, double initialValue);

    virtual ~ExternalInterfaceFunctionalMockupUnitExportToSchedule() override = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule(const ExternalInterfaceFunctionalMockupUnitExportToSchedule& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule(ExternalInterfaceFunctionalMockupUnitExportToSchedule&& other) = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule& operator=(const ExternalInterfaceFunctionalMockupUnitExportToSchedule&) = default;
    ExternalInterfaceFunctionalMockupUnitExportToSchedule& operator=(ExternalInterfaceFunctionalMockupUnitExportToSchedule&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ExternalInterfaceFunctionalMockupUnitExportToSchedule scalar accessor names/signatures.
    // - Field Mapping: fMUVariableName -> ExternalInterface:FunctionalMockupUnitExport:To:Schedule, FMU Variable Name.
    // - Field Mapping: initialValue -> ExternalInterface:FunctionalMockupUnitExport:To:Schedule, Initial Value.
    // - Field Mapping: scheduleTypeLimits is relationship-like (object-list target) and excluded from scalar scaffold.
    // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceFunctionalMockupUnitExportToSchedule.cpp writes FMU Variable Name
    //   and Initial Value directly from these APIs.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.

    /** @name FMU Variable Name */
    //@{
    std::string fMUVariableName() const;
    bool setFMUVariableName(const std::string& fMUVariableName);
    //@}

    /** @name Initial Value */
    //@{
    boost::optional<double> initialValue() const;
    bool setInitialValue(double initialValue);
    //@}

   protected:
    using ImplType = detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceFunctionalMockupUnitExportToSchedule(
      std::shared_ptr<detail::ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
