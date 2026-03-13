/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONAIRCHILLER_HPP
#define EPMODEL_REFRIGERATIONAIRCHILLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationAirChiller_Impl;
  }

  class EPMODEL_API RefrigerationAirChiller : public ModelObject
  {
   public:
    explicit RefrigerationAirChiller(const Model& model);

    virtual ~RefrigerationAirChiller() override = default;
    RefrigerationAirChiller(const RefrigerationAirChiller& other) = default;
    RefrigerationAirChiller(RefrigerationAirChiller&& other) = default;
    RefrigerationAirChiller& operator=(const RefrigerationAirChiller&) = default;
    RefrigerationAirChiller& operator=(RefrigerationAirChiller&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> capacityRatingTypeValues();
    static std::vector<std::string> capacityCorrectionCurveTypeValues();
    static std::vector<std::string> fanSpeedControlTypeValues();
    static std::vector<std::string> defrostTypeValues();
    static std::vector<std::string> defrostControlTypeValues();
    static std::vector<std::string> verticalLocationValues();

    // Schema Alignment Notes:
    // - API: Scalar accessors mirror the openstudio::model RefrigerationAirChiller names while mapping directly to the
    //   EnergyPlus `Refrigeration:AirChiller` fields enumerated by Refrigeration_AirChillerFields (see
    //   ForwardTranslateRefrigerationAirChiller.cpp for the translator evidence).
    // - Field Mapping: availability/heating/defrost schedules plus other relationship-only fields remain outside this
    //   scalar-focused API until dedicated helpers exist.

    std::string capacityRatingType() const;
    bool setCapacityRatingType(const std::string& capacityRatingType);

    boost::optional<double> ratedUnitLoadFactor() const;
    bool setRatedUnitLoadFactor(double ratedUnitLoadFactor);
    void resetRatedUnitLoadFactor();

    boost::optional<double> ratedCapacity() const;
    bool setRatedCapacity(double ratedCapacity);
    void resetRatedCapacity();

    double ratedRelativeHumidity() const;
    bool isRatedRelativeHumidityDefaulted() const;
    bool setRatedRelativeHumidity(double ratedRelativeHumidity);
    void resetRatedRelativeHumidity();

    double ratedCoolingSourceTemperature() const;
    bool setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature);

    double ratedTemperatureDifferenceDT1() const;
    bool setRatedTemperatureDifferenceDT1(double ratedTemperatureDifferenceDT1);

    boost::optional<double> maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature() const;
    bool setMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature(
      double maximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature);
    void resetMaximumTemperatureDifferenceBetweenInletAirandEvaporatingTemperature();

    double coilMaterialCorrectionFactor() const;
    bool isCoilMaterialCorrectionFactorDefaulted() const;
    bool setCoilMaterialCorrectionFactor(double coilMaterialCorrectionFactor);
    void resetCoilMaterialCorrectionFactor();

    double refrigerantCorrectionFactor() const;
    bool isRefrigerantCorrectionFactorDefaulted() const;
    bool setRefrigerantCorrectionFactor(double refrigerantCorrectionFactor);
    void resetRefrigerantCorrectionFactor();

    std::string capacityCorrectionCurveType() const;
    bool isCapacityCorrectionCurveTypeDefaulted() const;
    bool setCapacityCorrectionCurveType(const std::string& capacityCorrectionCurveType);
    void resetCapacityCorrectionCurveType();

    double sHR60CorrectionFactor() const;
    bool isSHR60CorrectionFactorDefaulted() const;
    bool setSHR60CorrectionFactor(double sHR60CorrectionFactor);
    void resetSHR60CorrectionFactor();

    double ratedTotalHeatingPower() const;
    bool setRatedTotalHeatingPower(double ratedTotalHeatingPower);

    std::string fanSpeedControlType() const;
    bool isFanSpeedControlTypeDefaulted() const;
    bool setFanSpeedControlType(const std::string& fanSpeedControlType);
    void resetFanSpeedControlType();

    double ratedFanPower() const;
    bool isRatedFanPowerDefaulted() const;
    bool setRatedFanPower(double ratedFanPower);
    void resetRatedFanPower();

    double ratedAirFlow() const;
    bool setRatedAirFlow(double ratedAirFlow);

    double minimumFanAirFlowRatio() const;
    bool isMinimumFanAirFlowRatioDefaulted() const;
    bool setMinimumFanAirFlowRatio(double minimumFanAirFlowRatio);
    void resetMinimumFanAirFlowRatio();

    std::string defrostType() const;
    bool isDefrostTypeDefaulted() const;
    bool setDefrostType(const std::string& defrostType);
    void resetDefrostType();

    std::string defrostControlType() const;
    bool isDefrostControlTypeDefaulted() const;
    bool setDefrostControlType(const std::string& defrostControlType);
    void resetDefrostControlType();

    boost::optional<double> defrostPower() const;
    bool setDefrostPower(double defrostPower);
    void resetDefrostPower();

    boost::optional<double> temperatureTerminationDefrostFractiontoIce() const;
    bool setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce);
    void resetTemperatureTerminationDefrostFractiontoIce();

    std::string verticalLocation() const;
    bool isVerticalLocationDefaulted() const;
    bool setVerticalLocation(const std::string& verticalLocation);
    void resetVerticalLocation();

    double averageRefrigerantChargeInventory() const;
    bool isAverageRefrigerantChargeInventoryDefaulted() const;
    bool setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory);
    void resetAverageRefrigerantChargeInventory();

   protected:
    using ImplType = detail::RefrigerationAirChiller_Impl;

    explicit RefrigerationAirChiller(std::shared_ptr<detail::RefrigerationAirChiller_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
