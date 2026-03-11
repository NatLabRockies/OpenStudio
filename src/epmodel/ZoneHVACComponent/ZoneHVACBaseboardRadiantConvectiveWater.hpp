/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACBaseboardRadiantConvectiveWater_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveWater : public ModelObject
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveWater(const Model& model);

    virtual ~ZoneHVACBaseboardRadiantConvectiveWater() override = default;
    ZoneHVACBaseboardRadiantConvectiveWater(const ZoneHVACBaseboardRadiantConvectiveWater& other) = default;
    ZoneHVACBaseboardRadiantConvectiveWater(ZoneHVACBaseboardRadiantConvectiveWater&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveWater& operator=(const ZoneHVACBaseboardRadiantConvectiveWater&) = default;
    ZoneHVACBaseboardRadiantConvectiveWater& operator=(ZoneHVACBaseboardRadiantConvectiveWater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: ratedAverageWaterTemperature, ratedWaterMassFlowRate, heatingDesignCapacity, and maximumWaterFlowRate map to the EnergyPlus
    //   ZoneHVAC:Baseboard:RadiantConvective:Water fields enumerated by ZoneHVAC_Baseboard_RadiantConvective_WaterFields via
    //   ForwardTranslateZoneHVACBaseboardRadiantConvectiveWater.cpp.
    // - Availability Schedule Name, Heating Coil Name, and the extensible surface entries remain relationship-only and are intentionally
    //   excluded from this scalar-only API.
    boost::optional<double> ratedAverageWaterTemperature() const;
    bool isRatedAverageWaterTemperatureDefaulted() const;
    bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);
    void resetRatedAverageWaterTemperature();

    boost::optional<double> ratedWaterMassFlowRate() const;
    bool isRatedWaterMassFlowRateDefaulted() const;
    bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
    void resetRatedWaterMassFlowRate();

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    boost::optional<double> maximumWaterFlowRate() const;
    bool isMaximumWaterFlowRateAutosized() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
    void autosizeMaximumWaterFlowRate();

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveWater(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
