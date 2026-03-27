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
    // - Status: Scalar Parity. The scalar field surface is aligned, while schedule/coils/node wiring remains relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardConvectiveWater.
    // - Implemented Parity: `heatingDesignCapacityMethod`, heating-capacity scalars, `uFactorTimesAreaValue`, `maximumWaterFlowRate`, and `convergenceTolerance` map directly to the EnergyPlus ZoneHVAC:Baseboard:Convective:Water fields.
    // - Documented Delta: Availability schedule, heating coil, and inlet/outlet node references are excluded because they are relationship-style links rather than scalar values.
    // - Field/Storage Mapping: The scalar field group is stored directly on the EnergyPlus object, while the omitted links are handled through topology/child-object APIs elsewhere in epmodel.
    // - Evidence: `src/model/ZoneHVACBaseboardConvectiveWater.hpp`, `src/model/ZoneHVACBaseboardConvectiveWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardConvectiveWater.cpp`, and `src/epmodel/test/ZoneHVACBaseboardConvectiveWater_GTest.cpp`.
    // - Remaining Parity Work: Add explicit relationship helpers only if the canonical model surface expands beyond the current scalar wrapper.
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
