/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCOMPRESSORRACK_HPP
#define EPMODEL_REFRIGERATIONCOMPRESSORRACK_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {

    class RefrigerationCompressorRack_Impl;

  }

  class EPMODEL_API RefrigerationCompressorRack : public StraightComponent
  {
   public:
    explicit RefrigerationCompressorRack(const Model& model);

    virtual ~RefrigerationCompressorRack() override = default;
    RefrigerationCompressorRack(const RefrigerationCompressorRack& other) = default;
    RefrigerationCompressorRack(RefrigerationCompressorRack&& other) = default;
    RefrigerationCompressorRack& operator=(const RefrigerationCompressorRack&) = default;
    RefrigerationCompressorRack& operator=(RefrigerationCompressorRack&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();
    static std::vector<std::string> waterCooledLoopFlowTypeValues();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical refrigeration-compressor-rack scalar surface is present, while curve, schedule, node, and object-list helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::RefrigerationCompressorRack.
    // - Implemented Parity: The preserved scalar API covers heat-rejection, condenser configuration, pump power, basin-heater, and end-use fields with matching default/autocalculate behavior.
    // - Documented Delta: Curve, schedule, node, and object-list helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Refrigeration:CompressorRack` scalar fields used by the forward translator.
    // - Evidence: `src/model/RefrigerationCompressorRack.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateRefrigerationCompressorRack.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.

    // Heat rejection
    std::string heatRejectionLocation() const;
    bool setHeatRejectionLocation(const std::string& heatRejectionLocation);

    // Compressor rack performance
    double designCompressorRackCOP() const;
    bool setDesignCompressorRackCOP(double designCompressorRackCOP);

    double designCondenserFanPower() const;
    bool setDesignCondenserFanPower(double designCondenserFanPower);

    // Condenser configuration
    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    std::string waterCooledLoopFlowType() const;
    bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);

    boost::optional<double> waterCooledCondenserDesignFlowRate() const;
    bool setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate);
    void resetWaterCooledCondenserDesignFlowRate();

    boost::optional<double> waterCooledCondenserMaximumFlowRate() const;
    bool setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate);
    void resetWaterCooledCondenserMaximumFlowRate();

    double waterCooledCondenserMaximumWaterOutletTemperature() const;
    bool setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature);

    double waterCooledCondenserMinimumWaterInletTemperature() const;
    bool setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature);

    // Evaporative condenser
    double evaporativeCondenserEffectiveness() const;
    bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

    boost::optional<double> evaporativeCondenserAirFlowRate() const;
    bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
    bool isEvaporativeCondenserAirFlowRateAutocalculated() const;
    bool autocalculateEvaporativeCondenserAirFlowRate();

    // Basin heater
    double basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);

    double basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    // Evaporative condenser water pump
    boost::optional<double> designEvaporativeCondenserWaterPumpPower() const;
    bool setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower);
    bool isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const;
    bool autocalculateDesignEvaporativeCondenserWaterPumpPower();

    // End use categorization
    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::RefrigerationCompressorRack_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationCompressorRack(std::shared_ptr<detail::RefrigerationCompressorRack_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
