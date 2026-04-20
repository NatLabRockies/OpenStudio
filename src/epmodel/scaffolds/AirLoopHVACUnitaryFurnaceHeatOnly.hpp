/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYFURNACEHEATONLY_HPP
#define EPMODEL_AIRLOOPHVACUNITARYFURNACEHEATONLY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACUnitaryFurnaceHeatOnly_Impl;
  }

  class EPMODEL_API AirLoopHVACUnitaryFurnaceHeatOnly : public ModelObject
  {
   public:
    explicit AirLoopHVACUnitaryFurnaceHeatOnly(const Model& model);

    virtual ~AirLoopHVACUnitaryFurnaceHeatOnly() override = default;
    AirLoopHVACUnitaryFurnaceHeatOnly(const AirLoopHVACUnitaryFurnaceHeatOnly& other) = default;
    AirLoopHVACUnitaryFurnaceHeatOnly(AirLoopHVACUnitaryFurnaceHeatOnly&& other) = default;
    AirLoopHVACUnitaryFurnaceHeatOnly& operator=(const AirLoopHVACUnitaryFurnaceHeatOnly&) = default;
    AirLoopHVACUnitaryFurnaceHeatOnly& operator=(AirLoopHVACUnitaryFurnaceHeatOnly&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanObjectTypeValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> heatingCoilObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to AirLoopHVAC:Unitary:Furnace:HeatOnly numeric/choice fields.
    // - Field Mapping: Availability schedule, inlet/outlet nodes, supply fan operating mode schedule, controlling zone, and *Name linkage fields remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    boost::optional<double> maximumSupplyAirTemperature() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
    bool isMaximumSupplyAirTemperatureDefaulted() const;
    bool isMaximumSupplyAirTemperatureAutosized() const;
    void resetMaximumSupplyAirTemperature();
    void autosizeMaximumSupplyAirTemperature();

    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    bool isHeatingSupplyAirFlowRateAutosized() const;
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
    using ImplType = detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitaryFurnaceHeatOnly(std::shared_ptr<detail::AirLoopHVACUnitaryFurnaceHeatOnly_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
