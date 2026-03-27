/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANZONEEXHAUST_HPP
#define EPMODEL_FANZONEEXHAUST_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FanZoneExhaust_Impl;
  }

  class EPMODEL_API FanZoneExhaust : public ZoneHVACComponent
  {
   public:
    explicit FanZoneExhaust(const Model& model);

    virtual ~FanZoneExhaust() override = default;
    FanZoneExhaust(const FanZoneExhaust& other) = default;
    FanZoneExhaust(FanZoneExhaust&& other) = default;
    FanZoneExhaust& operator=(const FanZoneExhaust&) = default;
    FanZoneExhaust& operator=(FanZoneExhaust&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> systemAvailabilityManagerCouplingModeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The exhaust-fan scalar fields are aligned, and the relationship-bearing schedule/node links stay outside the public surface.
    // - Canonical Counterpart: openstudio::model::FanZoneExhaust.
    // - Implemented Parity: `fanTotalEfficiency`, `fanEfficiency`, `pressureRise`, `maximumFlowRate`, `endUseSubcategory`, and `systemAvailabilityManagerCouplingMode` map directly to the EnergyPlus object.
    // - Documented Delta: Schedule and node references remain relationship-only and are intentionally excluded from this wrapper.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object, with no additional child topology to synchronize.
    // - Evidence: `src/model/FanZoneExhaust.hpp`, `src/model/FanZoneExhaust.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateFanZoneExhaust.cpp`, and `src/epmodel/test/FanZoneExhaust_GTest.cpp`.
    // - Remaining Parity Work: Keep the scalar API aligned; add relationship helpers only if the canonical wrapper later exposes them directly.
    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    double fanEfficiency() const;
    bool setFanEfficiency(double fanTotalEfficiency);

    double pressureRise() const;
    bool setPressureRise(double pressureRise);

    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    std::string systemAvailabilityManagerCouplingMode() const;
    bool setSystemAvailabilityManagerCouplingMode(const std::string& systemAvailabilityManagerCouplingMode);

   protected:
    using ImplType = detail::FanZoneExhaust_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanZoneExhaust(std::shared_ptr<detail::FanZoneExhaust_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
