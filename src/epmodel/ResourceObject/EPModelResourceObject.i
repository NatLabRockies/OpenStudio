#ifndef EPMODEL_ResourceObject_I
#define EPMODEL_ResourceObject_I

#ifdef SWIGPYTHON
  %module openstudioepmodelresourceobject
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

%include <epmodel/ResourceObject/ResourceObject.hpp>

EPMODELOBJECT_WRAP(DesignSpecificationOutdoorAir, <epmodel/ResourceObject/DesignSpecificationOutdoorAir.hpp>)
EPMODELOBJECT_WRAP(ScheduleTypeLimits, <epmodel/ResourceObject/ScheduleTypeLimits.hpp>)
EPMODELOBJECT_WRAP(ScheduleWeek, <epmodel/ResourceObject/ScheduleWeek.hpp>)
EPMODELOBJECT_WRAP(SpaceType, <epmodel/ResourceObject/SpaceType.hpp>)
EPMODELOBJECT_WRAP(ShadingControl, <epmodel/ResourceObject/ShadingControl.hpp>)
EPMODELOBJECT_WRAP(PythonPluginInstance, <epmodel/ResourceObject/PythonPluginInstance.hpp>)
EPMODELOBJECT_WRAP(PythonPluginSearchPaths, <epmodel/ResourceObject/PythonPluginSearchPaths.hpp>)
EPMODELOBJECT_WRAP(SurfacePropertyOtherSideCoefficients, <epmodel/ResourceObject/SurfacePropertyOtherSideCoefficients.hpp>)
EPMODELOBJECT_WRAP(SurfacePropertyOtherSideConditionsModel, <epmodel/ResourceObject/SurfacePropertyOtherSideConditionsModel.hpp>)
EPMODELOBJECT_WRAP(TableIndependentVariable, <epmodel/ResourceObject/TableIndependentVariable.hpp>)
EPMODELOBJECT_WRAP(WindowPropertyFrameAndDivider, <epmodel/ResourceObject/WindowPropertyFrameAndDivider.hpp>)
EPMODELOBJECT_WRAP(CoilCoolingDXCurveFitPerformance, <epmodel/ResourceObject/CoilCoolingDXCurveFitPerformance.hpp>)
EPMODELOBJECT_WRAP(CoilCoolingDXCurveFitOperatingMode, <epmodel/ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp>)
EPMODELOBJECT_WRAP(CoilCoolingDXCurveFitSpeed, <epmodel/ResourceObject/CoilCoolingDXCurveFitSpeed.hpp>)
EPMODELOBJECT_WRAP(HeatExchangerDesiccantBalancedFlowPerformanceDataType1, <epmodel/ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1.hpp>)
EPMODELOBJECT_WRAP(MaterialPropertyGlazingSpectralData, <epmodel/ResourceObject/MaterialPropertyGlazingSpectralData.hpp>)

#endif
