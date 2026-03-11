/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONDENSERLOOP_IMPL_HPP
#define EPMODEL_CONDENSERLOOP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CondenserLoop_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CondenserLoop_Impl() override = default;

  std::string fluidType() const;
  bool isFluidTypeDefaulted() const;
  bool setFluidType(const std::string& fluidType);
  void resetFluidType();

  double maximumLoopTemperature() const;
  bool setMaximumLoopTemperature(double maximumLoopTemperature);

  double minimumLoopTemperature() const;
  bool setMinimumLoopTemperature(double minimumLoopTemperature);

  boost::optional<double> maximumLoopFlowRate() const;
  bool setMaximumLoopFlowRate(double maximumLoopFlowRate);
  bool isMaximumLoopFlowRateAutosized() const;
  void autosizeMaximumLoopFlowRate();

  double minimumLoopFlowRate() const;
  bool isMinimumLoopFlowRateDefaulted() const;
  bool setMinimumLoopFlowRate(double minimumLoopFlowRate);
  void resetMinimumLoopFlowRate();

  boost::optional<double> condenserLoopVolume() const;
  bool setCondenserLoopVolume(double condenserLoopVolume);
  bool isCondenserLoopVolumeAutocalculated() const;
  void autocalculateCondenserLoopVolume();
  void resetCondenserLoopVolume();

  std::string loadDistributionScheme() const;
  bool isLoadDistributionSchemeDefaulted() const;
  bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
  void resetLoadDistributionScheme();

  std::string pressureSimulationType() const;
  bool isPressureSimulationTypeDefaulted() const;
  bool setPressureSimulationType(const std::string& pressureSimulationType);
  void resetPressureSimulationType();

  double loopCirculationTime() const;
  bool isLoopCirculationTimeDefaulted() const;
  bool setLoopCirculationTime(double loopCirculationTime);
  void resetLoopCirculationTime();

  std::vector<std::string> fluidTypeValues() const;
  std::vector<std::string> loadDistributionSchemeValues() const;
  std::vector<std::string> pressureSimulationTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
