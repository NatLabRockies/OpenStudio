#ifndef EPMODEL_SizingPeriod_I
#define EPMODEL_SizingPeriod_I

#ifdef SWIGPYTHON
  %module openstudioepmodelsizingperiod
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(DesignDay, <epmodel/SizingPeriod/DesignDay.hpp>, 0, 1)

#endif
