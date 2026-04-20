/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONETHERMALCHIMNEY_IMPL_HPP
#define EPMODEL_ZONETHERMALCHIMNEY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneThermalChimney_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneThermalChimney_Impl() override = default;

      double widthOfTheAbsorberWall() const;
      bool setWidthOfTheAbsorberWall(double widthOfTheAbsorberWall);

      double crossSectionalAreaOfAirChannelOutlet() const;
      bool setCrossSectionalAreaOfAirChannelOutlet(double crossSectionalAreaOfAirChannelOutlet);

      double dischargeCoefficient() const;
      bool setDischargeCoefficient(double dischargeCoefficient);
      bool isDischargeCoefficientDefaulted() const;
      void resetDischargeCoefficient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
