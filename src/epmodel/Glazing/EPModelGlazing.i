#ifndef EPMODEL_Glazing_I
#define EPMODEL_Glazing_I

#ifdef SWIGPYTHON
  %module openstudioepmodelglazing
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(RefractionExtinctionGlazing, <epmodel/Glazing/RefractionExtinctionGlazing.hpp>)
EPMODELOBJECT_WRAP(ThermochromicGlazing, <epmodel/Glazing/ThermochromicGlazing.hpp>)
EPMODELOBJECT_WRAP(SimpleGlazing, <epmodel/Glazing/SimpleGlazing.hpp>)
EPMODELOBJECT_WRAP(StandardGlazing, <epmodel/Glazing/StandardGlazing.hpp>)

#endif
