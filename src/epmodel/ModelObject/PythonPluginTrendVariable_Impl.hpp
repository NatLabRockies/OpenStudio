/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINTRENDVARIABLE_IMPL_HPP
#define EPMODEL_PYTHONPLUGINTRENDVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PythonPluginTrendVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PythonPluginTrendVariable_Impl() override = default;

      int numberofTimestepstobeLogged() const;
      bool setNumberofTimestepstobeLogged(int numberofTimestepstobeLogged);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
