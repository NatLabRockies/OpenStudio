/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICESHELF_IMPL_HPP
#define EPMODEL_DAYLIGHTINGDEVICESHELF_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DaylightingDeviceShelf_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DaylightingDeviceShelf_Impl() override = default;

  boost::optional<double> viewFactortoOutsideShelf() const;
  bool setViewFactortoOutsideShelf(double viewFactortoOutsideShelf);
  void resetViewFactortoOutsideShelf();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
