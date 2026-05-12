#ifndef EPMODEL_ShadingMaterial_I
#define EPMODEL_ShadingMaterial_I

#ifdef SWIGPYTHON
  %module openstudioepmodelshadingmaterial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/Material/EPModelMaterial.i>
%import <epmodel/FenestrationMaterial/EPModelFenestrationMaterial.i>

EPMODELOBJECT_WRAP(ShadingMaterial, <epmodel/ShadingMaterial/ShadingMaterial.hpp>, 0, 0)
EPMODELOBJECT_WRAP(Blind, <epmodel/ShadingMaterial/Blind.hpp>, 0, 1)
EPMODELOBJECT_WRAP(Shade, <epmodel/ShadingMaterial/Shade.hpp>, 0, 1)
EPMODELOBJECT_WRAP(Screen, <epmodel/ShadingMaterial/Screen.hpp>, 0, 1)

#endif
