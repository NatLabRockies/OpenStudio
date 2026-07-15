/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERCONSTANTCOP_HPP
#define EPMODEL_CHILLERCONSTANTCOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ChillerConstantCOP_Impl;
  }

  class EPMODEL_API ChillerConstantCOP : public ModelObject
  {
   public:
    explicit ChillerConstantCOP(const Model& model);

    virtual ~ChillerConstantCOP() override = default;
    ChillerConstantCOP(const ChillerConstantCOP& other) = default;
    ChillerConstantCOP(ChillerConstantCOP&& other) = default;
    ChillerConstantCOP& operator=(const ChillerConstantCOP&) = default;
    ChillerConstantCOP& operator=(ChillerConstantCOP&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();
    static std::vector<std::string> chillerFlowModeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived scalar accessor names.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus Chiller:ConstantCOP fields.
    // - Field Mapping: Relationship fields (node/object-list references) are excluded from this scalar-only scaffold.
    // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
    boost::optional<double> nominalCapacity() const;
    bool isNominalCapacityAutosized() const;
    bool setNominalCapacity(double nominalCapacity);
    void autosizeNominalCapacity();

    double nominalCOP() const;
    bool setNominalCOP(double nominalCOP);

    boost::optional<double> designChilledWaterFlowRate() const;
    bool isDesignChilledWaterFlowRateAutosized() const;
    bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
    void resetDesignChilledWaterFlowRate();
    void autosizeDesignChilledWaterFlowRate();

    boost::optional<double> designCondenserWaterFlowRate() const;
    bool isDesignCondenserWaterFlowRateAutosized() const;
    bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
    void resetDesignCondenserWaterFlowRate();
    void autosizeDesignCondenserWaterFlowRate();

    std::string condenserType() const;
    bool isCondenserTypeDefaulted() const;
    bool setCondenserType(const std::string& condenserType);
    void resetCondenserType();

    std::string chillerFlowMode() const;
    bool isChillerFlowModeDefaulted() const;
    bool setChillerFlowMode(const std::string& chillerFlowMode);
    void resetChillerFlowMode();

    double sizingFactor() const;
    bool isSizingFactorDefaulted() const;
    bool setSizingFactor(double sizingFactor);
    void resetSizingFactor();

    double basinHeaterCapacity() const;
    bool isBasinHeaterCapacityDefaulted() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);
    void resetBasinHeaterCapacity();

    double basinHeaterSetpointTemperature() const;
    bool isBasinHeaterSetpointTemperatureDefaulted() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
    void resetBasinHeaterSetpointTemperature();

    double thermosiphonMinimumTemperatureDifference() const;
    bool isThermosiphonMinimumTemperatureDifferenceDefaulted() const;
    bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);
    void resetThermosiphonMinimumTemperatureDifference();

   protected:
    using ImplType = detail::ChillerConstantCOP_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerConstantCOP(std::shared_ptr<detail::ChillerConstantCOP_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
