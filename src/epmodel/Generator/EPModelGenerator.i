#ifndef EPMODEL_Generator_I
#define EPMODEL_Generator_I

#ifdef SWIGPYTHON
  %module openstudioepmodelgenerator
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(GeneratorMicroTurbine, <epmodel/Generator/GeneratorMicroTurbine.hpp>, 0, 1)
EPMODELOBJECT_WRAP(GeneratorPhotovoltaic, <epmodel/Generator/GeneratorPhotovoltaic.hpp>, 0, 1)
EPMODELOBJECT_WRAP(GeneratorWindTurbine, <epmodel/Generator/GeneratorWindTurbine.hpp>, 0, 1)
EPMODELOBJECT_WRAP(GeneratorPVWatts, <epmodel/Generator/GeneratorPVWatts.hpp>, 0, 1)
EPMODELOBJECT_WRAP(GeneratorFuelCell, <epmodel/Generator/GeneratorFuelCell.hpp>, 0, 1)

#endif
