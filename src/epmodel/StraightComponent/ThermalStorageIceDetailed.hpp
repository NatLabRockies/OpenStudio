/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEICEDETAILED_HPP
#define EPMODEL_THERMALSTORAGEICEDETAILED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ThermalStorageIceDetailed_Impl;
  }

  class EPMODEL_API ThermalStorageIceDetailed : public StraightComponent
  {
   public:
    explicit ThermalStorageIceDetailed(const Model& model);

    virtual ~ThermalStorageIceDetailed() override = default;
    ThermalStorageIceDetailed(const ThermalStorageIceDetailed& other) = default;
    ThermalStorageIceDetailed(ThermalStorageIceDetailed&& other) = default;
    ThermalStorageIceDetailed& operator=(const ThermalStorageIceDetailed&) = default;
    ThermalStorageIceDetailed& operator=(ThermalStorageIceDetailed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> dischargingCurveVariableSpecificationsValues();
    static std::vector<std::string> chargingCurveVariableSpecificationsValues();
    static std::vector<std::string> thawProcessIndicatorValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for the numeric and choice fields listed here so the
    //   epmodel type stays aligned with the model-counterpart thermal storage coverage.
    // - Field Mapping: capacity, curve variable specifications, curve timestep, parasitic loads, tank loss, freezing temperature,
    //   and thaw indicator map directly to the EnergyPlus ThermalStorage:Ice:Detailed real/choice fields tracked by
    //   translateThermalStorageIceDetailed.
    // - Field Mapping: Relationship-like fields (schedules, curves, node links) are intentionally excluded from this scalar-only
    //   scaffold; node wiring is handled by StraightComponent inlet/outlet ports.
    // - TODO(parity): Add curve/schedule wiring helpers once the relationship pass supplies those APIs.

    double capacity() const;
    bool setCapacity(double capacity);
    bool isCapacityAutosized() const;
    void autosizeCapacity();

    std::string dischargingCurveVariableSpecifications() const;
    bool setDischargingCurveVariableSpecifications(const std::string& dischargingCurveVariableSpecifications);

    std::string chargingCurveVariableSpecifications() const;
    bool setChargingCurveVariableSpecifications(const std::string& chargingCurveVariableSpecifications);

    boost::optional<double> timestepoftheCurveData() const;
    bool setTimestepoftheCurveData(double timestepoftheCurveData);
    void resetTimestepoftheCurveData();

    boost::optional<double> parasiticElectricLoadDuringDischarging() const;
    bool setParasiticElectricLoadDuringDischarging(double parasiticElectricLoadDuringDischarging);
    void resetParasiticElectricLoadDuringDischarging();

    boost::optional<double> parasiticElectricLoadDuringCharging() const;
    bool setParasiticElectricLoadDuringCharging(double parasiticElectricLoadDuringCharging);
    void resetParasiticElectricLoadDuringCharging();

    boost::optional<double> tankLossCoefficient() const;
    bool setTankLossCoefficient(double tankLossCoefficient);
    void resetTankLossCoefficient();

    double freezingTemperatureofStorageMedium() const;
    bool setFreezingTemperatureofStorageMedium(double freezingTemperatureofStorageMedium);
    bool isFreezingTemperatureofStorageMediumDefaulted() const;
    void resetFreezingTemperatureofStorageMedium();

    std::string thawProcessIndicator() const;
    bool setThawProcessIndicator(const std::string& thawProcessIndicator);
    bool isThawProcessIndicatorDefaulted() const;
    void resetThawProcessIndicator();

   protected:
    using ImplType = detail::ThermalStorageIceDetailed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ThermalStorageIceDetailed(std::shared_ptr<detail::ThermalStorageIceDetailed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_THERMALSTORAGEICEDETAILED_HPP
