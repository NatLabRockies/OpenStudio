#ifndef EPMODEL_ShadingMaterial_I
#define EPMODEL_ShadingMaterial_I

#ifdef SWIGPYTHON
  %module openstudioepmodelshadingmaterial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Blind, <epmodel/ShadingMaterial/Blind.hpp>)
EPMODELOBJECT_WRAP(Shade, <epmodel/ShadingMaterial/Shade.hpp>)
EPMODELOBJECT_WRAP(Screen, <epmodel/ShadingMaterial/Screen.hpp>)

#endif
