/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TIMESTEP_IMPL_HPP
#define EPMODEL_TIMESTEP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Timestep_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Timestep_Impl() override = default;

      int numberOfTimestepsPerHour() const;
      bool isNumberOfTimestepsPerHourDefaulted() const;
      bool setNumberOfTimestepsPerHour(int numberOfTimestepsPerHour);
      void resetNumberOfTimestepsPerHour();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_TIMESTEP_IMPL_HPP
