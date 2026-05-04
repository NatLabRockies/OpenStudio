#ifndef EPMODEL_ScheduleBase_I
#define EPMODEL_ScheduleBase_I

#ifdef SWIGPYTHON
  %module openstudioepmodelschedulebase
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ScheduleDay, <epmodel/ScheduleBase/ScheduleDay.hpp>, 0, 1)

#endif
