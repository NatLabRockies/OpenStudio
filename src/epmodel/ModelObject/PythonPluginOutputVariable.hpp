/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PYTHONPLUGINOUTPUTVARIABLE_HPP
#define EPMODEL_PYTHONPLUGINOUTPUTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class PythonPluginOutputVariable_Impl;
  }

  /** \brief PythonPluginOutputVariable.
   *
   * \par EnergyPlus object
   * <code>PythonPlugin:OutputVariable</code>.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PythonPluginOutputVariable</code>. The scalar output-variable settings are exposed. The Python-plugin-variable relationship is not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API PythonPluginOutputVariable : public ModelObject
  {
   public:
    explicit PythonPluginOutputVariable(const Model& model);

    virtual ~PythonPluginOutputVariable() override = default;
    PythonPluginOutputVariable(const PythonPluginOutputVariable& other) = default;
    PythonPluginOutputVariable(PythonPluginOutputVariable&& other) = default;
    PythonPluginOutputVariable& operator=(const PythonPluginOutputVariable&) = default;
    PythonPluginOutputVariable& operator=(PythonPluginOutputVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeofDatainVariableValues();
    static std::vector<std::string> updateFrequencyValues();
    static std::vector<std::string> resourceTypeValues();
    static std::vector<std::string> groupTypeValues();
    static std::vector<std::string> endUseCategoryValues();
    std::string typeofDatainVariable() const;
    bool setTypeofDatainVariable(const std::string& typeofDatainVariable);

    std::string updateFrequency() const;
    bool setUpdateFrequency(const std::string& updateFrequency);

    boost::optional<std::string> units() const;
    bool setUnits(const std::string& units);
    void resetUnits();

    boost::optional<std::string> resourceType() const;
    bool setResourceType(const std::string& resourceType);
    void resetResourceType();

    boost::optional<std::string> groupType() const;
    bool setGroupType(const std::string& groupType);
    void resetGroupType();

    boost::optional<std::string> endUseCategory() const;
    bool setEndUseCategory(const std::string& endUseCategory);
    void resetEndUseCategory();

    boost::optional<std::string> endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::PythonPluginOutputVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PythonPluginOutputVariable(std::shared_ptr<detail::PythonPluginOutputVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_PYTHONPLUGINOUTPUTVARIABLE_HPP
