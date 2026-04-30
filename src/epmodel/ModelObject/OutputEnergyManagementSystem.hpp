/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTENERGYMANAGEMENTSYSTEM_HPP
#define EPMODEL_OUTPUTENERGYMANAGEMENTSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputEnergyManagementSystem_Impl;
  }

  class EPMODEL_API OutputEnergyManagementSystem : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    explicit OutputEnergyManagementSystem(const Model& model);

    virtual ~OutputEnergyManagementSystem() override = default;
    OutputEnergyManagementSystem(const OutputEnergyManagementSystem& other) = default;
    OutputEnergyManagementSystem(OutputEnergyManagementSystem&& other) = default;
    OutputEnergyManagementSystem& operator=(const OutputEnergyManagementSystem&) = default;
    OutputEnergyManagementSystem& operator=(OutputEnergyManagementSystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> actuatorAvailabilityDictionaryReportingValues();
    static std::vector<std::string> internalVariableAvailabilityDictionaryReportingValues();
    static std::vector<std::string> eMSRuntimeLanguageDebugOutputLevelValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::OutputEnergyManagementSystem accessor names/signatures, including eMSRuntimeLanguageDebugOutputLevel casing.
    // - Field Mapping: actuatorAvailabilityDictionaryReporting/internalVariableAvailabilityDictionaryReporting/eMSRuntimeLanguageDebugOutputLevel map directly to E+ Output:EnergyManagementSystem fields.
    // - ForwardTranslator evidence: ForwardTranslateOutputEnergyManagementSystem.cpp writes these same three fields from the preserved model APIs.
    // - TODO(parity): Keep scalar API stable while extending any non-scalar/translator-parity behavior in future passes.
    std::string actuatorAvailabilityDictionaryReporting() const;
    bool isActuatorAvailabilityDictionaryReportingDefaulted() const;
    bool setActuatorAvailabilityDictionaryReporting(const std::string& actuatorAvailabilityDictionaryReporting);
    void resetActuatorAvailabilityDictionaryReporting();

    std::string internalVariableAvailabilityDictionaryReporting() const;
    bool isInternalVariableAvailabilityDictionaryReportingDefaulted() const;
    bool setInternalVariableAvailabilityDictionaryReporting(const std::string& internalVariableAvailabilityDictionaryReporting);
    void resetInternalVariableAvailabilityDictionaryReporting();

    std::string eMSRuntimeLanguageDebugOutputLevel() const;
    bool isEMSRuntimeLanguageDebugOutputLevelDefaulted() const;
    bool setEMSRuntimeLanguageDebugOutputLevel(const std::string& eMSRuntimeLanguageDebugOutputLevel);
    void resetEMSRuntimeLanguageDebugOutputLevel();

   protected:
    using ImplType = detail::OutputEnergyManagementSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputEnergyManagementSystem(std::shared_ptr<detail::OutputEnergyManagementSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
