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

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::EnergyManagementSystemOutputVariable scalar accessor names/signatures.
    // - Field Mapping: emsVariableName/typeOfDataInVariable/updateFrequency/units map directly to E+ EnergyManagementSystem:OutputVariable fields.
    // - Field Mapping: emsProgramOrSubroutineName and object-handle overload APIs are relationship-like and intentionally excluded from scalar scaffold.
    // - ForwardTranslator evidence: ForwardTranslateEnergyManagementSystemOutputVariable.cpp writes these same scalar fields from the preserved APIs.
    // - TODO(parity): Add relationship-aware APIs incrementally without changing these scalar signatures.
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
