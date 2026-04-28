/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTMIXEDWATERLOOP_HPP
#define EPMODEL_HVACTEMPLATEPLANTMIXEDWATERLOOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantMixedWaterLoop_Impl;
  }

  class EPMODEL_API HVACTemplatePlantMixedWaterLoop : public ModelObject
  {
   public:
    explicit HVACTemplatePlantMixedWaterLoop(const Model& model);

    virtual ~HVACTemplatePlantMixedWaterLoop() override = default;
    HVACTemplatePlantMixedWaterLoop(const HVACTemplatePlantMixedWaterLoop& other) = default;
    HVACTemplatePlantMixedWaterLoop(HVACTemplatePlantMixedWaterLoop&& other) = default;
    HVACTemplatePlantMixedWaterLoop& operator=(const HVACTemplatePlantMixedWaterLoop&) = default;
    HVACTemplatePlantMixedWaterLoop& operator=(HVACTemplatePlantMixedWaterLoop&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> operationSchemeTypeValues();
    static std::vector<std::string> waterPumpConfigurationValues();
    static std::vector<std::string> waterPumpTypeValues();
    static std::vector<std::string> fluidTypeValues();
    static std::vector<std::string> loadDistributionSchemeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:MixedWaterLoop non-name, non-link scalar fields.
    // - Field Mapping: Pump/schedule/scheme name object-list fields are relationship-like and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.

    std::string pumpControlType() const;
    bool isPumpControlTypeDefaulted() const;
    bool setPumpControlType(const std::string& pumpControlType);
    void resetPumpControlType();

    std::string operationSchemeType() const;
    bool isOperationSchemeTypeDefaulted() const;
    bool setOperationSchemeType(const std::string& operationSchemeType);
    void resetOperationSchemeType();

    double highTemperatureDesignSetpoint() const;
    bool isHighTemperatureDesignSetpointDefaulted() const;
    bool setHighTemperatureDesignSetpoint(double highTemperatureDesignSetpoint);
    void resetHighTemperatureDesignSetpoint();

    double lowTemperatureDesignSetpoint() const;
    bool isLowTemperatureDesignSetpointDefaulted() const;
    bool setLowTemperatureDesignSetpoint(double lowTemperatureDesignSetpoint);
    void resetLowTemperatureDesignSetpoint();

    std::string waterPumpConfiguration() const;
    bool isWaterPumpConfigurationDefaulted() const;
    bool setWaterPumpConfiguration(const std::string& waterPumpConfiguration);
    void resetWaterPumpConfiguration();

    double waterPumpRatedHead() const;
    bool isWaterPumpRatedHeadDefaulted() const;
    bool setWaterPumpRatedHead(double waterPumpRatedHead);
    void resetWaterPumpRatedHead();

    std::string waterPumpType() const;
    bool isWaterPumpTypeDefaulted() const;
    bool setWaterPumpType(const std::string& waterPumpType);
    void resetWaterPumpType();

    bool supplySideBypassPipe() const;
    bool isSupplySideBypassPipeDefaulted() const;
    bool setSupplySideBypassPipe(bool supplySideBypassPipe);
    void resetSupplySideBypassPipe();

    bool demandSideBypassPipe() const;
    bool isDemandSideBypassPipeDefaulted() const;
    bool setDemandSideBypassPipe(bool demandSideBypassPipe);
    void resetDemandSideBypassPipe();

    std::string fluidType() const;
    bool isFluidTypeDefaulted() const;
    bool setFluidType(const std::string& fluidType);
    void resetFluidType();

    double loopDesignDeltaTemperature() const;
    bool isLoopDesignDeltaTemperatureDefaulted() const;
    bool setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature);
    void resetLoopDesignDeltaTemperature();

    std::string loadDistributionScheme() const;
    bool isLoadDistributionSchemeDefaulted() const;
    bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
    void resetLoadDistributionScheme();

   protected:
    using ImplType = detail::HVACTemplatePlantMixedWaterLoop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantMixedWaterLoop(std::shared_ptr<detail::HVACTemplatePlantMixedWaterLoop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
