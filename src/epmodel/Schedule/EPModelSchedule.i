#ifndef EPMODEL_Schedule_I
#define EPMODEL_Schedule_I

#ifdef SWIGPYTHON
  %module openstudioepmodelschedule
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

%include <epmodel/Schedule/Schedule.hpp>

EPMODELOBJECT_WRAP(ExternalInterfaceFunctionalMockupUnitImportToSchedule, <epmodel/Schedule/ExternalInterfaceFunctionalMockupUnitImportToSchedule.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ExternalInterfaceFunctionalMockupUnitExportToSchedule, <epmodel/Schedule/ExternalInterfaceFunctionalMockupUnitExportToSchedule.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ExternalInterfaceSchedule, <epmodel/Schedule/ExternalInterfaceSchedule.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ScheduleCompact, <epmodel/Schedule/ScheduleCompact.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ScheduleConstant, <epmodel/Schedule/ScheduleConstant.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ScheduleYear, <epmodel/Schedule/ScheduleYear.hpp>, 0, 1)

#endif
