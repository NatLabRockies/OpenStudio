#ifndef EPMODEL_Material_I
#define EPMODEL_Material_I

#ifdef SWIGPYTHON
  %module openstudioepmodelmaterial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ResourceObject/EPModelResourceObject.i>

EPMODELOBJECT_WRAP(Material, <epmodel/Material/Material.hpp>, 0, 0)

#endif
