#ifndef EPMODEL_COMMON_INCLUDE_I
#define EPMODEL_COMMON_INCLUDE_I

%include <utilities/UtilitiesAPI.hpp>
#define EPMODEL_API

%include <utilities/core/CommonInclude.i>
%import <utilities/core/CommonImport.i>
%import <utilities/Utilities.i>

%ignore openstudio::epmodel::detail;

%{
  #include <epmodel/Model.hpp>
  #include <epmodel/EPModelObjectIncludes.hpp>

  #include <utilities/data/DataEnums.hpp>
  #include <utilities/sql/SqlFile.hpp>
  #include <utilities/time/Date.hpp>

  using namespace openstudio;
  using namespace openstudio::epmodel;
%}

// Vector/Optional directives
%define EPMODELOBJECT_TEMPLATES(_name, _isUnique)
#if !(_isUnique)
  %ignore std::vector<openstudio::epmodel::_name>::vector(size_type);
  %ignore std::vector<openstudio::epmodel::_name>::resize(size_type);
  %template(_name##Vector) std::vector<openstudio::epmodel::_name>;
#endif
  %template(Optional##_name) boost::optional<openstudio::epmodel::_name>;
%enddef // EPMODELOBJECT_TEMPLATES

%define EPMODELEXTENSIBLEGROUP_TEMPLATES(_name)
  EPMODELOBJECT_TEMPLATES(_name, 0)
%enddef

// C++ methods for extending, so we can call from wrapper. Such as to_XXX, model.getXXXByName, etc
%define EPMODELOBJECT_CPP_EXTENSION(_name, _isUnique, _isConcrete)
  namespace openstudio {
    namespace epmodel {
      boost::optional<_name> to##_name(const openstudio::IdfObject& idfObject);
#if _isUnique
      _name get##_name(openstudio::epmodel::Model& t_model);
      boost::optional<_name> getOptional##_name(const openstudio::epmodel::Model& t_model);
#else
      boost::optional<_name> get##_name(const Model &t_model, const openstudio::Handle &t_handle);
      std::vector<_name> get##_name##s(const Model &t_model);
      boost::optional<_name> get##_name##ByName(const Model &t_model, const std::string &t_name);
      std::vector<_name> get##_name##sByName(const Model &t_model, const std::string &t_name, bool t_exactMatch);
#endif
    }
  }

  %inline {
    namespace openstudio {
      namespace epmodel {
        boost::optional<_name> to##_name(const openstudio::IdfObject& idfObject) {
          return idfObject.optionalCast<_name>();
        }

#if _isUnique
        _name get##_name(openstudio::epmodel::Model& t_model) {
          return t_model.getUniqueModelObject<openstudio::epmodel::##_name>();
        }
        boost::optional<_name> getOptional##_name(const openstudio::epmodel::Model& t_model) {
          return t_model.getOptionalUniqueModelObject<openstudio::epmodel::##_name>();
        }
#else
        boost::optional<_name> get##_name(const Model &t_model, const openstudio::Handle &t_handle) {
          return t_model.getModelObject<_name>(t_handle);
        }

        std::vector<_name> get##_name##s(const Model &t_model) {
          #if _isConcrete
            return t_model.getConcreteModelObjects<_name>();
          #else
            return t_model.getModelObjects<_name>();
          #endif
        }
        boost::optional<_name> get##_name##ByName(const Model &t_model, const std::string &t_name) {
          #if _isConcrete
            return t_model.getConcreteModelObjectByName<_name>(t_name);
          #else
            return t_model.getModelObjectByName<_name>(t_name);
          #endif
        }
        std::vector<_name> get##_name##sByName(const Model &t_model, const std::string &t_name, bool t_exactMatch) {
          #if _isConcrete
            return t_model.getConcreteModelObjectsByName<_name>(t_name, t_exactMatch);
          #else
            return t_model.getModelObjectsByName<_name>(t_name, t_exactMatch);
          #endif
        }
#endif
      }
    }
  }
%enddef


