#ifndef EPMODEL_FenestrationMaterial_I
#define EPMODEL_FenestrationMaterial_I

#ifdef SWIGPYTHON
  %module openstudioepmodelfenestrationmaterial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/Material/EPModelMaterial.i>

EPMODELOBJECT_WRAP(FenestrationMaterial, <epmodel/FenestrationMaterial/FenestrationMaterial.hpp>, 0, 0)

#endif
