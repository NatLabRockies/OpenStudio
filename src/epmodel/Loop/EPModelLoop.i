#ifndef EPMODEL_Loop_I
#define EPMODEL_Loop_I

#ifdef SWIGPYTHON
  %module openstudioepmodelloop
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ParentObject/EPModelParentObject.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

%{
  #include <epmodel/Loop/AirLoopHVAC_Impl.hpp>
%}

EPMODELOBJECT_WRAP(Loop, <epmodel/Loop/Loop.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVAC, <epmodel/Loop/AirLoopHVAC.hpp>)

namespace openstudio {
namespace epmodel {
  std::vector<AirLoopHVAC> getAirLoopHVACs(const Model& model);
}
}

%inline {
  namespace openstudio {
  namespace epmodel {
    std::vector<AirLoopHVAC> getAirLoopHVACs(const Model& model) {
      return model.getConcreteModelObjects<AirLoopHVAC>();
    }
  }
  }
}

#if defined SWIGRUBY
  %init %{
    rb_eval_string("OpenStudio::EPModel::Model.class_eval { define_method(:getAirLoopHVACs) { OpenStudio::EPModel::getAirLoopHVACs(self); } }");
  %}
#endif

EPMODELOBJECT_WRAP(PlantLoop, <epmodel/Loop/PlantLoop.hpp>)

#endif
