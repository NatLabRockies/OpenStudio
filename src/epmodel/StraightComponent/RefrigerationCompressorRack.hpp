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
    // - API: Preserve openstudio::model::RefrigerationCompressorRack scalar accessor names/signatures for counterpart parity.
    // - Field Mapping: heatRejectionLocation, designCompressorRackCOP, designCondenserFanPower, condenserType, waterCooledLoopFlowType,
    //   waterCooledCondenserDesignFlowRate, waterCooledCondenserMaximumFlowRate, evaporativeCondenserEffectiveness, evaporativeCondenserAirFlowRate,
    //   basinHeaterCapacity, basinHeaterSetpointTemperature, designEvaporativeCondenserWaterPumpPower, and endUseSubcategory map directly to
    //   EnergyPlus Refrigeration:CompressorRack fields per ForwardTranslateRefrigerationCompressorRack.cpp.
    // - Field Mapping: The autocalculatable evaporativeCondenserAirFlowRate and designEvaporativeCondenserWaterPumpPower fields expose
    //   is...Autocalculated/autocalculate helpers mirroring the autocalculatable metadata in the IDD.
    // - Field Mapping: Curve, schedule, node, and object-list fields (e.g., compressor/cop curves, schedule names, node names, and case/walk-in
    //   lists) are intentionally excluded in this scalar-only pass.
    std::string heatRejectionLocation() const;

    double designCompressorRackCOP() const;

    double designCondenserFanPower() const;

    std::string condenserType() const;

    std::string waterCooledLoopFlowType() const;

    boost::optional<double> waterCooledCondenserDesignFlowRate() const;
    boost::optional<double> waterCooledCondenserMaximumFlowRate() const;
    double waterCooledCondenserMaximumWaterOutletTemperature() const;
    double waterCooledCondenserMinimumWaterInletTemperature() const;

    double evaporativeCondenserEffectiveness() const;
    boost::optional<double> evaporativeCondenserAirFlowRate() const;
    bool isEvaporativeCondenserAirFlowRateAutocalculated() const;

    double basinHeaterCapacity() const;
    double basinHeaterSetpointTemperature() const;

    boost::optional<double> designEvaporativeCondenserWaterPumpPower() const;
    bool isDesignEvaporativeCondenserWaterPumpPowerAutocalculated() const;

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;

    bool setHeatRejectionLocation(const std::string& heatRejectionLocation);

    bool setDesignCompressorRackCOP(double designCompressorRackCOP);

    bool setDesignCondenserFanPower(double designCondenserFanPower);

    bool setCondenserType(const std::string& condenserType);

    bool setWaterCooledLoopFlowType(const std::string& waterCooledLoopFlowType);

    bool setWaterCooledCondenserDesignFlowRate(double waterCooledCondenserDesignFlowRate);
    void resetWaterCooledCondenserDesignFlowRate();

    bool setWaterCooledCondenserMaximumFlowRate(double waterCooledCondenserMaximumFlowRate);
    void resetWaterCooledCondenserMaximumFlowRate();

    bool setWaterCooledCondenserMaximumWaterOutletTemperature(double waterCooledCondenserMaximumWaterOutletTemperature);
    bool setWaterCooledCondenserMinimumWaterInletTemperature(double waterCooledCondenserMinimumWaterInletTemperature);

    bool setEvaporativeCondenserEffectiveness(double evaporativeCondenserEffectiveness);

    bool setEvaporativeCondenserAirFlowRate(double evaporativeCondenserAirFlowRate);
    bool autocalculateEvaporativeCondenserAirFlowRate();

    bool setBasinHeaterCapacity(double basinHeaterCapacity);
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    bool setDesignEvaporativeCondenserWaterPumpPower(double designEvaporativeCondenserWaterPumpPower);
    bool autocalculateDesignEvaporativeCondenserWaterPumpPower();

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
