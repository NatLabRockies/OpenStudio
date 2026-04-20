/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONHEATING_IMPL_HPP
#define EPMODEL_HEATPUMPWATERTOWATERPARAMETERESTIMATIONHEATING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HeatPumpWaterToWaterParameterEstimationHeating_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HeatPumpWaterToWaterParameterEstimationHeating_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
