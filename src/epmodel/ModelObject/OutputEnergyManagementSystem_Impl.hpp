/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTENERGYMANAGEMENTSYSTEM_IMPL_HPP
#define EPMODEL_OUTPUTENERGYMANAGEMENTSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputEnergyManagementSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputEnergyManagementSystem_Impl() override = default;

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

      std::vector<std::string> actuatorAvailabilityDictionaryReportingValues() const;
      std::vector<std::string> internalVariableAvailabilityDictionaryReportingValues() const;
      std::vector<std::string> eMSRuntimeLanguageDebugOutputLevelValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
