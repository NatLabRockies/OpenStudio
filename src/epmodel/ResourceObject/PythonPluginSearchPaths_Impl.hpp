/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINSEARCHPATHS_IMPL_HPP
#define EPMODEL_PYTHONPLUGINSEARCHPATHS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PythonPluginSearchPaths_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PythonPluginSearchPaths_Impl() override = default;

      bool addCurrentWorkingDirectoryToSearchPath() const;
      bool setAddCurrentWorkingDirectoryToSearchPath(bool addCurrentWorkingDirectoryToSearchPath);
      bool isAddCurrentWorkingDirectoryToSearchPathDefaulted() const;
      void resetAddCurrentWorkingDirectoryToSearchPath();

      bool addInputFileDirectoryToSearchPath() const;
      bool setAddInputFileDirectoryToSearchPath(bool addInputFileDirectoryToSearchPath);
      bool isAddInputFileDirectoryToSearchPathDefaulted() const;
      void resetAddInputFileDirectoryToSearchPath();

      bool addEpinEnvironmentVariableToSearchPath() const;
      bool setAddEpinEnvironmentVariableToSearchPath(bool addEpinEnvironmentVariableToSearchPath);
      bool isAddEpinEnvironmentVariableToSearchPathDefaulted() const;
      void resetAddEpinEnvironmentVariableToSearchPath();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
