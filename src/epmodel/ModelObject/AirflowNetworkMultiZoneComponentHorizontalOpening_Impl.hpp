/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTHORIZONTALOPENING_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTHORIZONTALOPENING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneComponentHorizontalOpening_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneComponentHorizontalOpening_Impl() override = default;

      double airMassFlowCoefficientWhenOpeningisClosed() const;
      bool setAirMassFlowCoefficientWhenOpeningisClosed(double airMassFlowCoefficientWhenOpeningisClosed);

      double airMassFlowExponentWhenOpeningisClosed() const;
      bool setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed);
      bool isAirMassFlowExponentWhenOpeningisClosedDefaulted() const;
      void resetAirMassFlowExponentWhenOpeningisClosed();

      double slopingPlaneAngle() const;
      bool setSlopingPlaneAngle(double slopingPlaneAngle);
      bool isSlopingPlaneAngleDefaulted() const;
      void resetSlopingPlaneAngle();

      double dischargeCoefficient() const;
      bool setDischargeCoefficient(double dischargeCoefficient);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
