/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINSEARCHPATHS_HPP
#define EPMODEL_PYTHONPLUGINSEARCHPATHS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PythonPluginSearchPaths_Impl;
  }

  class EPMODEL_API PythonPluginSearchPaths : public ModelObject
  {
   public:
    explicit PythonPluginSearchPaths(const Model& model);

    virtual ~PythonPluginSearchPaths() override = default;
    PythonPluginSearchPaths(const PythonPluginSearchPaths& other) = default;
    PythonPluginSearchPaths(PythonPluginSearchPaths&& other) = default;
    PythonPluginSearchPaths& operator=(const PythonPluginSearchPaths&) = default;
    PythonPluginSearchPaths& operator=(PythonPluginSearchPaths&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model counterpart scalar semantics for PythonPlugin:SearchPaths control toggles.
    // - Field Mapping: These scalars map directly to the EnergyPlus fields
    //   Add Current Working Directory to Search Path, Add Input File Directory to Search Path, and
    //   Add epin Environment Variable to Search Path via PythonPlugin_SearchPathsFields enums.
    // - ForwardTranslator evidence: ForwardTranslatePythonPluginInstance.cpp builds PythonPlugin:SearchPaths with the
    //   same field values while managing search-path extensible entries.
    // - Excluded Fields: The Search Path extensible group remains omitted from this scalar-only pass.

    bool addCurrentWorkingDirectoryToSearchPath() const;
    bool isAddCurrentWorkingDirectoryToSearchPathDefaulted() const;
    bool setAddCurrentWorkingDirectoryToSearchPath(bool addCurrentWorkingDirectoryToSearchPath);
    void resetAddCurrentWorkingDirectoryToSearchPath();

    bool addInputFileDirectoryToSearchPath() const;
    bool isAddInputFileDirectoryToSearchPathDefaulted() const;
    bool setAddInputFileDirectoryToSearchPath(bool addInputFileDirectoryToSearchPath);
    void resetAddInputFileDirectoryToSearchPath();

    bool addEpinEnvironmentVariableToSearchPath() const;
    bool isAddEpinEnvironmentVariableToSearchPathDefaulted() const;
    bool setAddEpinEnvironmentVariableToSearchPath(bool addEpinEnvironmentVariableToSearchPath);
    void resetAddEpinEnvironmentVariableToSearchPath();

   protected:
    using ImplType = detail::PythonPluginSearchPaths_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::PythonPluginSearchPaths_Impl;

    explicit PythonPluginSearchPaths(std::shared_ptr<detail::PythonPluginSearchPaths_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
