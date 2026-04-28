#ifndef EPMODEL_LayeredConstruction_I
#define EPMODEL_LayeredConstruction_I

#ifdef SWIGPYTHON
  %module openstudioepmodellayeredconstruction
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Construction, <epmodel/LayeredConstruction/Construction.hpp>)
EPMODELOBJECT_WRAP(ConstructionWithInternalSource, <epmodel/LayeredConstruction/ConstructionWithInternalSource.hpp>)

#endif
