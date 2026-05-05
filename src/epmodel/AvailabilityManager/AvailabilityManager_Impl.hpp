/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGER_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Loop;

  namespace detail {

    class EPMODEL_API AvailabilityManager_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AvailabilityManager_Impl() override = default;

      boost::optional<openstudio::epmodel::Loop> loop() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