#if defined SWIGRUBY
// Patch EPModel's ModelObject instead of the shared IdfObject base. Canonical
// model bindings also install to_<Type> helpers on IdfObject, and using that
// shared surface here would make same-named helpers such as to_Node collide
// across openstudio.model and openstudio.epmodel.
  %define EPMODELOBJECT_WRAPPER_EXTENSION(_name, _isUnique)
  %init %{
    rb_eval_string("OpenStudio::EPModel::ModelObject.class_eval { define_method(:to_" #_name ") { OpenStudio::EPModel::to" #_name "(self); } }");
  %}
#  if _isUnique
  %init %{
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_name ") { OpenStudio::EPModel::get" #_name "(self); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:getOptional" #_name ") { OpenStudio::EPModel::getOptional" #_name "(self); } }");
  %}
#  else
  %init %{
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_name ") { |handle| OpenStudio::EPModel::get" #_name "(self, handle); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_name "s) { OpenStudio::EPModel::get" #_name "s(self); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_name "ByName) { |name| OpenStudio::EPModel::get" #_name "ByName(self, name); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_name "sByName) { |name, exactMatch| OpenStudio::EPModel::get" #_name "sByName(self, name, exactMatch); } }");
  %}
#  endif
  %enddef // EPMODELOBJECT_WRAPPER_EXTENSION

  %define EPMODELOBJECT_ALIAS_CLASS_DEPRECATED_AT(_oldName, _newName, _deprecatedAtVersionMajor, _deprecatedAtVersionMinor, _deprecatedAtVersionPatch)
  %init %{
    rb_eval_string("OpenStudio::EPModel::" #_oldName " = OpenStudio::EPModel::" #_newName "");

    rb_eval_string("OpenStudio::EPModel::ModelObject.class_eval { define_method(:to_" #_oldName ") { OpenStudio::logFree(OpenStudio::Warn, 'openstudio.model._oldName', 'Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName'); OpenStudio::EPModel::to" #_newName "(self); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_oldName ") { |handle| OpenStudio::logFree(OpenStudio::Warn, 'openstudio.model._oldName', 'Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName');OpenStudio::EPModel::get" #_newName "(self, handle); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_oldName "s) { OpenStudio::logFree(OpenStudio::Warn, 'openstudio.model._oldName', 'Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName'); OpenStudio::EPModel::get" #_newName "s(self); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_oldName "ByName) { |name| OpenStudio::logFree(OpenStudio::Warn, 'openstudio.model._oldName', 'Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName'); OpenStudio::EPModel::get" #_newName "ByName(self, name); } }");
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:get" #_oldName "sByName) { |name, exactMatch| OpenStudio::logFree(OpenStudio::Warn, 'openstudio.model._oldName', 'Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName'); OpenStudio::EPModel::get" #_newName "sByName(self, name, exactMatch); } }");
  %}
  %enddef

#elif defined SWIGPYTHON

    %pythoncode %{
# Import common modules
import typing
import warnings
%}

  %define EPMODELOBJECT_WRAPPER_EXTENSION(_name, _isUnique)
// Patch EPModel's ModelObject instead of the shared IdfObject base. Canonical
// model bindings also install to_<Type> helpers on IdfObject, and using that
// shared surface here would make same-named helpers such as to_Node collide
// across openstudio.model and openstudio.epmodel.
  %pythoncode %{
    def _to_##_name(self) -> Optional##_name:
        """Try to cast the ModelObject to a _name.

        :return: An Optional _name.
        """
        return to##_name(self)
    openstudioepmodel.ModelObject.to_##_name = _to_##_name
  %}

#  if _isUnique
  %pythoncode %{
    def _get##_name(self) -> _name:
        """Get or instantiate a UniqueModelObject of type _name.

        :return: An existing _name or a newly instantiated one.
        """
        return get##_name(self)
    openstudioepmodel.Model.get##_name = _get##_name

    def _getOptional##_name(self) -> Optional##_name:
        """Return a UniqueModelObject of type _name only if it's already present in the Model.

        :return: An Optional _name.
        """
        return getOptional##_name(self)
    openstudioepmodel.Model.getOptional##_name = _getOptional##_name
  %}
#  else
  %pythoncode %{
    def _get##_name(self, t_handle: typing.Union[openstudioutilitiescore.UUID, str]) -> Optional##_name:
        """Try to get an object of type _name referenced by its handle.

        :param t_handle: The object's handle
        :return: An Optional _name.
        """
        if isinstance(t_handle, str):
            t_handle = openstudioutilitiescore.toUUID(t_handle)
        return get##_name(self, t_handle)
    openstudioepmodel.Model.get##_name = _get##_name

    def _get##_name##s(self) -> _name##Vector:
        """Get a vector of all objects of type _name in the model.

        :return: A vector of _name.
        """
        return get##_name##s(self)
    openstudioepmodel.Model.get##_name##s = _get##_name##s

    def _get##_name##ByName(self, t_name: str) -> Optional##_name:
        """Try to get an object of type _name that has this specific name (case-insentive).

        :param t_name: The object's name
        :return: An Optional _name.
        """
        return get##_name##ByName(self, t_name)
    openstudioepmodel.Model.get##_name##ByName = _get##_name##ByName

    def _get##_name##sByName(self, t_name: str, t_exactMatch: bool) -> _name##Vector:
        """Returns all objects of type _name named t_name (case insensitive).

        :param t_name: The object's name
        :param t_exactMatch: if false, will return all objects with name or name plus an integer suffix

        :return: A vector of matches.
        """
        return get##_name##sByName(self, t_name, t_exactMatch)
    openstudioepmodel.Model.get##_name##sByName = _get##_name##sByName
  %}
#  endif
  %enddef // EPMODELOBJECT_WRAPPER_EXTENSION

  %define EPMODELOBJECT_ALIAS_CLASS_DEPRECATED_AT(_oldName, _newName, _deprecatedAtVersionMajor, _deprecatedAtVersionMinor, _deprecatedAtVersionPatch)
  %pythoncode %{

    _oldName = _newName

    def _to_##_oldName(self) -> Optional##_newName:
        """Try to cast the ModelObject to a _newName.

        :return: An Optional _newName.

        .. deprecated:: _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch
           Use :meth:`"IdfObject.to_##_newName"`.
        """
        warnings.warn("_oldName was deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.", category=FutureWarning)
        openstudioutilitiescore.logFree(openstudioutilitiescore.Warn, "openstudio.model._oldName", "Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.")
        return to##_newName(self)
    openstudioutilitiesidf.IdfObject.to_##_oldName = _to_##_oldName

    def _get##_oldName(self, t_handle: typing.Union[openstudioutilitiescore.UUID, str]) -> Optional##_newName:
        """Try to get an object of type _newName referenced by its handle.

        :param t_handle: The object's handle
        :return: An Optional _newName.

        .. deprecated:: _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch
           Use :meth:`"Model.get##_newName"`.
        """
        warnings.warn("_oldName was deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.", category=FutureWarning)
        if isinstance(t_handle, str):
            t_handle = openstudioutilitiescore.toUUID(t_handle)
        openstudioutilitiescore.logFree(openstudioutilitiescore.Warn, "openstudio.model._oldName", "Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.")
        return get##_newName(self, t_handle)
    openstudioepmodel.Model.get##_oldName = _get##_oldName

    def _get##_oldName##s(self) -> _newName##Vector:
        """Get a vector of all objects of type _newName in the model.

        :return: A vector of _newName.

        .. deprecated:: _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch
           Use :meth:`"Model.get##_newName##s"`.
        """
        warnings.warn("_oldName was deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.", category=FutureWarning)
        openstudioutilitiescore.logFree(openstudioutilitiescore.Warn, "openstudio.model._oldName", "Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.")
        return get##_newName##s(self)
    openstudioepmodel.Model.get##_oldName##s = _get##_oldName##s

    def _get##_oldName##ByName(self, t_name: str) -> Optional##_newName:
        """Try to get an object of type _newName that has this specific name (case-insentive).

        :param t_name: The object's name
        :return: An Optional _newName.

        .. deprecated:: _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch
           Use :meth:`"Model.get##_newName##ByName"`.
        """
        warnings.warn("_oldName was deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.", category=FutureWarning)
        openstudioutilitiescore.logFree(openstudioutilitiescore.Warn, "openstudio.model._oldName", "Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.")
        return get##_newName##ByName(self, t_name)
    openstudioepmodel.Model.get##_oldName##ByName = _get##_oldName##ByName

    def _get##_oldName##sByName(self, t_name: str, t_exactMatch: bool) -> _newName##Vector:
        """Returns all objects of type _newName named t_name (case insensitive).

        :param t_name: The object's name
        :param t_exactMatch: if false, will return all objects with name or name plus an integer suffix

        :return: A vector of matches.

        .. deprecated:: _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch
           Use :meth:`"Model.get##_newName##sByName"`.
        """
        warnings.warn("_oldName was deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.", category=FutureWarning)
        openstudioutilitiescore.logFree(openstudioutilitiescore.Warn, "openstudio.model._oldName", "Deprecated at _deprecatedAtVersionMajor._deprecatedAtVersionMinor._deprecatedAtVersionPatch, use _newName.")
        return get##_newName##sByName(self, t_name, t_exactMatch)
    openstudioepmodel.Model.get##_oldName##sByName = _get##_oldName##sByName
  %}
  %enddef

#else

  #define EPMODELOBJECT_WRAPPER_EXTENSION(_name, _isUnique)
  #define EPMODELOBJECT_ALIAS_CLASS_DEPRECATED_AT(_oldName, _newName, _deprecatedAtVersionMajor, _deprecatedAtVersionMinor, _deprecatedAtVersionPatch)

#endif


%define EPMODELOBJECT_FORWARD_DECLARE(_name)
  namespace openstudio {
    namespace epmodel {
      class _name;
      %feature("valuewrapper") _name; // Allow by-value returns without needing a default ctor
      %nodefaultctor _name; // Do not generate **implicit** default constructors
      %ignore _name::_name(); // Ignore **explicit** default constructors too
    }
  }
%enddef


%define EPMODELOBJECT_WRAP(_name, _header, _isUnique, _isConcrete)
  EPMODELOBJECT_TEMPLATES(_name, _isUnique)
  %include _header
  EPMODELOBJECT_CPP_EXTENSION(_name, _isUnique, _isConcrete)
  EPMODELOBJECT_WRAPPER_EXTENSION(_name, _isUnique)
%enddef

EPMODELOBJECT_FORWARD_DECLARE(AirConditionerVariableRefrigerantFlow)
EPMODELOBJECT_FORWARD_DECLARE(AirConditionerVariableRefrigerantFlowFluidTemperatureControl)
EPMODELOBJECT_FORWARD_DECLARE(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR)
EPMODELOBJECT_FORWARD_DECLARE(AirGap)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVAC)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACControllerList)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACDedicatedOutdoorAirSystem)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACMixer)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACOutdoorAirSystem)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACOutdoorAirSystemEquipmentList)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACReturnPath)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACReturnPlenum)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACSplitter)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACSupplyPath)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACSupplyPlenum)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACUnitaryHeatPumpAirToAir)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACUnitaryHeatPumpAirToAirMultiSpeed)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACUnitarySystem)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACZoneMixer)
EPMODELOBJECT_FORWARD_DECLARE(AirLoopHVACZoneSplitter)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalDualDuctConstantVolume)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalDualDuctVAV)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalDualDuctVAVOutdoorAir)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctConstantVolumeCooledBeam)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctConstantVolumeFourPipeBeam)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctConstantVolumeFourPipeInduction)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctConstantVolumeNoReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctConstantVolumeReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctInletSideMixer)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctParallelPIUReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctSeriesPIUReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctVAVHeatAndCoolNoReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctVAVHeatAndCoolReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctVAVNoReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirTerminalSingleDuctVAVReheat)
EPMODELOBJECT_FORWARD_DECLARE(AirToAirComponent)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentCoil)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentConstantPressureDrop)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentDuct)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentFan)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentHeatExchanger)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentLeakageRatio)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentOutdoorAirFlow)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionComponentTerminalUnit)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionDuctViewFactors)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionLinkage)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkDistributionNode)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneComponentDetailedOpening)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneComponentHorizontalOpening)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneComponentSimpleOpening)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneComponentZoneExhaustFan)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneExternalNode)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneReferenceCrackConditions)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneSpecifiedFlowRate)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneSurface)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneSurfaceCrack)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkMultiZoneZone)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkOccupantVentilationControl)
EPMODELOBJECT_FORWARD_DECLARE(AirflowNetworkSimulationControl)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManager)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerAssignmentList)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerDifferentialThermostat)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerHighTemperatureTurnOff)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerHighTemperatureTurnOn)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerHybridVentilation)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerLowTemperatureTurnOff)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerLowTemperatureTurnOn)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerNightCycle)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerNightVentilation)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerOptimumStart)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerScheduledOff)
EPMODELOBJECT_FORWARD_DECLARE(AvailabilityManagerScheduledOn)
EPMODELOBJECT_FORWARD_DECLARE(Blind)
EPMODELOBJECT_FORWARD_DECLARE(BoilerHotWater)
EPMODELOBJECT_FORWARD_DECLARE(BoilerSteam)
EPMODELOBJECT_FORWARD_DECLARE(Branch)
EPMODELOBJECT_FORWARD_DECLARE(BranchList)
EPMODELOBJECT_FORWARD_DECLARE(BuildingStory)
EPMODELOBJECT_FORWARD_DECLARE(Building)
EPMODELOBJECT_FORWARD_DECLARE(CFactorUndergroundWallConstruction)
EPMODELOBJECT_FORWARD_DECLARE(ConstructionBase)
EPMODELOBJECT_FORWARD_DECLARE(CentralHeatPumpSystem)
EPMODELOBJECT_FORWARD_DECLARE(ChillerAbsorption)
EPMODELOBJECT_FORWARD_DECLARE(ChillerAbsorptionIndirect)
EPMODELOBJECT_FORWARD_DECLARE(ChillerElectric)
EPMODELOBJECT_FORWARD_DECLARE(ChillerElectricASHRAE205)
EPMODELOBJECT_FORWARD_DECLARE(ChillerElectricEIR)
EPMODELOBJECT_FORWARD_DECLARE(ChillerElectricReformulatedEIR)
EPMODELOBJECT_FORWARD_DECLARE(ChillerHeaterPerformanceElectricEIR)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDX)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXCurveFitOperatingMode)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXCurveFitPerformance)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXCurveFitSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXMultiSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXSingleSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXSingleSpeedThermalStorage)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXTwoSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXTwoStageWithHumidityControlMode)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXVariableRefrigerantFlow)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXVariableRefrigerantFlowFluidTemperatureControl)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingDXVariableSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingLowTempRadiantConstFlow)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingLowTempRadiantVarFlow)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingWater)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingWaterPanelRadiant)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingWaterToAirHeatPumpEquationFit)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit)
EPMODELOBJECT_FORWARD_DECLARE(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingDXMultiSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingDXSingleSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingDXVariableRefrigerantFlow)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingDXVariableSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingDesuperheater)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingElectric)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingElectricMultiStage)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingGas)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingGasMultiStage)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingLowTempRadiantConstFlow)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingLowTempRadiantVarFlow)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingWater)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingWaterBaseboard)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingWaterBaseboardRadiant)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingWaterToAirHeatPumpEquationFit)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit)
EPMODELOBJECT_FORWARD_DECLARE(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData)
EPMODELOBJECT_FORWARD_DECLARE(CoilPerformanceDXCooling)
EPMODELOBJECT_FORWARD_DECLARE(CoilSystemCoolingDX)
EPMODELOBJECT_FORWARD_DECLARE(CoilSystemCoolingDXHeatExchangerAssisted)
EPMODELOBJECT_FORWARD_DECLARE(CoilSystemCoolingWater)
EPMODELOBJECT_FORWARD_DECLARE(CoilSystemCoolingWaterHeatExchangerAssisted)
EPMODELOBJECT_FORWARD_DECLARE(CoilSystemHeatingDX)
EPMODELOBJECT_FORWARD_DECLARE(CoilSystemIntegratedHeatPumpAirSource)
EPMODELOBJECT_FORWARD_DECLARE(CoilUserDefined)
EPMODELOBJECT_FORWARD_DECLARE(CoilWaterHeatingAirToWaterHeatPump)
EPMODELOBJECT_FORWARD_DECLARE(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData)
EPMODELOBJECT_FORWARD_DECLARE(CoilWaterHeatingAirToWaterHeatPumpWrapped)
EPMODELOBJECT_FORWARD_DECLARE(CoilWaterHeatingDesuperheater)
EPMODELOBJECT_FORWARD_DECLARE(ComponentCostAdjustments)
EPMODELOBJECT_FORWARD_DECLARE(ConnectorMixer)
EPMODELOBJECT_FORWARD_DECLARE(ConnectorSplitter)
EPMODELOBJECT_FORWARD_DECLARE(Construction)
EPMODELOBJECT_FORWARD_DECLARE(ConstructionAirBoundary)
EPMODELOBJECT_FORWARD_DECLARE(ConstructionWithInternalSource)
EPMODELOBJECT_FORWARD_DECLARE(ControllerMechanicalVentilation)
EPMODELOBJECT_FORWARD_DECLARE(ControllerOutdoorAir)
EPMODELOBJECT_FORWARD_DECLARE(ControllerWaterCoil)
EPMODELOBJECT_FORWARD_DECLARE(ConvergenceLimits)
EPMODELOBJECT_FORWARD_DECLARE(CoolingTowerPerformanceCoolTools)
EPMODELOBJECT_FORWARD_DECLARE(CoolingTowerPerformanceYorkCalc)
EPMODELOBJECT_FORWARD_DECLARE(CoolingTowerSingleSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoolingTowerTwoSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CoolingTowerVariableSpeed)
EPMODELOBJECT_FORWARD_DECLARE(CurrencyType)
EPMODELOBJECT_FORWARD_DECLARE(Curve)
EPMODELOBJECT_FORWARD_DECLARE(CurveBicubic)
EPMODELOBJECT_FORWARD_DECLARE(CurveBiquadratic)
EPMODELOBJECT_FORWARD_DECLARE(CurveChillerPartLoadWithLift)
EPMODELOBJECT_FORWARD_DECLARE(CurveCubic)
EPMODELOBJECT_FORWARD_DECLARE(CurveCubicLinear)
EPMODELOBJECT_FORWARD_DECLARE(CurveDoubleExponentialDecay)
EPMODELOBJECT_FORWARD_DECLARE(CurveExponent)
EPMODELOBJECT_FORWARD_DECLARE(CurveExponentialDecay)
EPMODELOBJECT_FORWARD_DECLARE(CurveExponentialSkewNormal)
EPMODELOBJECT_FORWARD_DECLARE(CurveFanPressureRise)
EPMODELOBJECT_FORWARD_DECLARE(CurveFunctionalPressureDrop)
EPMODELOBJECT_FORWARD_DECLARE(CurveLinear)
EPMODELOBJECT_FORWARD_DECLARE(CurveQuadLinear)
EPMODELOBJECT_FORWARD_DECLARE(CurveQuadratic)
EPMODELOBJECT_FORWARD_DECLARE(CurveQuadraticLinear)
EPMODELOBJECT_FORWARD_DECLARE(CurveQuartic)
EPMODELOBJECT_FORWARD_DECLARE(CurveQuintLinear)
EPMODELOBJECT_FORWARD_DECLARE(CurveRectangularHyperbola1)
EPMODELOBJECT_FORWARD_DECLARE(CurveRectangularHyperbola2)
EPMODELOBJECT_FORWARD_DECLARE(CurveSigmoid)
EPMODELOBJECT_FORWARD_DECLARE(CurveTriquadratic)
EPMODELOBJECT_FORWARD_DECLARE(DaylightingDeviceLightWell)
EPMODELOBJECT_FORWARD_DECLARE(DaylightingDeviceShelf)
EPMODELOBJECT_FORWARD_DECLARE(DaylightingDeviceTubular)
EPMODELOBJECT_FORWARD_DECLARE(DesignDay)
EPMODELOBJECT_FORWARD_DECLARE(DesignSpecificationOutdoorAir)
EPMODELOBJECT_FORWARD_DECLARE(DesignSpecificationOutdoorAirSpaceList)
EPMODELOBJECT_FORWARD_DECLARE(DistrictCooling)
EPMODELOBJECT_FORWARD_DECLARE(DistrictHeatingSteam)
EPMODELOBJECT_FORWARD_DECLARE(DistrictHeatingWater)
EPMODELOBJECT_FORWARD_DECLARE(Duct)
EPMODELOBJECT_FORWARD_DECLARE(ElectricEquipment)
EPMODELOBJECT_FORWARD_DECLARE(ElectricEquipmentITEAirCooled)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterDistribution)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterInverterLookUpTable)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterInverterPVWatts)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterInverterSimple)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterStorageConverter)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterStorageLiIonNMCBattery)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterStorageSimple)
EPMODELOBJECT_FORWARD_DECLARE(ElectricLoadCenterTransformer)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemActuator)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemConstructionIndexVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemCurveOrTableIndexVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemGlobalVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemInternalVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemMeteredOutputVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemOutputVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemProgram)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemProgramCallingManager)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemSensor)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemSubroutine)
EPMODELOBJECT_FORWARD_DECLARE(EnergyManagementSystemTrendVariable)
EPMODELOBJECT_FORWARD_DECLARE(EnvironmentalImpactFactors)
EPMODELOBJECT_FORWARD_DECLARE(EvaporativeCoolerDirectResearchSpecial)
EPMODELOBJECT_FORWARD_DECLARE(EvaporativeCoolerIndirectResearchSpecial)
EPMODELOBJECT_FORWARD_DECLARE(EvaporativeFluidCoolerSingleSpeed)
EPMODELOBJECT_FORWARD_DECLARE(EvaporativeFluidCoolerTwoSpeed)
EPMODELOBJECT_FORWARD_DECLARE(ExteriorFuelEquipment)
EPMODELOBJECT_FORWARD_DECLARE(ExteriorLights)
EPMODELOBJECT_FORWARD_DECLARE(ExteriorWaterEquipment)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterface)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceActuator)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitExportFromVariable)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitExportToActuator)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitExportToSchedule)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitExportToVariable)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitImport)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitImportFromVariable)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitImportToActuator)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitImportToSchedule)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceFunctionalMockupUnitImportToVariable)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceSchedule)
EPMODELOBJECT_FORWARD_DECLARE(ExternalInterfaceVariable)
EPMODELOBJECT_FORWARD_DECLARE(FFactorGroundFloorConstruction)
EPMODELOBJECT_FORWARD_DECLARE(FanComponentModel)
EPMODELOBJECT_FORWARD_DECLARE(FanConstantVolume)
EPMODELOBJECT_FORWARD_DECLARE(FanOnOff)
EPMODELOBJECT_FORWARD_DECLARE(FanSystemModel)
EPMODELOBJECT_FORWARD_DECLARE(FanVariableVolume)
EPMODELOBJECT_FORWARD_DECLARE(FanZoneExhaust)
EPMODELOBJECT_FORWARD_DECLARE(FenestrationMaterial)
EPMODELOBJECT_FORWARD_DECLARE(FluidCoolerSingleSpeed)
EPMODELOBJECT_FORWARD_DECLARE(FluidCoolerTwoSpeed)
EPMODELOBJECT_FORWARD_DECLARE(FluidPropertiesName)
EPMODELOBJECT_FORWARD_DECLARE(FoundationKiva)
EPMODELOBJECT_FORWARD_DECLARE(FoundationKivaSettings)
EPMODELOBJECT_FORWARD_DECLARE(FuelFactors)
EPMODELOBJECT_FORWARD_DECLARE(Gas)
EPMODELOBJECT_FORWARD_DECLARE(GasEquipment)
EPMODELOBJECT_FORWARD_DECLARE(GasLayer)
EPMODELOBJECT_FORWARD_DECLARE(GasMixture)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCell)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellAirSupply)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellAuxiliaryHeater)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellElectricalStorage)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellExhaustGasToWaterHeatExchanger)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellInverter)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellPowerModule)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellStackCooler)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelCellWaterSupply)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorFuelSupply)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorMicroTurbine)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorPVWatts)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorPhotovoltaic)
EPMODELOBJECT_FORWARD_DECLARE(GeneratorWindTurbine)
EPMODELOBJECT_FORWARD_DECLARE(Glazing)
EPMODELOBJECT_FORWARD_DECLARE(GroundHeatExchangerHorizontalTrench)
EPMODELOBJECT_FORWARD_DECLARE(GroundHeatExchangerVertical)
EPMODELOBJECT_FORWARD_DECLARE(HVACComponent)
EPMODELOBJECT_FORWARD_DECLARE(HeaderedPumpsConstantSpeed)
EPMODELOBJECT_FORWARD_DECLARE(HeaderedPumpsVariableSpeed)
EPMODELOBJECT_FORWARD_DECLARE(HeatBalanceAlgorithm)
EPMODELOBJECT_FORWARD_DECLARE(HeatExchangerAirToAirSensibleAndLatent)
EPMODELOBJECT_FORWARD_DECLARE(HeatExchangerDesiccantBalancedFlow)
EPMODELOBJECT_FORWARD_DECLARE(HeatExchangerDesiccantBalancedFlowPerformanceDataType1)
EPMODELOBJECT_FORWARD_DECLARE(HeatExchangerFluidToFluid)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpAirToWater)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpAirToWaterFuelFiredCooling)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpAirToWaterFuelFiredHeating)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpPlantLoopEIRCooling)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpPlantLoopEIRHeating)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpWaterToWaterEquationFitCooling)
EPMODELOBJECT_FORWARD_DECLARE(HeatPumpWaterToWaterEquationFitHeating)
EPMODELOBJECT_FORWARD_DECLARE(HotWaterEquipment)
EPMODELOBJECT_FORWARD_DECLARE(HumidifierSteamElectric)
EPMODELOBJECT_FORWARD_DECLARE(HumidifierSteamGas)
EPMODELOBJECT_FORWARD_DECLARE(InfraredTransparentMaterial)
EPMODELOBJECT_FORWARD_DECLARE(InsideSurfaceConvectionAlgorithm)
EPMODELOBJECT_FORWARD_DECLARE(InteriorPartitionSurface)
EPMODELOBJECT_FORWARD_DECLARE(LayeredConstruction)
EPMODELOBJECT_FORWARD_DECLARE(LifeCycleCost)
EPMODELOBJECT_FORWARD_DECLARE(LifeCycleCostParameters)
EPMODELOBJECT_FORWARD_DECLARE(LifeCycleCostUsePriceEscalation)
EPMODELOBJECT_FORWARD_DECLARE(Lights)
EPMODELOBJECT_FORWARD_DECLARE(LoadProfilePlant)
EPMODELOBJECT_FORWARD_DECLARE(Loop)
EPMODELOBJECT_FORWARD_DECLARE(MasslessOpaqueMaterial)
EPMODELOBJECT_FORWARD_DECLARE(Material)
EPMODELOBJECT_FORWARD_DECLARE(MaterialPropertyGlazingSpectralData)
EPMODELOBJECT_FORWARD_DECLARE(MaterialPropertyMoisturePenetrationDepthSettings)
EPMODELOBJECT_FORWARD_DECLARE(MaterialPropertyPhaseChange)
EPMODELOBJECT_FORWARD_DECLARE(MaterialPropertyPhaseChangeHysteresis)
EPMODELOBJECT_FORWARD_DECLARE(MeterCustom)
EPMODELOBJECT_FORWARD_DECLARE(MeterCustomDecrement)
EPMODELOBJECT_FORWARD_DECLARE(Mixer)
EPMODELOBJECT_FORWARD_DECLARE(ModelObject)
EPMODELOBJECT_FORWARD_DECLARE(Node)
EPMODELOBJECT_FORWARD_DECLARE(NodeList)
EPMODELOBJECT_FORWARD_DECLARE(OpaqueMaterial)
EPMODELOBJECT_FORWARD_DECLARE(OtherEquipment)
EPMODELOBJECT_FORWARD_DECLARE(OutdoorAirMixer)
EPMODELOBJECT_FORWARD_DECLARE(OutputConstructions)
EPMODELOBJECT_FORWARD_DECLARE(OutputControlFiles)
EPMODELOBJECT_FORWARD_DECLARE(OutputControlReportingTolerances)
EPMODELOBJECT_FORWARD_DECLARE(OutputControlResilienceSummaries)
EPMODELOBJECT_FORWARD_DECLARE(OutputControlTableStyle)
EPMODELOBJECT_FORWARD_DECLARE(OutputControlTimestamp)
EPMODELOBJECT_FORWARD_DECLARE(OutputDebuggingData)
EPMODELOBJECT_FORWARD_DECLARE(OutputDiagnostics)
EPMODELOBJECT_FORWARD_DECLARE(OutputEnergyManagementSystem)
EPMODELOBJECT_FORWARD_DECLARE(OutputEnvironmentalImpactFactors)
EPMODELOBJECT_FORWARD_DECLARE(OutputJSON)
EPMODELOBJECT_FORWARD_DECLARE(OutputSQLite)
EPMODELOBJECT_FORWARD_DECLARE(OutputSchedules)
EPMODELOBJECT_FORWARD_DECLARE(OutputTableAnnual)
EPMODELOBJECT_FORWARD_DECLARE(OutputTableMonthly)
EPMODELOBJECT_FORWARD_DECLARE(OutputTableSummaryReports)
EPMODELOBJECT_FORWARD_DECLARE(OutputVariable)
EPMODELOBJECT_FORWARD_DECLARE(OutsideSurfaceConvectionAlgorithm)
EPMODELOBJECT_FORWARD_DECLARE(ParentObject)
EPMODELOBJECT_FORWARD_DECLARE(People)
EPMODELOBJECT_FORWARD_DECLARE(PerformancePrecisionTradeoffs)
EPMODELOBJECT_FORWARD_DECLARE(PhotovoltaicPerformanceSandia)
EPMODELOBJECT_FORWARD_DECLARE(PhotovoltaicPerformanceSimple)
EPMODELOBJECT_FORWARD_DECLARE(PipeAdiabatic)
EPMODELOBJECT_FORWARD_DECLARE(PipeIndoor)
EPMODELOBJECT_FORWARD_DECLARE(PipeOutdoor)
EPMODELOBJECT_FORWARD_DECLARE(PlanarSurface)
EPMODELOBJECT_FORWARD_DECLARE(PlanarSurfaceGroup)
EPMODELOBJECT_FORWARD_DECLARE(PlantComponentTemperatureSource)
EPMODELOBJECT_FORWARD_DECLARE(PlantComponentUserDefined)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationChillerHeaterChangeover)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationComponentSetpoint)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationCoolingLoad)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationHeatingLoad)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorDewpoint)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorDewpointDifference)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorDryBulb)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorDryBulbDifference)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorRelativeHumidity)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorWetBulb)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationOutdoorWetBulbDifference)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationRangeBasedScheme)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationScheme)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationSchemes)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentList)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationThermalEnergyStorage)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationUncontrolled)
EPMODELOBJECT_FORWARD_DECLARE(PlantEquipmentOperationUserDefined)
EPMODELOBJECT_FORWARD_DECLARE(PlantLoop)
EPMODELOBJECT_FORWARD_DECLARE(PumpConstantSpeed)
EPMODELOBJECT_FORWARD_DECLARE(PumpVariableSpeed)
EPMODELOBJECT_FORWARD_DECLARE(PythonPluginInstance)
EPMODELOBJECT_FORWARD_DECLARE(PythonPluginOutputVariable)
EPMODELOBJECT_FORWARD_DECLARE(PythonPluginSearchPaths)
EPMODELOBJECT_FORWARD_DECLARE(PythonPluginTrendVariable)
EPMODELOBJECT_FORWARD_DECLARE(PythonPluginVariable)
EPMODELOBJECT_FORWARD_DECLARE(RefractionExtinctionGlazing)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationAirChiller)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCase)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCompressor)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCompressorRack)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCondenserAirCooled)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCondenserCascade)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCondenserEvaporativeCooled)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationCondenserWaterCooled)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationGasCoolerAirCooled)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationSecondarySystem)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationSubcooler)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationSubcoolerLiquidSuction)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationSubcoolerMechanical)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationSystem)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationTranscriticalSystem)
EPMODELOBJECT_FORWARD_DECLARE(RefrigerationWalkIn)
EPMODELOBJECT_FORWARD_DECLARE(ResourceObject)
EPMODELOBJECT_FORWARD_DECLARE(RoofVegetation)
EPMODELOBJECT_FORWARD_DECLARE(RunPeriod)
EPMODELOBJECT_FORWARD_DECLARE(RunPeriodControlDaylightSavingTime)
EPMODELOBJECT_FORWARD_DECLARE(RunPeriodControlSpecialDays)
EPMODELOBJECT_FORWARD_DECLARE(Schedule)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleCompact)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleConstant)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleDay)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleFile)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleTypeLimits)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleWeek)
EPMODELOBJECT_FORWARD_DECLARE(ScheduleYear)
EPMODELOBJECT_FORWARD_DECLARE(Screen)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManager)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerColdest)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerFollowGroundTemperature)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerFollowOutdoorAirTemperature)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerFollowSystemNodeTemperature)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMixedAir)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMultiZoneCoolingAverage)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMultiZoneHeatingAverage)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMultiZoneHumidityMaximum)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMultiZoneHumidityMinimum)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMultiZoneMaximumHumidityAverage)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerMultiZoneMinimumHumidityAverage)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerOutdoorAirPretreat)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerOutdoorAirReset)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerScheduled)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerScheduledDualSetpoint)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneCooling)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneHeating)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneHumidityMaximum)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneHumidityMinimum)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneOneStageCooling)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneOneStageHeating)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSingleZoneReheat)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSystemNodeResetHumidity)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerSystemNodeResetTemperature)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerWarmest)
EPMODELOBJECT_FORWARD_DECLARE(SetpointManagerWarmestTemperatureFlow)
EPMODELOBJECT_FORWARD_DECLARE(Shade)
EPMODELOBJECT_FORWARD_DECLARE(ShadingControl)
EPMODELOBJECT_FORWARD_DECLARE(ShadingMaterial)
EPMODELOBJECT_FORWARD_DECLARE(ShadowCalculation)
EPMODELOBJECT_FORWARD_DECLARE(SimpleGlazing)
EPMODELOBJECT_FORWARD_DECLARE(SimulationControl)
EPMODELOBJECT_FORWARD_DECLARE(Site)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundReflectance)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureBuildingSurface)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureDeep)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureFCfactorMethod)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureShallow)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureUndisturbedFiniteDifference)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureUndisturbedKusudaAchenbach)
EPMODELOBJECT_FORWARD_DECLARE(SiteGroundTemperatureUndisturbedXing)
EPMODELOBJECT_FORWARD_DECLARE(SiteWaterMainsTemperature)
EPMODELOBJECT_FORWARD_DECLARE(SizingParameters)
EPMODELOBJECT_FORWARD_DECLARE(SizingPlant)
EPMODELOBJECT_FORWARD_DECLARE(SizingSystem)
EPMODELOBJECT_FORWARD_DECLARE(SizingZone)
EPMODELOBJECT_FORWARD_DECLARE(SkyTemperature)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorFlatPlatePhotovoltaicThermal)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorFlatPlateWater)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorIntegralCollectorStorage)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorPerformanceFlatPlate)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorPerformanceIntegralCollectorStorage)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorPerformancePhotovoltaicThermalBIPVT)
EPMODELOBJECT_FORWARD_DECLARE(SolarCollectorPerformancePhotovoltaicThermalSimple)
EPMODELOBJECT_FORWARD_DECLARE(Space)
EPMODELOBJECT_FORWARD_DECLARE(SpaceInfiltrationDesignFlowRate)
EPMODELOBJECT_FORWARD_DECLARE(SpaceInfiltrationEffectiveLeakageArea)
EPMODELOBJECT_FORWARD_DECLARE(SpaceInfiltrationFlowCoefficient)
EPMODELOBJECT_FORWARD_DECLARE(SpaceList)
EPMODELOBJECT_FORWARD_DECLARE(SpaceType)
EPMODELOBJECT_FORWARD_DECLARE(Splitter)
EPMODELOBJECT_FORWARD_DECLARE(StandardGlazing)
EPMODELOBJECT_FORWARD_DECLARE(StandardOpaqueMaterial)
EPMODELOBJECT_FORWARD_DECLARE(SteamEquipment)
EPMODELOBJECT_FORWARD_DECLARE(StraightComponent)
EPMODELOBJECT_FORWARD_DECLARE(SubSurface)
EPMODELOBJECT_FORWARD_DECLARE(Surface)
EPMODELOBJECT_FORWARD_DECLARE(SurfaceControlMovableInsulation)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyConvectionCoefficients)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyConvectionCoefficientsMultipleSurface)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyExposedFoundationPerimeter)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyGroundSurfaces)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyIncidentSolarMultiplier)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyLocalEnvironment)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyOtherSideCoefficients)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertyOtherSideConditionsModel)
EPMODELOBJECT_FORWARD_DECLARE(SurfacePropertySurroundingSurfaces)
EPMODELOBJECT_FORWARD_DECLARE(SwimmingPoolIndoor)
EPMODELOBJECT_FORWARD_DECLARE(TableIndependentVariable)
EPMODELOBJECT_FORWARD_DECLARE(TableLookup)
EPMODELOBJECT_FORWARD_DECLARE(TemperingValve)
EPMODELOBJECT_FORWARD_DECLARE(ThermalStorageChilledWaterStratified)
EPMODELOBJECT_FORWARD_DECLARE(ThermalStorageIceDetailed)
EPMODELOBJECT_FORWARD_DECLARE(ThermalZone)
EPMODELOBJECT_FORWARD_DECLARE(ThermochromicGlazing)
EPMODELOBJECT_FORWARD_DECLARE(Thermostat)
EPMODELOBJECT_FORWARD_DECLARE(ThermostatSetpointDualSetpoint)
EPMODELOBJECT_FORWARD_DECLARE(Timestep)
EPMODELOBJECT_FORWARD_DECLARE(Version)
EPMODELOBJECT_FORWARD_DECLARE(WaterHeaterHeatPump)
EPMODELOBJECT_FORWARD_DECLARE(WaterHeaterHeatPumpWrappedCondenser)
EPMODELOBJECT_FORWARD_DECLARE(WaterHeaterMixed)
EPMODELOBJECT_FORWARD_DECLARE(WaterHeaterSizing)
EPMODELOBJECT_FORWARD_DECLARE(WaterHeaterStratified)
EPMODELOBJECT_FORWARD_DECLARE(WaterToAirComponent)
EPMODELOBJECT_FORWARD_DECLARE(WaterToWaterComponent)
EPMODELOBJECT_FORWARD_DECLARE(WaterUseConnections)
EPMODELOBJECT_FORWARD_DECLARE(WaterUseEquipment)
EPMODELOBJECT_FORWARD_DECLARE(WindowPropertyFrameAndDivider)
EPMODELOBJECT_FORWARD_DECLARE(ZoneAirContaminantBalance)
EPMODELOBJECT_FORWARD_DECLARE(ZoneAirHeatBalanceAlgorithm)
EPMODELOBJECT_FORWARD_DECLARE(ZoneAirMassFlowConservation)
EPMODELOBJECT_FORWARD_DECLARE(ZoneCapacitanceMultiplierResearchSpecial)
EPMODELOBJECT_FORWARD_DECLARE(ZoneControlContaminantController)
EPMODELOBJECT_FORWARD_DECLARE(ZoneControlHumidistat)
EPMODELOBJECT_FORWARD_DECLARE(ZoneControlThermostatStagedDualSetpoint)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACAirDistributionUnit)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACBaseboardConvectiveElectric)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACBaseboardConvectiveWater)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACBaseboardRadiantConvectiveElectric)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACBaseboardRadiantConvectiveWater)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACBaseboardRadiantConvectiveWaterDesign)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACComponent)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACCoolingPanelRadiantConvectiveWater)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACDehumidifierDX)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACEnergyRecoveryVentilator)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACEnergyRecoveryVentilatorController)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACEquipmentConnections)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACEquipmentList)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACEvaporativeCoolerUnit)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACFourPipeFanCoil)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACHighTemperatureRadiant)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACIdealLoadsAirSystem)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACLowTempRadiantConstFlow)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACLowTempRadiantConstFlowDesign)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACLowTempRadiantVarFlow)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACLowTempRadiantVarFlowDesign)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACLowTemperatureRadiantElectric)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACLowTemperatureRadiantSurfaceGroup)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACPackagedTerminalAirConditioner)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACPackagedTerminalHeatPump)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACTerminalUnitVariableRefrigerantFlow)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACUnitHeater)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACUnitVentilator)
EPMODELOBJECT_FORWARD_DECLARE(ZoneHVACWaterToAirHeatPump)
EPMODELOBJECT_FORWARD_DECLARE(ZoneMixing)
EPMODELOBJECT_FORWARD_DECLARE(ZonePropertyUserViewFactorsBySurfaceName)
EPMODELOBJECT_FORWARD_DECLARE(ZoneVentilationWindandStackOpenArea)

#endif
