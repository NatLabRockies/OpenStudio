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

/** \brief A detailed ice thermal-storage component.
 *
 * \par EnergyPlus object
 * \epobject{group-water-heaters.html#thermalstorageicedetailed,ThermalStorage:Ice:Detailed}
 *
 * \par Important behavior
 * Availability, charging/discharging curves, scalar storage fields, and plant-demand placement map directly to ThermalStorage:Ice:Detailed.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::ThermalStorageIceDetailed</code>.
 *
 * \par Known limitations
 * Broader topology behavior remains outside this wrapper slice.
 */
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
