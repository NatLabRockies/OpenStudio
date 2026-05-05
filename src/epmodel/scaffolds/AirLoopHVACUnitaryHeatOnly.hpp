/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATONLY_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATONLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACUnitaryHeatOnly_Impl;
  }

  class EPMODEL_API AirLoopHVACUnitaryHeatOnly : public ModelObject
  {
   public:
    explicit AirLoopHVACUnitaryHeatOnly(const Model& model);

    virtual ~AirLoopHVACUnitaryHeatOnly() override = default;
    AirLoopHVACUnitaryHeatOnly(const AirLoopHVACUnitaryHeatOnly& other) = default;
    AirLoopHVACUnitaryHeatOnly(AirLoopHVACUnitaryHeatOnly&& other) = default;
    AirLoopHVACUnitaryHeatOnly& operator=(const AirLoopHVACUnitaryHeatOnly&) = default;
    AirLoopHVACUnitaryHeatOnly& operator=(AirLoopHVACUnitaryHeatOnly&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanObjectTypeValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> heatingCoilObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to AirLoopHVAC:UnitaryHeatOnly numeric/choice fields.
    // - Field Mapping: Availability schedule, inlet/outlet nodes, supply fan operating mode schedule, controlling zone, and *Name linkage fields remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    boost::optional<double> maximumSupplyAirTemperature() const;
    bool isMaximumSupplyAirTemperatureDefaulted() const;
    bool isMaximumSupplyAirTemperatureAutosized() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
    void resetMaximumSupplyAirTemperature();
    void autosizeMaximumSupplyAirTemperature();

    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool isHeatingSupplyAirFlowRateAutosized() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    void autosizeHeatingSupplyAirFlowRate();

    std::string supplyFanObjectType() const;
    bool setSupplyFanObjectType(const std::string& supplyFanObjectType);

    std::string fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);
    bool isFanPlacementDefaulted() const;
    void resetFanPlacement();

    std::string heatingCoilObjectType() const;
    bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

   protected:
    using ImplType = detail::AirLoopHVACUnitaryHeatOnly_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitaryHeatOnly(std::shared_ptr<detail::AirLoopHVACUnitaryHeatOnly_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
