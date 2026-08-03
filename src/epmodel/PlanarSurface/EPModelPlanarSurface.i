#ifndef EPMODEL_PlanarSurface_I
#define EPMODEL_PlanarSurface_I

#ifdef SWIGPYTHON
  %module openstudioepmodelplanarsurface
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ParentObject/EPModelParentObject.i>
%import <epmodel/PlanarSurfaceGroup/EPModelPlanarSurfaceGroup.i>

%{
  #include <sstream>
%}

%extend openstudio::epmodel::SurfaceIntersection {
  std::string __str__() {
    std::ostringstream os;
    os << *$self;
    return os.str();
  }
};

EPMODELOBJECT_WRAP(PlanarSurface, <epmodel/PlanarSurface/PlanarSurface.hpp>, 0, 0)
EPMODELOBJECT_WRAP(Surface, <epmodel/PlanarSurface/Surface.hpp>, 0, 1)  // also defines SurfaceIntersection
EPMODELOBJECT_TEMPLATES(SurfaceIntersection, 0)
EPMODELOBJECT_WRAP(SubSurface, <epmodel/PlanarSurface/SubSurface.hpp>, 0, 1)
EPMODELOBJECT_WRAP(InteriorPartitionSurface, <epmodel/PlanarSurface/InteriorPartitionSurface.hpp>, 0, 1)

#endif
