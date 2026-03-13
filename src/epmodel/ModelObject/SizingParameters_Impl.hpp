/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPARAMETERS_IMPL_HPP
#define EPMODEL_SIZINGPARAMETERS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SizingParameters_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SizingParameters_Impl() override = default;

      double heatingSizingFactor() const;
      bool isHeatingSizingFactorDefaulted() const;
      bool setHeatingSizingFactor(double heatingSizingFactor);
      void resetHeatingSizingFactor();

      double coolingSizingFactor() const;
      bool isCoolingSizingFactorDefaulted() const;
      bool setCoolingSizingFactor(double coolingSizingFactor);
      void resetCoolingSizingFactor();

      boost::optional<int> timestepsinAveragingWindow() const;
      bool setTimestepsinAveragingWindow(boost::optional<int> timestepsinAveragingWindow);
      void resetTimestepsinAveragingWindow();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
