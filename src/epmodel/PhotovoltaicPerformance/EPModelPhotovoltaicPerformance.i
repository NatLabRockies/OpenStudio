#ifndef EPMODEL_PhotovoltaicPerformance_I
#define EPMODEL_PhotovoltaicPerformance_I

#ifdef SWIGPYTHON
  %module openstudioepmodelphotovoltaicperformance
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(PhotovoltaicPerformanceSimple, <epmodel/PhotovoltaicPerformance/PhotovoltaicPerformanceSimple.hpp>, 0, 1)
EPMODELOBJECT_WRAP(PhotovoltaicPerformanceSandia, <epmodel/PhotovoltaicPerformance/PhotovoltaicPerformanceSandia.hpp>, 0, 1)

#endif
