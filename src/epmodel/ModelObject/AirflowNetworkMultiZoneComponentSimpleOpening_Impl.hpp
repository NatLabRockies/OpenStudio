/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTSIMPLEOPENING_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTSIMPLEOPENING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneComponentSimpleOpening_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneComponentSimpleOpening_Impl() override = default;

      double airMassFlowCoefficientWhenOpeningisClosed() const;
      bool setAirMassFlowCoefficientWhenOpeningisClosed(double airMassFlowCoefficientWhenOpeningisClosed);

      double airMassFlowExponentWhenOpeningisClosed() const;
      bool setAirMassFlowExponentWhenOpeningisClosed(double airMassFlowExponentWhenOpeningisClosed);
      bool isAirMassFlowExponentWhenOpeningisClosedDefaulted() const;
      void resetAirMassFlowExponentWhenOpeningisClosed();

      double minimumDensityDifferenceforTwoWayFlow() const;
      bool setMinimumDensityDifferenceforTwoWayFlow(double minimumDensityDifferenceforTwoWayFlow);

      double dischargeCoefficient() const;
      bool setDischargeCoefficient(double dischargeCoefficient);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
