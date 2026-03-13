/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCONSTANTVOLUME_IMPL_HPP
#define EPMODEL_FANCONSTANTVOLUME_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "Node.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FanConstantVolume_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~FanConstantVolume_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node);

      double fanTotalEfficiency() const;
      bool setFanTotalEfficiency(double fanTotalEfficiency);

      double pressureRise() const;
      bool setPressureRise(double pressureRise);

      boost::optional<double> maximumFlowRate() const;
      bool setMaximumFlowRate(double maximumFlowRate);
      void resetMaximumFlowRate();
      void autosizeMaximumFlowRate();
      bool isMaximumFlowRateAutosized() const;

      double motorEfficiency() const;
      bool setMotorEfficiency(double motorEfficiency);

      double motorInAirstreamFraction() const;
      bool setMotorInAirstreamFraction(double motorInAirstreamFraction);

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
