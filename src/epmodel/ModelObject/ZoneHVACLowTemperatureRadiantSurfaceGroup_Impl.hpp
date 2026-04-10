/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACLOWTEMPERATURERADIANTSURFACEGROUP_IMPL_HPP
#define EPMODEL_ZONEHVACLOWTEMPERATURERADIANTSURFACEGROUP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Surface;

  namespace detail {

    class EPMODEL_API ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl() override = default;

      std::vector<Surface> surfaces() const;
      std::vector<double> flowFractions() const;

      void clearSurfaces();
      bool addSurface(Surface& surface, double flowFraction);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
