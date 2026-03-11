/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACESCHEDULE_HPP
#define EPMODEL_EXTERNALINTERFACESCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExternalInterfaceSchedule_Impl;
}

class EPMODEL_API ExternalInterfaceSchedule : public ModelObject
{
 public:
  explicit ExternalInterfaceSchedule(const Model& model, double initialValue);
  explicit ExternalInterfaceSchedule(const Model& model);

  virtual ~ExternalInterfaceSchedule() override = default;
  ExternalInterfaceSchedule(const ExternalInterfaceSchedule& other) = default;
  ExternalInterfaceSchedule(ExternalInterfaceSchedule&& other) = default;
  ExternalInterfaceSchedule& operator=(const ExternalInterfaceSchedule&) = default;
  ExternalInterfaceSchedule& operator=(ExternalInterfaceSchedule&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExternalInterfaceSchedule constructor and scalar accessor names/signatures where mappable to E+.
  // - Field Mapping: initialValue -> ExternalInterface:Schedule, Initial Value.
  // - Field Mapping: scheduleTypeLimits is relationship-like (Schedule Type Limits Name object-list target) and excluded from scalar scaffold.
  // - API Drift: exportToBCVTB/isExportToBCVTBDefaulted/setExportToBCVTB/resetExportToBCVTB are OS-only fields
  //   (OS:ExternalInterface:Schedule ExportToBCVTB) and are not present on EnergyPlus ExternalInterface:Schedule.
  // - ForwardTranslator evidence: ForwardTranslateExternalInterfaceSchedule.cpp writes only ScheduleTypeLimitsName and InitialValue to E+.
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
  double initialValue() const;
  bool setInitialValue(double initialValue);

 protected:
  using ImplType = detail::ExternalInterfaceSchedule_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExternalInterfaceSchedule(std::shared_ptr<detail::ExternalInterfaceSchedule_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
