#ifndef EPMODEL_PlanarSurfaceGroup_I
#define EPMODEL_PlanarSurfaceGroup_I

#ifdef SWIGPYTHON
  %module openstudioepmodelplanarsurfacegroup
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Space, <epmodel/PlanarSurfaceGroup/Space.hpp>, 0, 1)

#endif
