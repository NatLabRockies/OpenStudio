/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemMeteredOutputVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:MeteredOutputVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemmeteredoutputvariable,EnergyManagementSystem:MeteredOutputVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemMeteredOutputVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemMeteredOutputVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const std::string& eMSVariableName);

    virtual ~EnergyManagementSystemMeteredOutputVariable() override = default;
    EnergyManagementSystemMeteredOutputVariable(const EnergyManagementSystemMeteredOutputVariable& other) = default;
    EnergyManagementSystemMeteredOutputVariable(EnergyManagementSystemMeteredOutputVariable&& other) = default;
    EnergyManagementSystemMeteredOutputVariable& operator=(const EnergyManagementSystemMeteredOutputVariable&) = default;
    EnergyManagementSystemMeteredOutputVariable& operator=(EnergyManagementSystemMeteredOutputVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> updateFrequencyValues();
    static std::vector<std::string> resourceTypeValues();
    static std::vector<std::string> groupTypeValues();
    static std::vector<std::string> endUseCategoryValues();
    std::string emsVariableName() const;
    bool setEMSVariableName(const std::string& eMSVariableName);

    std::string updateFrequency() const;
    bool setUpdateFrequency(const std::string& updateFrequency);

    std::string resourceType() const;
    bool setResourceType(const std::string& resourceType);

    std::string groupType() const;
    bool setGroupType(const std::string& groupType);

    std::string endUseCategory() const;
    bool setEndUseCategory(const std::string& endUseCategory);

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    std::string units() const;
    bool setUnits(const std::string& units);
    void resetUnits();

   protected:
    using ImplType = detail::EnergyManagementSystemMeteredOutputVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemMeteredOutputVariable(std::shared_ptr<detail::EnergyManagementSystemMeteredOutputVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
