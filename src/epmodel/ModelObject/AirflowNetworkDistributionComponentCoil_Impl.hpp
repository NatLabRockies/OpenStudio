/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCOIL_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCOIL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkDistributionComponentCoil_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkDistributionComponentCoil_Impl() override = default;

      std::string coilObjectType() const;
      bool setCoilObjectType(const std::string& coilObjectType);
      std::vector<std::string> coilObjectTypeValues() const;

      double airPathLength() const;
      bool setAirPathLength(double airPathLength);

      double airPathHydraulicDiameter() const;
      bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
