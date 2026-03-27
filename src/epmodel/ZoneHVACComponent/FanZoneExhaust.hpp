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
    // - API: Preserves openstudio::model::FanZoneExhaust scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: fanEfficiency API delegates to FanTotalEfficiency (same as openstudio::model).
    // - Field Mapping: scalar APIs map directly to E+ Fan:ZoneExhaust fields; relationship fields (schedules/nodes) remain excluded.
    // - ForwardTranslator evidence: ForwardTranslateFanZoneExhaust.cpp writes these scalar fields directly.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
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
