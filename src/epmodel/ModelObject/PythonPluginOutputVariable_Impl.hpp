/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINOUTPUTVARIABLE_IMPL_HPP
#define EPMODEL_PYTHONPLUGINOUTPUTVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PythonPluginOutputVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PythonPluginOutputVariable_Impl() override = default;

      std::string typeofDatainVariable() const;
      bool setTypeofDatainVariable(const std::string& typeofDatainVariable);

      std::string updateFrequency() const;
      bool setUpdateFrequency(const std::string& updateFrequency);

      boost::optional<std::string> units() const;
      bool setUnits(const std::string& units);
      void resetUnits();

      boost::optional<std::string> resourceType() const;
      bool setResourceType(const std::string& resourceType);
      void resetResourceType();

      boost::optional<std::string> groupType() const;
      bool setGroupType(const std::string& groupType);
      void resetGroupType();

      boost::optional<std::string> endUseCategory() const;
      bool setEndUseCategory(const std::string& endUseCategory);
      void resetEndUseCategory();

      boost::optional<std::string> endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PYTHONPLUGINOUTPUTVARIABLE_IMPL_HPP
