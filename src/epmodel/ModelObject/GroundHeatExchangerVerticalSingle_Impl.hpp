/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICALSINGLE_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICALSINGLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatExchangerVerticalSingle_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatExchangerVerticalSingle_Impl() override = default;

      double xLocation() const;
      bool setXLocation(double xLocation);

      double yLocation() const;
      bool setYLocation(double yLocation);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
