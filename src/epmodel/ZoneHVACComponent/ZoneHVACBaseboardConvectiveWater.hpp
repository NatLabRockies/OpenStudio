/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACBaseboardConvectiveWater_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardConvectiveWater : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACBaseboardConvectiveWater(const Model& model);

    virtual ~ZoneHVACBaseboardConvectiveWater() override = default;
    ZoneHVACBaseboardConvectiveWater(const ZoneHVACBaseboardConvectiveWater& other) = default;
    ZoneHVACBaseboardConvectiveWater(ZoneHVACBaseboardConvectiveWater&& other) = default;
    ZoneHVACBaseboardConvectiveWater& operator=(const ZoneHVACBaseboardConvectiveWater&) = default;
    ZoneHVACBaseboardConvectiveWater& operator=(ZoneHVACBaseboardConvectiveWater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: heatingDesignCapacity* / heatingDesignCapacityPerFloorArea / fractionofAutosizedHeatingDesignCapacity / uFactorTimesAreaValue / maximumWaterFlowRate / convergenceTolerance
    //   map to the EnergyPlus ZoneHVAC:Baseboard:Convective:Water fields documented in ForwardTranslateZoneHVACBaseboardConvectiveWater.cpp via ZoneHVAC_Baseboard_Convective_WaterFields.
    // - Availability Schedule Name, Heating Coil Name, and the inlet/outlet node names remain relationship-only connectors handled elsewhere and are excluded from this scalar API.
    static std::vector<std::string> heatingDesignCapacityMethodValues();

    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    bool isHeatingDesignCapacityAutosized() const;
    void autosizeHeatingDesignCapacity();

    double heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

    boost::optional<double> uFactorTimesAreaValue() const;
    bool setUFactorTimesAreaValue(double uFactorTimesAreaValue);
    bool isUFactorTimesAreaValueDefaulted() const;
    bool isUFactorTimesAreaValueAutosized() const;
    void resetUFactorTimesAreaValue();
    void autosizeUFactorTimesAreaValue();

    boost::optional<double> maximumWaterFlowRate() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
    bool isMaximumWaterFlowRateDefaulted() const;
    bool isMaximumWaterFlowRateAutosized() const;
    void resetMaximumWaterFlowRate();
    void autosizeMaximumWaterFlowRate();

    double convergenceTolerance() const;
    bool setConvergenceTolerance(double convergenceTolerance);
    bool isConvergenceToleranceDefaulted() const;
    void resetConvergenceTolerance();

   protected:
    using ImplType = detail::ZoneHVACBaseboardConvectiveWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardConvectiveWater(std::shared_ptr<detail::ZoneHVACBaseboardConvectiveWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
