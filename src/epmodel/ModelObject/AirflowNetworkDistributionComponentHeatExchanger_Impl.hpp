/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTHEATEXCHANGER_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTHEATEXCHANGER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkDistributionComponentHeatExchanger_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkDistributionComponentHeatExchanger_Impl() override = default;

      double airPathLength() const;
      bool setAirPathLength(double airPathLength);

      double airPathHydraulicDiameter() const;
      bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
