#ifndef EPMODEL_OpaqueMaterial_I
#define EPMODEL_OpaqueMaterial_I

#ifdef SWIGPYTHON
  %module openstudioepmodelopaquematerial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(StandardOpaqueMaterial, <epmodel/OpaqueMaterial/StandardOpaqueMaterial.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirGap, <epmodel/OpaqueMaterial/AirGap.hpp>, 0, 1)
EPMODELOBJECT_WRAP(MasslessOpaqueMaterial, <epmodel/OpaqueMaterial/MasslessOpaqueMaterial.hpp>, 0, 1)
EPMODELOBJECT_WRAP(RoofVegetation, <epmodel/OpaqueMaterial/RoofVegetation.hpp>, 0, 1)

#endif
