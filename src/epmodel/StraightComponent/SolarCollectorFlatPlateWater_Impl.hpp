/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORFLATPLATEWATER_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORFLATPLATEWATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SolarCollectorFlatPlateWater_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~SolarCollectorFlatPlateWater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      /** @name Maximum flow rate */
      //@{
      boost::optional<double> maximumFlowRate() const;
      bool setMaximumFlowRate(double maximumFlowRate);
      void resetMaximumFlowRate();
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
