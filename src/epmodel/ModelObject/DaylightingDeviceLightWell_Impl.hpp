/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICELIGHTWELL_IMPL_HPP
#define EPMODEL_DAYLIGHTINGDEVICELIGHTWELL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DaylightingDeviceLightWell_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DaylightingDeviceLightWell_Impl() override = default;

  double heightofWell() const;
  bool setHeightofWell(double heightofWell);

  double perimeterofBottomofWell() const;
  bool setPerimeterofBottomofWell(double perimeterofBottomofWell);

  double areaofBottomofWell() const;
  bool setAreaofBottomofWell(double areaofBottomofWell);

  double visibleReflectanceofWellWalls() const;
  bool setVisibleReflectanceofWellWalls(double visibleReflectanceofWellWalls);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
