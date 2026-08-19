/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMINTERNALVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMINTERNALVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemInternalVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:InternalVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsysteminternalvariable,EnergyManagementSystem:InternalVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemInternalVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemInternalVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemInternalVariable(const Model& model, const std::string& internalDataType);

    virtual ~EnergyManagementSystemInternalVariable() override = default;
    EnergyManagementSystemInternalVariable(const EnergyManagementSystemInternalVariable& other) = default;
    EnergyManagementSystemInternalVariable(EnergyManagementSystemInternalVariable&& other) = default;
    EnergyManagementSystemInternalVariable& operator=(const EnergyManagementSystemInternalVariable&) = default;
    EnergyManagementSystemInternalVariable& operator=(EnergyManagementSystemInternalVariable&&) = default;

    static IddObjectType iddObjectType();
    /** @name Internal Data Index Key Name */
    //@{
    std::string internalDataIndexKeyName() const;
    bool setInternalDataIndexKeyName(const std::string& internalDataIndexKeyName);
    void resetInternalDataIndexKeyName();
    //@}

    /** @name Internal Data Type */
    //@{
    std::string internalDataType() const;
    bool setInternalDataType(const std::string& internalDataType);
    //@}

   protected:
    using ImplType = detail::EnergyManagementSystemInternalVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemInternalVariable(std::shared_ptr<detail::EnergyManagementSystemInternalVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
