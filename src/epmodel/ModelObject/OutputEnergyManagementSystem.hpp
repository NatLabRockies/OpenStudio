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

  /** \brief OutputEnergyManagementSystem.
   *
   * \par EnergyPlus object
   * \epobject{input-for-output.html#outputenergymanagementsystem,Output:EnergyManagementSystem}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::OutputEnergyManagementSystem</code>. The three reporting settings map directly to EnergyPlus. No additional EMS relationship API is exposed.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API OutputEnergyManagementSystem : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~OutputEnergyManagementSystem() override = default;
    OutputEnergyManagementSystem(const OutputEnergyManagementSystem& other) = default;
    OutputEnergyManagementSystem(OutputEnergyManagementSystem&& other) = default;
    OutputEnergyManagementSystem& operator=(const OutputEnergyManagementSystem&) = default;
    OutputEnergyManagementSystem& operator=(OutputEnergyManagementSystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> actuatorAvailabilityDictionaryReportingValues();
    static std::vector<std::string> internalVariableAvailabilityDictionaryReportingValues();
    static std::vector<std::string> eMSRuntimeLanguageDebugOutputLevelValues();
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
    explicit OutputEnergyManagementSystem(const Model& model);

    using ImplType = detail::OutputEnergyManagementSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputEnergyManagementSystem(std::shared_ptr<detail::OutputEnergyManagementSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
