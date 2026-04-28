#ifndef EPMODEL_ModelPartitionMaterial_I
#define EPMODEL_ModelPartitionMaterial_I

#ifdef SWIGPYTHON
  %module openstudioepmodelmodelpartitionmaterial
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(InfraredTransparentMaterial, <epmodel/ModelPartitionMaterial/InfraredTransparentMaterial.hpp>)

#endif
