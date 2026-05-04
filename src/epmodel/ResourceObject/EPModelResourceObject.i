#ifndef EPMODEL_ResourceObject_I
#define EPMODEL_ResourceObject_I

#ifdef SWIGPYTHON
  %module openstudioepmodelresourceobject
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

%include <epmodel/ResourceObject/ResourceObject.hpp>

EPMODELOBJECT_WRAP(DesignSpecificationOutdoorAir, <epmodel/ResourceObject/DesignSpecificationOutdoorAir.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ScheduleTypeLimits, <epmodel/ResourceObject/ScheduleTypeLimits.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ScheduleWeek, <epmodel/ResourceObject/ScheduleWeek.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SpaceType, <epmodel/ResourceObject/SpaceType.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ShadingControl, <epmodel/ResourceObject/ShadingControl.hpp>, 0, 1)
EPMODELOBJECT_WRAP(PythonPluginInstance, <epmodel/ResourceObject/PythonPluginInstance.hpp>, 0, 1)
EPMODELOBJECT_WRAP(PythonPluginSearchPaths, <epmodel/ResourceObject/PythonPluginSearchPaths.hpp>, 1, 1)
EPMODELOBJECT_WRAP(SurfacePropertyOtherSideCoefficients, <epmodel/ResourceObject/SurfacePropertyOtherSideCoefficients.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SurfacePropertyOtherSideConditionsModel, <epmodel/ResourceObject/SurfacePropertyOtherSideConditionsModel.hpp>, 0, 1)
EPMODELOBJECT_WRAP(TableIndependentVariable, <epmodel/ResourceObject/TableIndependentVariable.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WindowPropertyFrameAndDivider, <epmodel/ResourceObject/WindowPropertyFrameAndDivider.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilCoolingDXCurveFitPerformance, <epmodel/ResourceObject/CoilCoolingDXCurveFitPerformance.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilCoolingDXCurveFitOperatingMode, <epmodel/ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CoilCoolingDXCurveFitSpeed, <epmodel/ResourceObject/CoilCoolingDXCurveFitSpeed.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HeatExchangerDesiccantBalancedFlowPerformanceDataType1, <epmodel/ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1.hpp>, 0, 1)
EPMODELOBJECT_WRAP(MaterialPropertyGlazingSpectralData, <epmodel/ResourceObject/MaterialPropertyGlazingSpectralData.hpp>, 0, 1)

#endif
