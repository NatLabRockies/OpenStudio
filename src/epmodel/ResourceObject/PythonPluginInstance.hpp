/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGININSTANCE_HPP
#define EPMODEL_PYTHONPLUGININSTANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PythonPluginInstance_Impl;
  }

  /** \brief Identifies a Python plugin class and module for EnergyPlus.
   *
   * \par EnergyPlus object
   * \epobject{group-python-plugins.html#pythonplugininstance,PythonPlugin:Instance}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::PythonPluginInstance</code>. EPModel stores the
   * Python module name directly with <code>pythonModuleName()</code> and
   * <code>setPythonModuleName()</code>; the Model API instead exposes the
   * <code>externalFile()</code> relationship and file-inspection helpers
   * (<code>findPluginClassNameInFile()</code> and
   * <code>validPluginClassNamesInFile()</code>).
   *
   * \par Known limitations
   * EPModel does not inspect an external Python file or validate that the
   * module contains the named plugin class.
   */
  class EPMODEL_API PythonPluginInstance : public ModelObject
  {
   public:
    explicit PythonPluginInstance(const Model& model);

    virtual ~PythonPluginInstance() override = default;
    PythonPluginInstance(const PythonPluginInstance& other) = default;
    PythonPluginInstance(PythonPluginInstance&& other) = default;
    PythonPluginInstance& operator=(const PythonPluginInstance&) = default;
    PythonPluginInstance& operator=(PythonPluginInstance&&) = default;

    static IddObjectType iddObjectType();


    bool runDuringWarmupDays() const;
    bool setRunDuringWarmupDays(bool runDuringWarmupDays);
    bool isRunDuringWarmupDaysDefaulted() const;
    void resetRunDuringWarmupDays();

    std::string pythonModuleName() const;
    bool setPythonModuleName(const std::string& pythonModuleName);

    std::string pluginClassName() const;
    bool setPluginClassName(const std::string& pluginClassName);

   protected:
    using ImplType = detail::PythonPluginInstance_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::PythonPluginInstance_Impl;

    explicit PythonPluginInstance(std::shared_ptr<detail::PythonPluginInstance_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
