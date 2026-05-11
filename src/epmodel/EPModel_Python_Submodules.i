#ifndef EPMODEL_PYTHON_SUBMODULES_I
#define EPMODEL_PYTHON_SUBMODULES_I

#ifdef SWIGPYTHON
  %pythoncode %{
    from openstudioepmodelmodelobject import *
    from openstudioepmodelresourceobject import *
    from openstudioepmodelplantequipmentoperationscheme import *
    from openstudioepmodelparentobject import *
    from openstudioepmodelgaslayer import *
    from openstudioepmodelshadingmaterial import *
    from openstudioepmodelairflownetworklinkage import *
    from openstudioepmodelairflownetworknode import *
    from openstudioepmodelavailabilitymanager import *
    from openstudioepmodelexteriorloadinstance import *
    from openstudioepmodelschedule import *
    from openstudioepmodelschedulebase import *
    from openstudioepmodelspaceloadinstance import *
    from openstudioepmodelspaceload import *
    from openstudioepmodelmaterial import *
    from openstudioepmodelopaquematerial import *
    from openstudioepmodelmodelpartitionmaterial import *
    from openstudioepmodelthermostat import *
    from openstudioepmodelsizingperiod import *
    from openstudioepmodellayeredconstruction import *
    from openstudioepmodelconstructionbase import *
    from openstudioepmodelinverter import *
    from openstudioepmodelelectricalstorage import *
    from openstudioepmodelplanarsurface import *
    from openstudioepmodelgenerator import *
    from openstudioepmodelphotovoltaicperformance import *
    from openstudioepmodelglazing import *
    from openstudioepmodelplanarsurfacegroup import *
    from openstudioepmodelcurve import *
    from openstudioepmodelhvaccomponent import *
    from openstudioepmodelscheduleinterval import *
    from openstudioepmodelloop import *
    from openstudioepmodelstraightcomponent import *
    from openstudioepmodelwatertoaircomponent import *
    from openstudioepmodelzonehvaccomponent import *
    from openstudioepmodelwatertowatercomponent import *
    from openstudioepmodelairtoaircomponent import *
    from openstudioepmodelmixer import *
    from openstudioepmodelsplitter import *
    from openstudioepmodelsetpointmanager import *
  %}
#endif

#endif
