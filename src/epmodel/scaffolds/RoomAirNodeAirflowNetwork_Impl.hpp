/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORK_IMPL_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORK_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoomAirNodeAirflowNetwork_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirNodeAirflowNetwork_Impl() override = default;

      boost::optional<double> fractionOfZoneAirVolume() const;
      bool isFractionOfZoneAirVolumeDefaulted() const;
      bool setFractionOfZoneAirVolume(double fractionOfZoneAirVolume);
      void resetFractionOfZoneAirVolume();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
