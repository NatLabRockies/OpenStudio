/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICALSIZINGRECTANGLE_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICALSIZINGRECTANGLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatExchangerVerticalSizingRectangle_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatExchangerVerticalSizingRectangle_Impl() override = default;

  double designFlowRatePerBorehole() const;
  double availableBoreholeFieldLength() const;
  double availableBoreholeFieldWidth() const;
  double maximumNumberofBoreholes() const;
  double minimumBoreholeSpacing() const;
  double maximumBoreholeSpacing() const;
  double minimumBoreholeVerticalLength() const;
  double maximumBoreholeVerticalLength() const;
  double minimumExitingFluidTemperatureforSizing() const;
  double maximumExitingFluidTemperatureforSizing() const;

  bool isDesignFlowRatePerBoreholeDefaulted() const;
  bool isMinimumBoreholeSpacingDefaulted() const;
  bool isMaximumBoreholeSpacingDefaulted() const;
  bool isMinimumBoreholeVerticalLengthDefaulted() const;
  bool isMaximumBoreholeVerticalLengthDefaulted() const;
  bool isMinimumExitingFluidTemperatureforSizingDefaulted() const;
  bool isMaximumExitingFluidTemperatureforSizingDefaulted() const;

  bool setDesignFlowRatePerBorehole(double designFlowRatePerBorehole);
  bool setAvailableBoreholeFieldLength(double availableBoreholeFieldLength);
  bool setAvailableBoreholeFieldWidth(double availableBoreholeFieldWidth);
  bool setMaximumNumberofBoreholes(double maximumNumberofBoreholes);
  bool setMinimumBoreholeSpacing(double minimumBoreholeSpacing);
  bool setMaximumBoreholeSpacing(double maximumBoreholeSpacing);
  bool setMinimumBoreholeVerticalLength(double minimumBoreholeVerticalLength);
  bool setMaximumBoreholeVerticalLength(double maximumBoreholeVerticalLength);
  bool setMinimumExitingFluidTemperatureforSizing(double minimumExitingFluidTemperatureforSizing);
  bool setMaximumExitingFluidTemperatureforSizing(double maximumExitingFluidTemperatureforSizing);

  void resetDesignFlowRatePerBorehole();
  void resetMinimumBoreholeSpacing();
  void resetMaximumBoreholeSpacing();
  void resetMinimumBoreholeVerticalLength();
  void resetMaximumBoreholeVerticalLength();
  void resetMinimumExitingFluidTemperatureforSizing();
  void resetMaximumExitingFluidTemperatureforSizing();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
