/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTCHILLEDWATERLOOP_HPP
#define EPMODEL_HVACTEMPLATEPLANTCHILLEDWATERLOOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantChilledWaterLoop_Impl;
  }

  class EPMODEL_API HVACTemplatePlantChilledWaterLoop : public ModelObject
  {
   public:
    explicit HVACTemplatePlantChilledWaterLoop(const Model& model);

    virtual ~HVACTemplatePlantChilledWaterLoop() override = default;
    HVACTemplatePlantChilledWaterLoop(const HVACTemplatePlantChilledWaterLoop& other) = default;
    HVACTemplatePlantChilledWaterLoop(HVACTemplatePlantChilledWaterLoop&& other) = default;
    HVACTemplatePlantChilledWaterLoop& operator=(const HVACTemplatePlantChilledWaterLoop&) = default;
    HVACTemplatePlantChilledWaterLoop& operator=(HVACTemplatePlantChilledWaterLoop&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> chillerPlantOperationSchemeTypeValues();
    static std::vector<std::string> chilledWaterPumpConfigurationValues();
    static std::vector<std::string> condenserPlantOperationSchemeTypeValues();
    static std::vector<std::string> condenserWaterTemperatureControlTypeValues();
    static std::vector<std::string> chilledWaterSetpointResetTypeValues();
    static std::vector<std::string> chilledWaterPrimaryPumpTypeValues();
    static std::vector<std::string> chilledWaterSecondaryPumpTypeValues();
    static std::vector<std::string> condenserWaterPumpTypeValues();
    static std::vector<std::string> fluidTypeValues();
    static std::vector<std::string> chilledWaterLoadDistributionSchemeValues();
    static std::vector<std::string> condenserWaterLoadDistributionSchemeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:ChilledWaterLoop non-name, non-link scalar fields.
    // - Field Mapping: Pump/schedule/scheme name object-list fields are relationship-like and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.
    std::string pumpControlType() const;
    bool isPumpControlTypeDefaulted() const;
    bool setPumpControlType(const std::string& pumpControlType);
    void resetPumpControlType();

    std::string chillerPlantOperationSchemeType() const;
    bool isChillerPlantOperationSchemeTypeDefaulted() const;
    bool setChillerPlantOperationSchemeType(const std::string& chillerPlantOperationSchemeType);
    void resetChillerPlantOperationSchemeType();

    double chilledWaterDesignSetpoint() const;
    bool isChilledWaterDesignSetpointDefaulted() const;
    bool setChilledWaterDesignSetpoint(double chilledWaterDesignSetpoint);
    void resetChilledWaterDesignSetpoint();

    std::string chilledWaterPumpConfiguration() const;
    bool isChilledWaterPumpConfigurationDefaulted() const;
    bool setChilledWaterPumpConfiguration(const std::string& chilledWaterPumpConfiguration);
    void resetChilledWaterPumpConfiguration();

    double primaryChilledWaterPumpRatedHead() const;
    bool isPrimaryChilledWaterPumpRatedHeadDefaulted() const;
    bool setPrimaryChilledWaterPumpRatedHead(double primaryChilledWaterPumpRatedHead);
    void resetPrimaryChilledWaterPumpRatedHead();

    double secondaryChilledWaterPumpRatedHead() const;
    bool isSecondaryChilledWaterPumpRatedHeadDefaulted() const;
    bool setSecondaryChilledWaterPumpRatedHead(double secondaryChilledWaterPumpRatedHead);
    void resetSecondaryChilledWaterPumpRatedHead();

    std::string condenserPlantOperationSchemeType() const;
    bool isCondenserPlantOperationSchemeTypeDefaulted() const;
    bool setCondenserPlantOperationSchemeType(const std::string& condenserPlantOperationSchemeType);
    void resetCondenserPlantOperationSchemeType();

    boost::optional<std::string> condenserWaterTemperatureControlType() const;
    bool setCondenserWaterTemperatureControlType(const std::string& condenserWaterTemperatureControlType);
    void resetCondenserWaterTemperatureControlType();

    double condenserWaterDesignSetpoint() const;
    bool isCondenserWaterDesignSetpointDefaulted() const;
    bool setCondenserWaterDesignSetpoint(double condenserWaterDesignSetpoint);
    void resetCondenserWaterDesignSetpoint();

    double condenserWaterPumpRatedHead() const;
    bool isCondenserWaterPumpRatedHeadDefaulted() const;
    bool setCondenserWaterPumpRatedHead(double condenserWaterPumpRatedHead);
    void resetCondenserWaterPumpRatedHead();

    std::string chilledWaterSetpointResetType() const;
    bool isChilledWaterSetpointResetTypeDefaulted() const;
    bool setChilledWaterSetpointResetType(const std::string& chilledWaterSetpointResetType);
    void resetChilledWaterSetpointResetType();

    double chilledWaterSetpointatOutdoorDryBulbLow() const;
    bool isChilledWaterSetpointatOutdoorDryBulbLowDefaulted() const;
    bool setChilledWaterSetpointatOutdoorDryBulbLow(double chilledWaterSetpointatOutdoorDryBulbLow);
    void resetChilledWaterSetpointatOutdoorDryBulbLow();

    double chilledWaterResetOutdoorDryBulbLow() const;
    bool isChilledWaterResetOutdoorDryBulbLowDefaulted() const;
    bool setChilledWaterResetOutdoorDryBulbLow(double chilledWaterResetOutdoorDryBulbLow);
    void resetChilledWaterResetOutdoorDryBulbLow();

    double chilledWaterSetpointatOutdoorDryBulbHigh() const;
    bool isChilledWaterSetpointatOutdoorDryBulbHighDefaulted() const;
    bool setChilledWaterSetpointatOutdoorDryBulbHigh(double chilledWaterSetpointatOutdoorDryBulbHigh);
    void resetChilledWaterSetpointatOutdoorDryBulbHigh();

    double chilledWaterResetOutdoorDryBulbHigh() const;
    bool isChilledWaterResetOutdoorDryBulbHighDefaulted() const;
    bool setChilledWaterResetOutdoorDryBulbHigh(double chilledWaterResetOutdoorDryBulbHigh);
    void resetChilledWaterResetOutdoorDryBulbHigh();

    std::string chilledWaterPrimaryPumpType() const;
    bool isChilledWaterPrimaryPumpTypeDefaulted() const;
    bool setChilledWaterPrimaryPumpType(const std::string& chilledWaterPrimaryPumpType);
    void resetChilledWaterPrimaryPumpType();

    std::string chilledWaterSecondaryPumpType() const;
    bool isChilledWaterSecondaryPumpTypeDefaulted() const;
    bool setChilledWaterSecondaryPumpType(const std::string& chilledWaterSecondaryPumpType);
    void resetChilledWaterSecondaryPumpType();

    std::string condenserWaterPumpType() const;
    bool isCondenserWaterPumpTypeDefaulted() const;
    bool setCondenserWaterPumpType(const std::string& condenserWaterPumpType);
    void resetCondenserWaterPumpType();

    bool chilledWaterSupplySideBypassPipe() const;
    bool isChilledWaterSupplySideBypassPipeDefaulted() const;
    bool setChilledWaterSupplySideBypassPipe(bool chilledWaterSupplySideBypassPipe);
    void resetChilledWaterSupplySideBypassPipe();

    bool chilledWaterDemandSideBypassPipe() const;
    bool isChilledWaterDemandSideBypassPipeDefaulted() const;
    bool setChilledWaterDemandSideBypassPipe(bool chilledWaterDemandSideBypassPipe);
    void resetChilledWaterDemandSideBypassPipe();

    bool condenserWaterSupplySideBypassPipe() const;
    bool isCondenserWaterSupplySideBypassPipeDefaulted() const;
    bool setCondenserWaterSupplySideBypassPipe(bool condenserWaterSupplySideBypassPipe);
    void resetCondenserWaterSupplySideBypassPipe();

    bool condenserWaterDemandSideBypassPipe() const;
    bool isCondenserWaterDemandSideBypassPipeDefaulted() const;
    bool setCondenserWaterDemandSideBypassPipe(bool condenserWaterDemandSideBypassPipe);
    void resetCondenserWaterDemandSideBypassPipe();

    std::string fluidType() const;
    bool isFluidTypeDefaulted() const;
    bool setFluidType(const std::string& fluidType);
    void resetFluidType();

    double loopDesignDeltaTemperature() const;
    bool isLoopDesignDeltaTemperatureDefaulted() const;
    bool setLoopDesignDeltaTemperature(double loopDesignDeltaTemperature);
    void resetLoopDesignDeltaTemperature();

    boost::optional<double> minimumOutdoorDryBulbTemperature() const;
    bool setMinimumOutdoorDryBulbTemperature(double minimumOutdoorDryBulbTemperature);
    void resetMinimumOutdoorDryBulbTemperature();

    std::string chilledWaterLoadDistributionScheme() const;
    bool isChilledWaterLoadDistributionSchemeDefaulted() const;
    bool setChilledWaterLoadDistributionScheme(const std::string& chilledWaterLoadDistributionScheme);
    void resetChilledWaterLoadDistributionScheme();

    std::string condenserWaterLoadDistributionScheme() const;
    bool isCondenserWaterLoadDistributionSchemeDefaulted() const;
    bool setCondenserWaterLoadDistributionScheme(const std::string& condenserWaterLoadDistributionScheme);
    void resetCondenserWaterLoadDistributionScheme();

   protected:
    using ImplType = detail::HVACTemplatePlantChilledWaterLoop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantChilledWaterLoop(std::shared_ptr<detail::HVACTemplatePlantChilledWaterLoop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
