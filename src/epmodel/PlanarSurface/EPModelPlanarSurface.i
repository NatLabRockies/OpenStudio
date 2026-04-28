#ifndef EPMODEL_PlanarSurface_I
#define EPMODEL_PlanarSurface_I

#ifdef SWIGPYTHON
  %module openstudioepmodelplanarsurface
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Surface, <epmodel/PlanarSurface/Surface.hpp>)
EPMODELOBJECT_WRAP(SubSurface, <epmodel/PlanarSurface/SubSurface.hpp>)
EPMODELOBJECT_WRAP(InteriorPartitionSurface, <epmodel/PlanarSurface/InteriorPartitionSurface.hpp>)

#endif
