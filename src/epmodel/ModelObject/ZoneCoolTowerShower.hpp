/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONECOOLTOWER_SHOWER_HPP
#define EPMODEL_ZONECOOLTOWER_SHOWER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneCoolTowerShower_Impl;
  }

  class EPMODEL_API ZoneCoolTowerShower : public ModelObject
  {
   public:
    explicit ZoneCoolTowerShower(const Model& model);

    virtual ~ZoneCoolTowerShower() override = default;
    ZoneCoolTowerShower(const ZoneCoolTowerShower& other) = default;
    ZoneCoolTowerShower(ZoneCoolTowerShower&& other) = default;
    ZoneCoolTowerShower& operator=(const ZoneCoolTowerShower&) = default;
    ZoneCoolTowerShower& operator=(ZoneCoolTowerShower&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> flowControlTypeValues();

    // Schema Alignment Notes:
    // - API: IDD-derived scalar naming is preserved because there is no openstudio::model counterpart.
    // - Field Mapping: Flow Control Type, Maximum Water Flow Rate, Effective Tower Height, Airflow Outlet Area,
    //   Maximum Air Flow Rate, Minimum Indoor Temperature, Fraction of Water Loss, Fraction of Flow Schedule, and
    //   Rated Power Consumption map directly to the ZoneCoolTower:Shower IDD fields.
    // - Field Mapping: Availability Schedule Name, Zone or Space Name, Water Supply Storage Tank Name, and
    //   Pump Flow Rate Schedule Name remain object-list relationships and are intentionally excluded.
    // - TODO(parity): Add relationship helpers once downstream needs emerge.
    std::string flowControlType() const;
    bool setFlowControlType(const std::string& flowControlType);
    bool isFlowControlTypeDefaulted() const;
    void resetFlowControlType();

    double maximumWaterFlowRate() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);

    double effectiveTowerHeight() const;
    bool setEffectiveTowerHeight(double effectiveTowerHeight);

    double airflowOutletArea() const;
    bool setAirflowOutletArea(double airflowOutletArea);

    double maximumAirFlowRate() const;
    bool setMaximumAirFlowRate(double maximumAirFlowRate);

    double minimumIndoorTemperature() const;
    bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

    boost::optional<double> fractionofWaterLoss() const;
    bool setFractionofWaterLoss(double fractionofWaterLoss);
    bool isFractionofWaterLossDefaulted() const;
    void resetFractionofWaterLoss();

    boost::optional<double> fractionofFlowSchedule() const;
    bool setFractionofFlowSchedule(double fractionofFlowSchedule);
    bool isFractionofFlowScheduleDefaulted() const;
    void resetFractionofFlowSchedule();

    double ratedPowerConsumption() const;
    bool setRatedPowerConsumption(double ratedPowerConsumption);

   protected:
    using ImplType = detail::ZoneCoolTowerShower_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneCoolTowerShower(std::shared_ptr<detail::ZoneCoolTowerShower_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
