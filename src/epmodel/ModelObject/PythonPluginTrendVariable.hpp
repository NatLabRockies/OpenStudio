/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINTRENDVARIABLE_HPP
#define EPMODEL_PYTHONPLUGINTRENDVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PythonPluginTrendVariable_Impl;
  }

  class EPMODEL_API PythonPluginTrendVariable : public ModelObject
  {
   public:
    explicit PythonPluginTrendVariable(const Model& model);

    virtual ~PythonPluginTrendVariable() override = default;
    PythonPluginTrendVariable(const PythonPluginTrendVariable& other) = default;
    PythonPluginTrendVariable(PythonPluginTrendVariable&& other) = default;
    PythonPluginTrendVariable& operator=(const PythonPluginTrendVariable&) = default;
    PythonPluginTrendVariable& operator=(PythonPluginTrendVariable&&) = default;

    static IddObjectType iddObjectType();

    /** Field accessors for Number of Timesteps to be Logged. */
    //@{
    // Schema Alignment Notes:
    // - API: Expose only the simple scalar Number of Timesteps to be Logged accessor while the PythonPluginVariable relationship field remains pending.
    // - Field Mapping: Number of Timesteps to be Logged maps directly to OS_PythonPlugin_TrendVariableFields::NumberofTimestepstobeLogged.
    // - Field Mapping: Name of a Python Plugin Variable is a reference to PythonPluginVariable and is intentionally excluded from this scalar-only run.
    // - TODO(parity): Reintroduce pythonPluginVariable getter/setter once PythonPluginVariable has been scaffolded in epmodel.
    int numberofTimestepstobeLogged() const;
    bool setNumberofTimestepstobeLogged(int numberofTimestepstobeLogged);
    //@}

   protected:
    using ImplType = detail::PythonPluginTrendVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PythonPluginTrendVariable(std::shared_ptr<detail::PythonPluginTrendVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
