#ifndef EPMODEL_I
#define EPMODEL_I

#ifdef SWIGPYTHON
  %module(directors="1") openstudioepmodel
#endif

%include <epmodel/EPModel_Common_Include.i>

%include <epmodel/ModelObject/ModelObject.hpp>
%include <epmodel/ResourceObject/ResourceObject.hpp>
%include <epmodel/Schedule/Schedule.hpp>
%include <epmodel/Model.hpp>

EPMODELOBJECT_TEMPLATES(ModelObject)
EPMODELOBJECT_TEMPLATES(ResourceObject)
EPMODELOBJECT_TEMPLATES(Schedule)
%template(OptionalEPModel) boost::optional<openstudio::epmodel::Model>;

#endif
