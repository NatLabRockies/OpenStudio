/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINVARIABLE_HPP
#define EPMODEL_PYTHONPLUGINVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class PythonPluginTrendVariable;
  class PythonPluginOutputVariable;

  namespace detail {
    class PythonPluginVariable_Impl;
  }

  class EPMODEL_API PythonPluginVariable : public ModelObject
  {
   public:
    explicit PythonPluginVariable(const Model& model);

    virtual ~PythonPluginVariable() override = default;
    PythonPluginVariable(const PythonPluginVariable& other) = default;
    PythonPluginVariable(PythonPluginVariable&& other) = default;
    PythonPluginVariable& operator=(const PythonPluginVariable&) = default;
    PythonPluginVariable& operator=(PythonPluginVariable&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Field Mapping: Name is the only simple scalar on OS:PythonPlugin:Variable and is provided by ModelObject::nameString/setName.
    // - Relationship Field: PythonPluginTrendVariable and PythonPluginOutputVariable reference this object via their PythonPluginVariableName fields, so we expose the sources here.
    // - TODO(parity): Extend scalar accessors when the schema adds additional data fields beyond Name.
    std::vector<PythonPluginTrendVariable> pythonPluginTrendVariables() const;
    std::vector<PythonPluginOutputVariable> pythonPluginOutputVariables() const;

   protected:
    using ImplType = detail::PythonPluginVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PythonPluginVariable(std::shared_ptr<detail::PythonPluginVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PYTHONPLUGINVARIABLE_HPP
