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
      bool isDesignFlowRatePerBoreholeDefaulted() const;
      bool setDesignFlowRatePerBorehole(double designFlowRatePerBorehole);
      void resetDesignFlowRatePerBorehole();

      double availableBoreholeFieldLength() const;
      bool setAvailableBoreholeFieldLength(double availableBoreholeFieldLength);

      double availableBoreholeFieldWidth() const;
      bool setAvailableBoreholeFieldWidth(double availableBoreholeFieldWidth);

      double maximumNumberofBoreholes() const;
      bool setMaximumNumberofBoreholes(double maximumNumberofBoreholes);

      double minimumBoreholeSpacing() const;
      bool isMinimumBoreholeSpacingDefaulted() const;
      bool setMinimumBoreholeSpacing(double minimumBoreholeSpacing);
      void resetMinimumBoreholeSpacing();

      double maximumBoreholeSpacing() const;
      bool isMaximumBoreholeSpacingDefaulted() const;
      bool setMaximumBoreholeSpacing(double maximumBoreholeSpacing);
      void resetMaximumBoreholeSpacing();

      double minimumBoreholeVerticalLength() const;
      bool isMinimumBoreholeVerticalLengthDefaulted() const;
      bool setMinimumBoreholeVerticalLength(double minimumBoreholeVerticalLength);
      void resetMinimumBoreholeVerticalLength();

      double maximumBoreholeVerticalLength() const;
      bool isMaximumBoreholeVerticalLengthDefaulted() const;
      bool setMaximumBoreholeVerticalLength(double maximumBoreholeVerticalLength);
      void resetMaximumBoreholeVerticalLength();

      double minimumExitingFluidTemperatureforSizing() const;
      bool isMinimumExitingFluidTemperatureforSizingDefaulted() const;
      bool setMinimumExitingFluidTemperatureforSizing(double minimumExitingFluidTemperatureforSizing);
      void resetMinimumExitingFluidTemperatureforSizing();

      double maximumExitingFluidTemperatureforSizing() const;
      bool isMaximumExitingFluidTemperatureforSizingDefaulted() const;
      bool setMaximumExitingFluidTemperatureforSizing(double maximumExitingFluidTemperatureforSizing);
      void resetMaximumExitingFluidTemperatureforSizing();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
