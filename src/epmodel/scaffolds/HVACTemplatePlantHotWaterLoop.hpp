/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTHOTWATERLOOP_HPP
#define EPMODEL_HVACTEMPLATEPLANTHOTWATERLOOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HVACTemplatePlantHotWaterLoop_Impl;
  }

  class EPMODEL_API HVACTemplatePlantHotWaterLoop : public ModelObject
  {
   public:
    explicit HVACTemplatePlantHotWaterLoop(const Model& model);

    virtual ~HVACTemplatePlantHotWaterLoop() override = default;
    HVACTemplatePlantHotWaterLoop(const HVACTemplatePlantHotWaterLoop& other) = default;
    HVACTemplatePlantHotWaterLoop(HVACTemplatePlantHotWaterLoop&& other) = default;
    HVACTemplatePlantHotWaterLoop& operator=(const HVACTemplatePlantHotWaterLoop&) = default;
    HVACTemplatePlantHotWaterLoop& operator=(HVACTemplatePlantHotWaterLoop&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> pumpControlTypeValues();
    static std::vector<std::string> hotWaterPlantOperationSchemeTypeValues();
    static std::vector<std::string> hotWaterPumpConfigurationValues();
    static std::vector<std::string> hotWaterSetpointResetTypeValues();
    static std::vector<std::string> hotWaterPumpTypeValues();
    static std::vector<std::string> fluidTypeValues();
    static std::vector<std::string> loadDistributionSchemeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HVACTemplate:Plant:HotWaterLoop non-name, non-link scalar fields.
    // - Field Mapping: Pump/schedule/scheme name object-list fields are relationship-like and excluded from scalar accessors.
    // - TODO(parity): Add relationship/object-link APIs in a later parity pass.

    std::string pumpControlType() const;
    bool isPumpControlTypeDefaulted() const;
    bool setPumpControlType(const std::string& pumpControlType);
    void resetPumpControlType();

    std::string hotWaterPlantOperationSchemeType() const;
    bool isHotWaterPlantOperationSchemeTypeDefaulted() const;
    bool setHotWaterPlantOperationSchemeType(const std::string& hotWaterPlantOperationSchemeType);
    void resetHotWaterPlantOperationSchemeType();

    double hotWaterDesignSetpoint() const;
    bool isHotWaterDesignSetpointDefaulted() const;
    bool setHotWaterDesignSetpoint(double hotWaterDesignSetpoint);
    void resetHotWaterDesignSetpoint();

    std::string hotWaterPumpConfiguration() const;
    bool isHotWaterPumpConfigurationDefaulted() const;
    bool setHotWaterPumpConfiguration(const std::string& hotWaterPumpConfiguration);
    void resetHotWaterPumpConfiguration();

    double hotWaterPumpRatedHead() const;
    bool isHotWaterPumpRatedHeadDefaulted() const;
    bool setHotWaterPumpRatedHead(double hotWaterPumpRatedHead);
    void resetHotWaterPumpRatedHead();

    std::string hotWaterSetpointResetType() const;
    bool isHotWaterSetpointResetTypeDefaulted() const;
    bool setHotWaterSetpointResetType(const std::string& hotWaterSetpointResetType);
    void resetHotWaterSetpointResetType();

    double hotWaterSetpointatOutdoorDryBulbLow() const;
    bool isHotWaterSetpointatOutdoorDryBulbLowDefaulted() const;
    bool setHotWaterSetpointatOutdoorDryBulbLow(double hotWaterSetpointatOutdoorDryBulbLow);
    void resetHotWaterSetpointatOutdoorDryBulbLow();

    double hotWaterResetOutdoorDryBulbLow() const;
    bool isHotWaterResetOutdoorDryBulbLowDefaulted() const;
    bool setHotWaterResetOutdoorDryBulbLow(double hotWaterResetOutdoorDryBulbLow);
    void resetHotWaterResetOutdoorDryBulbLow();

    double hotWaterSetpointatOutdoorDryBulbHigh() const;
    bool isHotWaterSetpointatOutdoorDryBulbHighDefaulted() const;
    bool setHotWaterSetpointatOutdoorDryBulbHigh(double hotWaterSetpointatOutdoorDryBulbHigh);
    void resetHotWaterSetpointatOutdoorDryBulbHigh();

    double hotWaterResetOutdoorDryBulbHigh() const;
    bool isHotWaterResetOutdoorDryBulbHighDefaulted() const;
    bool setHotWaterResetOutdoorDryBulbHigh(double hotWaterResetOutdoorDryBulbHigh);
    void resetHotWaterResetOutdoorDryBulbHigh();

    std::string hotWaterPumpType() const;
    bool isHotWaterPumpTypeDefaulted() const;
    bool setHotWaterPumpType(const std::string& hotWaterPumpType);
    void resetHotWaterPumpType();

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

    boost::optional<double> maximumOutdoorDryBulbTemperature() const;
    bool setMaximumOutdoorDryBulbTemperature(double maximumOutdoorDryBulbTemperature);
    void resetMaximumOutdoorDryBulbTemperature();

    std::string loadDistributionScheme() const;
    bool isLoadDistributionSchemeDefaulted() const;
    bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
    void resetLoadDistributionScheme();

   protected:
    using ImplType = detail::HVACTemplatePlantHotWaterLoop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HVACTemplatePlantHotWaterLoop(std::shared_ptr<detail::HVACTemplatePlantHotWaterLoop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
