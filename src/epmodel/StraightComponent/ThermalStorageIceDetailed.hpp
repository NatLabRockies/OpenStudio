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
  class Node;
  class Schedule;
  class Curve;

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
    // - Status: Near Parity. The canonical availability-schedule, curve, scalar, and plant-demand-side node surface is present for the bounded slice.
    // - Canonical Counterpart: openstudio::model::ThermalStorageIceDetailed.
    // - Implemented Parity: `availabilitySchedule`, `dischargingCurve`, `chargingCurve`, the preserved scalar API, and plant-demand-side `addToNode(...)`
    //   match the canonical wrapper surface and default behavior for this campaign slice.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `ThermalStorage:Ice:Detailed` scalar fields used by the forward translator.
    // - Evidence: `src/model/ThermalStorageIceDetailed.hpp`, `src/model/ThermalStorageIceDetailed.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateThermalStorageIceDetailed.cpp`.
    // - Remaining Parity Work: Broader epmodel topology work remains outside this entity slice.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    Curve dischargingCurve() const;
    bool setDischargingCurve(const Curve& dischargingCurve);

    Curve chargingCurve() const;
    bool setChargingCurve(const Curve& chargingCurve);

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

    bool addToNode(Node& node);

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
