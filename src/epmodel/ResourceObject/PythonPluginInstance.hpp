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

  /** PythonPluginInstance is a ModelObject that wraps the EnergyPlus IDD object 'PythonPlugin:Instance'. */
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

    // Schema Alignment Notes:
    // - API: Preserve the openstudio::model counterpart names (runDuringWarmupDays, pluginClassName) and expose the
    //   PythonModuleName IDD field as a scalar-only accessor for direct EnergyPlus parity.
    // - Field Mapping: The EnergyPlus PythonPlugin:Instance fields (Run During Warmup Days, Python Module Name, Plugin Class
    //   Name) map directly to these scalars; Run During Warmup Days keeps Yes/No semantics with is...Defaulted/reset.
    // - ForwardTranslator evidence: ForwardTranslatePythonPluginInstance.cpp drives PythonModuleName from the linked ExternalFile
    //   and propagates the pluginClassName/runDuringWarmupDays values to the translated IDF.
    // - TODO(parity): Reconcile pythonModuleName with the ExternalFile helper once Python plugin resources gain richer APIs.

    bool runDuringWarmupDays() const;
    bool isRunDuringWarmupDaysDefaulted() const;
    bool setRunDuringWarmupDays(bool runDuringWarmupDays);
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
