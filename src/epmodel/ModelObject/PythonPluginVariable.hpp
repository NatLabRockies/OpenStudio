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

  /** \brief PythonPluginVariable.
   *
   * \par EnergyPlus object
   * \epobject{group-python-plugins.html#pythonpluginvariables,PythonPlugin:Variables}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PythonPluginVariable</code>. The object has only its inherited name field; EPModel exposes source trend/output-variable queries. Model-side relationship mutation is not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
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
