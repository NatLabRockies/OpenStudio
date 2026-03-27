/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITHEATER_HPP
#define EPMODEL_ZONEHVACUNITHEATER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACUnitHeater_Impl;
  }

  class EPMODEL_API ZoneHVACUnitHeater : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACUnitHeater(const Model& model);

    virtual ~ZoneHVACUnitHeater() override = default;
    ZoneHVACUnitHeater(const ZoneHVACUnitHeater& other) = default;
    ZoneHVACUnitHeater(ZoneHVACUnitHeater&& other) = default;
    ZoneHVACUnitHeater& operator=(const ZoneHVACUnitHeater&) = default;
    ZoneHVACUnitHeater& operator=(ZoneHVACUnitHeater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The core unit-heater scalars are aligned, but the availability/fan/coil/node relationships remain separate.
    // - Canonical Counterpart: openstudio::model::ZoneHVACUnitHeater.
    // - Implemented Parity: `maximumSupplyAirFlowRate`, `fanControlType`, `maximumHotWaterFlowRate`, `minimumHotWaterFlowRate`, and `heatingConvergenceTolerance` map directly to the EnergyPlus object.
    // - Documented Delta: Availability, supply-fan, heating-coil, and node targets are relationship-only and remain outside the scalar surface.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while the omitted links are represented through child-object and topology state.
    // - Evidence: `src/model/ZoneHVACUnitHeater.hpp`, `src/model/ZoneHVACUnitHeater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACUnitHeater.cpp`, and `src/epmodel/test/ZoneHVACUnitHeater_GTest.cpp`.
    // - Remaining Parity Work: Add the missing relationship helpers only if the canonical wrapper still exposes them as public API.

    /** @name Maximum Supply Air Flow Rate */
    //@{
    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();
    boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;
    //@}

    /** @name Fan Control Type */
    //@{
    std::string fanControlType() const;
    bool setFanControlType(const std::string& fanControlType);
    //@}

    /** @name Maximum Hot Water Flow Rate */
    //@{
    boost::optional<double> maximumHotWaterFlowRate() const;
    bool isMaximumHotWaterFlowRateAutosized() const;
    bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
    void resetMaximumHotWaterFlowRate();
    void autosizeMaximumHotWaterFlowRate();
    boost::optional<double> autosizedMaximumHotWaterFlowRate() const;
    //@}

    /** @name Minimum Hot Water Flow Rate */
    //@{
    double minimumHotWaterFlowRate() const;
    bool isMinimumHotWaterFlowRateDefaulted() const;
    bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
    void resetMinimumHotWaterFlowRate();
    //@}

    /** @name Heating Convergence Tolerance */
    //@{
    double heatingConvergenceTolerance() const;
    bool isHeatingConvergenceToleranceDefaulted() const;
    bool setHeatingConvergenceTolerance(double heatingConvergenceTolerance);
    void resetHeatingConvergenceTolerance();
    //@}

   protected:
    using ImplType = detail::ZoneHVACUnitHeater_Impl;

    explicit ZoneHVACUnitHeater(std::shared_ptr<detail::ZoneHVACUnitHeater_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
