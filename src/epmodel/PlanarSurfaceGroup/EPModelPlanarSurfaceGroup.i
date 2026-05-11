#ifndef EPMODEL_PlanarSurfaceGroup_I
#define EPMODEL_PlanarSurfaceGroup_I

#ifdef SWIGPYTHON
  %module openstudioepmodelplanarsurfacegroup
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/PlanarSurface/EPModelPlanarSurface.i>

%{
  #include <utilities/geometry/BoundingBox.hpp>
  #include <utilities/geometry/Polyhedron.hpp>
  #include <utilities/geometry/Transformation.hpp>
%}


EPMODELOBJECT_WRAP(PlanarSurfaceGroup, <epmodel/PlanarSurfaceGroup/PlanarSurfaceGroup.hpp>, 0, 0)
EPMODELOBJECT_WRAP(Space, <epmodel/PlanarSurfaceGroup/Space.hpp>, 0, 1)

#endif
