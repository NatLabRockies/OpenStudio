#ifndef EPMODEL_GasLayer_I
#define EPMODEL_GasLayer_I

#ifdef SWIGPYTHON
  %module openstudioepmodelgaslayer
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/Material/EPModelMaterial.i>

EPMODELOBJECT_WRAP(Gas, <epmodel/GasLayer/Gas.hpp>, 0, 1)
EPMODELOBJECT_WRAP(GasMixture, <epmodel/GasLayer/GasMixture.hpp>, 0, 1)

#endif
