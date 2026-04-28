#ifndef EPMODEL_OpaqueMaterial_I
#define EPMODEL_OpaqueMaterial_I

#ifdef SWIGPYTHON
  %module openstudioepmodelopaquematerial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(StandardOpaqueMaterial, <epmodel/OpaqueMaterial/StandardOpaqueMaterial.hpp>)
EPMODELOBJECT_WRAP(AirGap, <epmodel/OpaqueMaterial/AirGap.hpp>)
EPMODELOBJECT_WRAP(MasslessOpaqueMaterial, <epmodel/OpaqueMaterial/MasslessOpaqueMaterial.hpp>)
EPMODELOBJECT_WRAP(RoofVegetation, <epmodel/OpaqueMaterial/RoofVegetation.hpp>)

#endif
