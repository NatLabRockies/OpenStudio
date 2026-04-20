/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACVENTILATEDSLAB_HPP
#define EPMODEL_ZONEHVACVENTILATEDSLAB_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACVentilatedSlab_Impl;
  }

  class EPMODEL_API ZoneHVACVentilatedSlab : public ModelObject
  {
   public:
    explicit ZoneHVACVentilatedSlab(const Model& model);

    virtual ~ZoneHVACVentilatedSlab() override = default;
    ZoneHVACVentilatedSlab(const ZoneHVACVentilatedSlab& other) = default;
    ZoneHVACVentilatedSlab(ZoneHVACVentilatedSlab&& other) = default;
    ZoneHVACVentilatedSlab& operator=(const ZoneHVACVentilatedSlab&) = default;
    ZoneHVACVentilatedSlab& operator=(ZoneHVACVentilatedSlab&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type exposes IDD-derived scalars for ZoneHVAC:VentilatedSlab while preserving the epmodel naming in the absence of a forward translator.
    // - Field Mapping: Numeric/choice accessors map directly to ZoneHVAC:VentilatedSlab fields (Maximum/Minimum Air Flow, control types, coil object choices, core geometry).
    // - Field Mapping: Relationship-like node/object-list inputs (schedules, nodes, mixer paths, coil names) are excluded per contract.
    // - TODO(parity): Add relationship/node helpers only if future schema adds simple scalar fields that require them.

    static std::vector<std::string> outdoorAirControlTypeValues();
    static std::vector<std::string> systemConfigurationTypeValues();
    static std::vector<std::string> temperatureControlTypeValues();
    static std::vector<std::string> coilOptionTypeValues();
    static std::vector<std::string> heatingCoilObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();

    // Maximum air flow rate
    boost::optional<double> maximumAirFlowRate() const;
    bool isMaximumAirFlowRateAutosized() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);
    void autosizeMaximumAirFlowRate();

    // Minimum outdoor air flow rate
    boost::optional<double> minimumOutdoorAirFlowRate() const;
    bool isMinimumOutdoorAirFlowRateAutosized() const;
    bool setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate);
    void autosizeMinimumOutdoorAirFlowRate();

    // Maximum outdoor air flow rate
    boost::optional<double> maximumOutdoorAirFlowRate() const;
    bool isMaximumOutdoorAirFlowRateAutosized() const;
    bool setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate);
    void autosizeMaximumOutdoorAirFlowRate();

    // Outdoor air control type
    std::string outdoorAirControlType() const;
    bool setOutdoorAirControlType(const std::string& outdoorAirControlType);

    // System configuration type
    std::string systemConfigurationType() const;
    bool isSystemConfigurationTypeDefaulted() const;
    bool setSystemConfigurationType(const std::string& systemConfigurationType);
    void resetSystemConfigurationType();

    // Hollow core inside diameter
    boost::optional<double> hollowCoreInsideDiameter() const;
    bool isHollowCoreInsideDiameterDefaulted() const;
    bool setHollowCoreInsideDiameter(double hollowCoreInsideDiameter);
    void resetHollowCoreInsideDiameter();

    // Hollow core length
    boost::optional<double> hollowCoreLength() const;
    bool setHollowCoreLength(double hollowCoreLength);
    void resetHollowCoreLength();

    // Temperature control type
    std::string temperatureControlType() const;
    bool isTemperatureControlTypeDefaulted() const;
    bool setTemperatureControlType(const std::string& temperatureControlType);
    void resetTemperatureControlType();

    // Coil option type
    std::string coilOptionType() const;
    bool setCoilOptionType(const std::string& coilOptionType);

    // Heating coil object type
    boost::optional<std::string> heatingCoilObjectType() const;
    bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);
    void resetHeatingCoilObjectType();

    // Cooling coil object type
    boost::optional<std::string> coolingCoilObjectType() const;
    bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);
    void resetCoolingCoilObjectType();

   protected:
    using ImplType = detail::ZoneHVACVentilatedSlab_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACVentilatedSlab(std::shared_ptr<detail::ZoneHVACVentilatedSlab_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
