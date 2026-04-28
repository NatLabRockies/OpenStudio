#ifndef EPMODEL_GasLayer_I
#define EPMODEL_GasLayer_I

#ifdef SWIGPYTHON
  %module openstudioepmodelgaslayer
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(Gas, <epmodel/GasLayer/Gas.hpp>)
EPMODELOBJECT_WRAP(GasMixture, <epmodel/GasLayer/GasMixture.hpp>)

#endif
