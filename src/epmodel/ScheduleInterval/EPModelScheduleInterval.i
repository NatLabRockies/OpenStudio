#ifndef EPMODEL_ScheduleInterval_I
#define EPMODEL_ScheduleInterval_I

#ifdef SWIGPYTHON
  %module openstudioepmodelscheduleinterval
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ScheduleFile, <epmodel/ScheduleInterval/ScheduleFile.hpp>)

#endif
