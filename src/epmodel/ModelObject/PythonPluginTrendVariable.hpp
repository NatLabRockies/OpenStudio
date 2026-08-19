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

  /** \brief PythonPluginTrendVariable.
   *
   * \par EnergyPlus object
   * \epobject{group-python-plugins.html#pythonplugintrendvariable,PythonPlugin:TrendVariable}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PythonPluginTrendVariable</code>. The number-of-timesteps field is exposed. The Python-plugin-variable relationship is not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
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
