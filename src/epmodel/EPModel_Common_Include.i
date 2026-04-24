#ifndef EPMODEL_COMMON_INCLUDE_I
#define EPMODEL_COMMON_INCLUDE_I

%include <utilities/UtilitiesAPI.hpp>
#define EPMODEL_API

%include <utilities/core/CommonInclude.i>
%import <utilities/core/CommonImport.i>
%import <utilities/Utilities.i>

%ignore openstudio::epmodel::detail;
%ignore openstudio::epmodel::Model::getOrCreateTransientByName;
%ignore openstudio::epmodel::Model::getOrCreateTransientByNameOrCreate;
%ignore openstudio::epmodel::Model::getConcreteModelObjects;

%{
  #include <epmodel/Model.hpp>
  #include <epmodel/Model_Impl.hpp>
  #include <epmodel/ModelObject/ModelObject.hpp>
  #include <epmodel/ModelObject/ModelObject_Impl.hpp>
  #include <epmodel/ResourceObject/ResourceObject.hpp>
  #include <epmodel/ResourceObject/ResourceObject_Impl.hpp>
  #include <epmodel/Schedule/Schedule.hpp>
  #include <utilities/sql/SqlFile.hpp>

  using namespace openstudio;
  using namespace openstudio::epmodel;
%}

%define EPMODELOBJECT_TEMPLATES(_name)
  %ignore std::vector<openstudio::epmodel::_name>::vector(size_type);
  %ignore std::vector<openstudio::epmodel::_name>::resize(size_type);
  %template(_name##Vector) std::vector<openstudio::epmodel::_name>;
  %template(Optional##_name) boost::optional<openstudio::epmodel::_name>;
%enddef

#endif
