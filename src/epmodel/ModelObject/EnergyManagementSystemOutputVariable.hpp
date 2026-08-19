/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMOUTPUTVARIABLE_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMOUTPUTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class EnergyManagementSystemOutputVariable_Impl;
  }

  /** \brief Represents <code>EnergyManagementSystem:OutputVariable</code>.
   *
   * \par EnergyPlus object
   * \epobject{group-energy-management-system-ems.html#energymanagementsystemoutputvariable,EnergyManagementSystem:OutputVariable}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::EnergyManagementSystemOutputVariable</code>.
   * **Not yet available:** Model typed object-target, program-body, and EMS relationship conveniences are not exposed unless declared by this wrapper.
   *
   * \par Known limitations
   * Typed relationship and extensible-list conveniences not represented by the public declarations are unavailable.
   */
  class EPMODEL_API EnergyManagementSystemOutputVariable : public ModelObject
  {
   public:
    explicit EnergyManagementSystemOutputVariable(const Model& model, const std::string& eMSVariableName);

    virtual ~EnergyManagementSystemOutputVariable() override = default;
    EnergyManagementSystemOutputVariable(const EnergyManagementSystemOutputVariable& other) = default;
    EnergyManagementSystemOutputVariable(EnergyManagementSystemOutputVariable&& other) = default;
    EnergyManagementSystemOutputVariable& operator=(const EnergyManagementSystemOutputVariable&) = default;
    EnergyManagementSystemOutputVariable& operator=(EnergyManagementSystemOutputVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeOfDataInVariableValues();
    static std::vector<std::string> updateFrequencyValues();
    /** EMS Variable Name */
    //@{
    std::string emsVariableName() const;
    bool setEMSVariableName(const std::string& eMSVariableName);
    //@}

    /** Type of Data In Variable */
    //@{
    std::string typeOfDataInVariable() const;
    bool setTypeOfDataInVariable(const std::string& typeofDatainVariable);
    //@}

    /** Update Frequency */
    //@{
    std::string updateFrequency() const;
    bool setUpdateFrequency(const std::string& updateFrequency);
    //@}

    /** Units */
    //@{
    std::string units() const;
    bool setUnits(const std::string& units);
    void resetUnits();
    //@}

   protected:
    using ImplType = detail::EnergyManagementSystemOutputVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit EnergyManagementSystemOutputVariable(std::shared_ptr<detail::EnergyManagementSystemOutputVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
