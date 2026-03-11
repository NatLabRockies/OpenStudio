/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINVARIABLE_IMPL_HPP
#define EPMODEL_PYTHONPLUGINVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class PythonPluginTrendVariable;
  class PythonPluginOutputVariable;

  namespace detail {

    class EPMODEL_API PythonPluginVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PythonPluginVariable_Impl() override = default;

      std::vector<PythonPluginTrendVariable> pythonPluginTrendVariables() const;
      std::vector<PythonPluginOutputVariable> pythonPluginOutputVariables() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PYTHONPLUGINVARIABLE_IMPL_HPP
