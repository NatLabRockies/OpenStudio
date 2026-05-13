#ifndef EPMODEL_LayeredConstruction_I
#define EPMODEL_LayeredConstruction_I

#ifdef SWIGPYTHON
  %module openstudioepmodellayeredconstruction
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ConstructionBase/EPModelConstructionBase.i>

EPMODELOBJECT_WRAP(LayeredConstruction, <epmodel/LayeredConstruction/LayeredConstruction.hpp>, 0, 0)
EPMODELOBJECT_WRAP(Construction, <epmodel/LayeredConstruction/Construction.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ConstructionWithInternalSource, <epmodel/LayeredConstruction/ConstructionWithInternalSource.hpp>, 0, 1)

#endif
