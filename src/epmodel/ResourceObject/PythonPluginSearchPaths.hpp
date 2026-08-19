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

  /** \brief Controls the built-in directories added to the Python plugin search path.
   *
   * \par EnergyPlus object
   * \epobject{group-python-plugins.html#subsec:plugin-search-paths,PythonPlugin:SearchPaths}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PythonPluginSearchPaths</code>. The three
   * directory toggles are available with the same meaning, but EPModel uses
   * <code>...ToSearchPath</code> method names while Model uses
   * <code>...toSearchPath</code>. Model's custom search-path list methods
   * (<code>searchPaths()</code>, <code>addSearchPath()</code>, and
   * <code>clearSearchPaths()</code>) are not available.
   *
   * \par Known limitations
   * Only the three EnergyPlus boolean toggles are exposed; custom search-path
   * extensible rows cannot be edited through this wrapper.
   */
  class EPMODEL_API PythonPluginSearchPaths : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~PythonPluginSearchPaths() override = default;
    PythonPluginSearchPaths(const PythonPluginSearchPaths& other) = default;
    PythonPluginSearchPaths(PythonPluginSearchPaths&& other) = default;
    PythonPluginSearchPaths& operator=(const PythonPluginSearchPaths&) = default;
    PythonPluginSearchPaths& operator=(PythonPluginSearchPaths&&) = default;

    static IddObjectType iddObjectType();


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

   protected:
    explicit PythonPluginSearchPaths(const Model& model);

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
