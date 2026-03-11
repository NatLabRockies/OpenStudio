/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDELIGHTCOMPLEXFENESTRATION_IMPL_HPP
#define EPMODEL_DAYLIGHTINGDELIGHTCOMPLEXFENESTRATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DaylightingDELightComplexFenestration_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DaylightingDELightComplexFenestration_Impl() override = default;

  std::string complexFenestrationType() const;
  bool setComplexFenestrationType(const std::string& complexFenestrationType);

  double fenestrationRotation() const;
  bool isFenestrationRotationDefaulted() const;
  bool setFenestrationRotation(double fenestrationRotation);
  void resetFenestrationRotation();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
