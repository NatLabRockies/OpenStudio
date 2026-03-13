/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACFORCEDAIRUSERDEFINED_IMPL_HPP
#define EPMODEL_ZONEHVACFORCEDAIRUSERDEFINED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACForcedAirUserDefined_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACForcedAirUserDefined_Impl() override = default;

      /** @name Number of Plant Loop Connections */
      //@{
      int numberofPlantLoopConnections() const;
      bool setNumberofPlantLoopConnections(int numberofPlantLoopConnections);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
