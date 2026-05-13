#ifndef EPMODEL_I
#define EPMODEL_I

#ifdef SWIGPYTHON
  %module(directors="1") openstudioepmodel
#endif

%include <epmodel/EPModel_Common_Include.i>

namespace openstudio {
namespace epmodel {
class Model;
%feature("valuewrapper") Model;
}
}

// Root EPModel owns ModelObject and ResourceObject as the common EPModel object
// bases. Schedule is included here because Model directly returns Schedule from
// its always-on schedule accessors.
%include <epmodel/ModelObject/ModelObject.hpp>
%include <epmodel/ResourceObject/ResourceObject.hpp>
// Using %import: we need SWIG to see the full definition of ScheduleBase (to resolve the inheritance chain for Schedule),
// not to generate bindings for it in the root module
%import <epmodel/ScheduleBase/ScheduleBase.hpp>
%include <epmodel/Schedule/Schedule.hpp>

// Root-owned classes do not pass through submodule EPMODELOBJECT_WRAP entries,
// so emit their vector/optional wrappers here. This matches canonical model's
// ModelObjectVector treatment and keeps APIs returning std::vector<ModelObject>
// from degrading to opaque SwigPyObject values in Python.
EPMODELOBJECT_TEMPLATES(ModelObject, 0)
EPMODELOBJECT_TEMPLATES(ResourceObject, 0)
EPMODELOBJECT_TEMPLATES(Schedule, 0)

// These templated C++ helper APIs are used internally by EPModel objects and are
// not directly representable as useful Ruby/Python binding methods.
%ignore openstudio::epmodel::Model::getOrCreateTransientByName;
%ignore openstudio::epmodel::Model::getOrCreateTransientByNameOrCreate;
%ignore openstudio::epmodel::Model::getConcreteModelObjects;

#ifdef SWIGPYTHON
  // `None` is a Python keyword. Keep the C++ enum spelling unchanged, but expose
  // an explicit Python-safe name instead of relying on SWIG's automatic rename.
  %rename(None_) openstudio::epmodel::SanitizationPolicy::None;
#endif

%include <epmodel/Model.hpp>

#ifdef SWIGPYTHON
  %include <epmodel/EPModel_Python_Submodules.i>
#endif

%template(OptionalEPModel) boost::optional<openstudio::epmodel::Model>;

#endif
