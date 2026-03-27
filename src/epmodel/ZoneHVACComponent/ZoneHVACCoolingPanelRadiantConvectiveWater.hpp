/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP

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
    class ZoneHVACCoolingPanelRadiantConvectiveWater_Impl;
  }

  class EPMODEL_API ZoneHVACCoolingPanelRadiantConvectiveWater : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACCoolingPanelRadiantConvectiveWater(const Model& model);

    virtual ~ZoneHVACCoolingPanelRadiantConvectiveWater() override = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater(const ZoneHVACCoolingPanelRadiantConvectiveWater& other) = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater(ZoneHVACCoolingPanelRadiantConvectiveWater&& other) = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater& operator=(const ZoneHVACCoolingPanelRadiantConvectiveWater&) = default;
    ZoneHVACCoolingPanelRadiantConvectiveWater& operator=(ZoneHVACCoolingPanelRadiantConvectiveWater&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> coolingDesignCapacityMethodValues();
    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> condensationControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar field groups are aligned, and the remaining schedule/node/surface wiring is still relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACCoolingPanelRadiantConvectiveWater.
    // - Implemented Parity: The inlet temperatures, water mass flow, control type fields, condensation controls, and radiant-fraction scalars map directly to the EnergyPlus object and its translator.
    // - Documented Delta: Availability schedule, water inlet/outlet nodes, cooling coil links, schedule links, and extensible surface groups are intentionally excluded from the scalar surface.
    // - Field/Storage Mapping: Scalar inputs live on the EnergyPlus object; surface membership and hydraulic connections are tracked through explicit child/topology state.
    // - Evidence: `src/model/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp`, `src/model/ZoneHVACCoolingPanelRadiantConvectiveWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACCoolingPanelRadiantConvectiveWater.cpp`, and `src/epmodel/test/ZoneHVACCoolingPanelRadiantConvectiveWater_GTest.cpp`.
    // - Remaining Parity Work: Add relationship helpers only if the canonical wrapper exposes more of the schedule and node topology directly.

    double ratedInletWaterTemperature() const;
    bool isRatedInletWaterTemperatureDefaulted() const;
    bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);
    void resetRatedInletWaterTemperature();

    double ratedInletSpaceTemperature() const;
    bool isRatedInletSpaceTemperatureDefaulted() const;
    bool setRatedInletSpaceTemperature(double ratedInletSpaceTemperature);
    void resetRatedInletSpaceTemperature();

    double ratedWaterMassFlowRate() const;
    bool isRatedWaterMassFlowRateDefaulted() const;
    bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
    void resetRatedWaterMassFlowRate();

    std::string coolingDesignCapacityMethod() const;
    bool isCoolingDesignCapacityMethodDefaulted() const;
    bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
    void resetCoolingDesignCapacityMethod();

    boost::optional<double> coolingDesignCapacity() const;
    bool isCoolingDesignCapacityAutosized() const;
    bool setCoolingDesignCapacity(double coolingDesignCapacity);
    void autosizeCoolingDesignCapacity();

    boost::optional<double> coolingDesignCapacityPerFloorArea() const;
    bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
    void resetCoolingDesignCapacityPerFloorArea();

    boost::optional<double> fractionOfAutosizedCoolingDesignCapacity() const;
    bool setFractionOfAutosizedCoolingDesignCapacity(double fractionOfAutosizedCoolingDesignCapacity);
    void resetFractionOfAutosizedCoolingDesignCapacity();

    boost::optional<double> maximumChilledWaterFlowRate() const;
    bool isMaximumChilledWaterFlowRateAutosized() const;
    bool setMaximumChilledWaterFlowRate(double maximumChilledWaterFlowRate);
    void autosizeMaximumChilledWaterFlowRate();

    std::string controlType() const;
    bool isControlTypeDefaulted() const;
    bool setControlType(const std::string& controlType);
    void resetControlType();

    double coolingControlThrottlingRange() const;
    bool isCoolingControlThrottlingRangeDefaulted() const;
    bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);
    void resetCoolingControlThrottlingRange();

    std::string condensationControlType() const;
    bool isCondensationControlTypeDefaulted() const;
    bool setCondensationControlType(const std::string& condensationControlType);
    void resetCondensationControlType();

    double condensationControlDewpointOffset() const;
    bool isCondensationControlDewpointOffsetDefaulted() const;
    bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);
    void resetCondensationControlDewpointOffset();

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    boost::optional<double> fractionOfRadiantEnergyIncidentOnPeople() const;
    bool setFractionOfRadiantEnergyIncidentOnPeople(double fractionOfRadiantEnergyIncidentOnPeople);
    void resetFractionOfRadiantEnergyIncidentOnPeople();

   protected:
    using ImplType = detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACCoolingPanelRadiantConvectiveWater(std::shared_ptr<detail::ZoneHVACCoolingPanelRadiantConvectiveWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONEHVACCOOLINGPANELRADIANTCONVECTIVEWATER_HPP
