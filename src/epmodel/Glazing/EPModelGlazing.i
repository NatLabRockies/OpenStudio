#ifndef EPMODEL_Glazing_I
#define EPMODEL_Glazing_I

#ifdef SWIGPYTHON
  %module openstudioepmodelglazing
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(RefractionExtinctionGlazing, <epmodel/Glazing/RefractionExtinctionGlazing.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ThermochromicGlazing, <epmodel/Glazing/ThermochromicGlazing.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SimpleGlazing, <epmodel/Glazing/SimpleGlazing.hpp>, 0, 1)
EPMODELOBJECT_WRAP(StandardGlazing, <epmodel/Glazing/StandardGlazing.hpp>, 0, 1)

#endif
