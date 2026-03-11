/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACUNITHEATER_HPP
#define EPMODEL_ZONEHVACUNITHEATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

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

  class EPMODEL_API ZoneHVACUnitHeater : public ModelObject
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
    // - API: Scalar accessors preserve the openstudio::model names (maximumSupplyAirFlowRate, fanControlType, maximumHotWaterFlowRate,
    //   minimumHotWaterFlowRate, heatingConvergenceTolerance) while mapping directly to the EnergyPlus ZoneHVAC:UnitHeater fields via
    //   ZoneHVAC_UnitHeaterFields (see ForwardTranslateZoneHVACUnitHeater.cpp for the mapping evidence).
    // - Field Mapping: availability/supply fan/heating coil references and node targets remain relationship-only and are intentionally
    //   excluded from this scalar-only surface until dedicated helpers exist.

    /** @name Getters */
    //@{
    boost::optional<double> maximumSupplyAirFlowRate() const;
    bool isMaximumSupplyAirFlowRateAutosized() const;

    std::string fanControlType() const;

    boost::optional<double> maximumHotWaterFlowRate() const;
    bool isMaximumHotWaterFlowRateAutosized() const;

    double minimumHotWaterFlowRate() const;
    bool isMinimumHotWaterFlowRateDefaulted() const;

    double heatingConvergenceTolerance() const;
    bool isHeatingConvergenceToleranceDefaulted() const;

    boost::optional<double> autosizedMaximumSupplyAirFlowRate() const;
    boost::optional<double> autosizedMaximumHotWaterFlowRate() const;
    //@}

    /** @name Setters */
    //@{
    bool setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate);
    void autosizeMaximumSupplyAirFlowRate();

    bool setFanControlType(const std::string& fanControlType);

    bool setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate);
    void resetMaximumHotWaterFlowRate();
    void autosizeMaximumHotWaterFlowRate();

    bool setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate);
    void resetMinimumHotWaterFlowRate();

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
