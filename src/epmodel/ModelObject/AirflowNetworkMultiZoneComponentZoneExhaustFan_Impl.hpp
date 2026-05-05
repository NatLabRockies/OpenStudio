/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTZONEEXHAUSTFAN_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONECOMPONENTZONEEXHAUSTFAN_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneComponentZoneExhaustFan_Impl() override = default;

      double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions() const;
      bool setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(
        double airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions);

      double airMassFlowExponentWhentheZoneExhaustFanisOff() const;
      bool isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted() const;
      bool setAirMassFlowExponentWhentheZoneExhaustFanisOff(double airMassFlowExponentWhentheZoneExhaustFanisOff);
      void resetAirMassFlowExponentWhentheZoneExhaustFanisOff();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
