/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTLOOP_IMPL_HPP
#define EPMODEL_PLANTLOOP_IMPL_HPP

#include "Loop/Loop_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PlantLoop_Impl : public Loop_Impl
    {
     public:
      using Loop_Impl::Loop_Impl;
      virtual ~PlantLoop_Impl() override = default;

      std::string loadDistributionScheme() const;
      bool setLoadDistributionScheme(const std::string& scheme);

      std::string fluidType() const;
      bool setFluidType(const std::string& value);

      int glycolConcentration() const;
      bool setGlycolConcentration(int glycolConcentration);

      double maximumLoopTemperature() const;
      bool setMaximumLoopTemperature(double value);

      double minimumLoopTemperature() const;
      bool setMinimumLoopTemperature(double value);

      boost::optional<double> maximumLoopFlowRate() const;
      bool setMaximumLoopFlowRate(double value);
      bool isMaximumLoopFlowRateAutosized() const;
      void autosizeMaximumLoopFlowRate();

      boost::optional<double> minimumLoopFlowRate() const;
      bool setMinimumLoopFlowRate(double value);
      bool isMinimumLoopFlowRateAutosized() const;
      void autosizeMinimumLoopFlowRate();

      boost::optional<double> plantLoopVolume() const;
      bool setPlantLoopVolume(double value);
      bool isPlantLoopVolumeAutocalculated() const;
      void autocalculatePlantLoopVolume();

      std::string commonPipeSimulation() const;
      bool isCommonPipeSimulationDefaulted() const;
      bool setCommonPipeSimulation(const std::string& value);
      void resetCommonPipeSimulation();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
