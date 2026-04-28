#ifndef EPMODEL_Schedule_I
#define EPMODEL_Schedule_I

#ifdef SWIGPYTHON
  %module openstudioepmodelschedule
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

%include <epmodel/Schedule/Schedule.hpp>

EPMODELOBJECT_WRAP(ExternalInterfaceFunctionalMockupUnitImportToSchedule, <epmodel/Schedule/ExternalInterfaceFunctionalMockupUnitImportToSchedule.hpp>)
EPMODELOBJECT_WRAP(ExternalInterfaceFunctionalMockupUnitExportToSchedule, <epmodel/Schedule/ExternalInterfaceFunctionalMockupUnitExportToSchedule.hpp>)
EPMODELOBJECT_WRAP(ExternalInterfaceSchedule, <epmodel/Schedule/ExternalInterfaceSchedule.hpp>)
EPMODELOBJECT_WRAP(ScheduleCompact, <epmodel/Schedule/ScheduleCompact.hpp>)
EPMODELOBJECT_WRAP(ScheduleConstant, <epmodel/Schedule/ScheduleConstant.hpp>)
EPMODELOBJECT_WRAP(ScheduleYear, <epmodel/Schedule/ScheduleYear.hpp>)

#endif
