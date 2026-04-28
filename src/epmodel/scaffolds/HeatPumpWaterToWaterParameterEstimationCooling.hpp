/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONCOOLING_HPP
#define EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONCOOLING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HeatPumpWaterToWaterParameterEstimationCooling_Impl;
  }

  class EPMODEL_API HeatPumpWaterToWaterParameterEstimationCooling : public ModelObject
  {
   public:
    explicit HeatPumpWaterToWaterParameterEstimationCooling(const Model& model);

    virtual ~HeatPumpWaterToWaterParameterEstimationCooling() override = default;
    HeatPumpWaterToWaterParameterEstimationCooling(const HeatPumpWaterToWaterParameterEstimationCooling& other) = default;
    HeatPumpWaterToWaterParameterEstimationCooling(HeatPumpWaterToWaterParameterEstimationCooling&& other) = default;
    HeatPumpWaterToWaterParameterEstimationCooling& operator=(const HeatPumpWaterToWaterParameterEstimationCooling&) = default;
    HeatPumpWaterToWaterParameterEstimationCooling& operator=(HeatPumpWaterToWaterParameterEstimationCooling&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to HeatPump:WaterToWater:ParameterEstimation:Cooling numeric fields.
    // - Field Mapping: Name and source/load-side node linkage fields remain excluded as relationship fields.
    // - TODO(parity): Add non-scalar relationship APIs after scalar saturation without changing scalar signatures.

    boost::optional<double> nominalCOP() const;
    bool setNominalCOP(double nominalCOP);

    boost::optional<double> nominalCapacity() const;
    bool setNominalCapacity(double nominalCapacity);

    boost::optional<double> minimumPartLoadRatio() const;
    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

    boost::optional<double> maximumPartLoadRatio() const;
    bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

    boost::optional<double> optimumPartLoadRatio() const;
    bool setOptimumPartLoadRatio(double optimumPartLoadRatio);

    boost::optional<double> loadSideFlowRate() const;
    bool setLoadSideFlowRate(double loadSideFlowRate);

    boost::optional<double> sourceSideFlowRate() const;
    bool setSourceSideFlowRate(double sourceSideFlowRate);

    boost::optional<double> loadSideHeatTransferCoefficient() const;
    bool setLoadSideHeatTransferCoefficient(double loadSideHeatTransferCoefficient);

    boost::optional<double> sourceSideHeatTransferCoefficient() const;
    bool setSourceSideHeatTransferCoefficient(double sourceSideHeatTransferCoefficient);

    boost::optional<double> pistonDisplacement() const;
    bool setPistonDisplacement(double pistonDisplacement);

    boost::optional<double> compressorClearanceFactor() const;
    bool setCompressorClearanceFactor(double compressorClearanceFactor);

    boost::optional<double> compressorSuctionandDischargePressureDrop() const;
    bool setCompressorSuctionandDischargePressureDrop(double compressorSuctionandDischargePressureDrop);

    boost::optional<double> superheating() const;
    bool setSuperheating(double superheating);

    boost::optional<double> constantPartofElectromechanicalPowerLosses() const;
    bool setConstantPartofElectromechanicalPowerLosses(double constantPartofElectromechanicalPowerLosses);

    boost::optional<double> lossFactor() const;
    bool setLossFactor(double lossFactor);

    double highPressureCutOff() const;
    bool isHighPressureCutOffDefaulted() const;
    bool setHighPressureCutOff(double highPressureCutOff);
    void resetHighPressureCutOff();

    double lowPressureCutOff() const;
    bool isLowPressureCutOffDefaulted() const;
    bool setLowPressureCutOff(double lowPressureCutOff);
    void resetLowPressureCutOff();

   protected:
    using ImplType = detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatPumpWaterToWaterParameterEstimationCooling(std::shared_ptr<detail::HeatPumpWaterToWaterParameterEstimationCooling_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
