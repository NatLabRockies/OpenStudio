/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYINCIDENTSOLARMULTIPLIER_IMPL_HPP
#define EPMODEL_SURFACEPROPERTYINCIDENTSOLARMULTIPLIER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfacePropertyIncidentSolarMultiplier_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfacePropertyIncidentSolarMultiplier_Impl() override = default;

      double incidentSolarMultiplier() const;
      bool setIncidentSolarMultiplier(double incidentSolarMultiplier);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
