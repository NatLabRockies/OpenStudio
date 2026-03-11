/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONAIRBOUNDARY_IMPL_HPP
#define EPMODEL_CONSTRUCTIONAIRBOUNDARY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ConstructionAirBoundary_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ConstructionAirBoundary_Impl() override = default;

  // Simple scalar-only API; schedule/object-link fields remain intentionally excluded in this scaffold pass.
  std::string airExchangeMethod() const;
  bool isAirExchangeMethodDefaulted() const;

  double simpleMixingAirChangesPerHour() const;
  bool isSimpleMixingAirChangesPerHourDefaulted() const;

  bool setAirExchangeMethod(const std::string& airExchangeMethod);
  void resetAirExchangeMethod();

  bool setSimpleMixingAirChangesPerHour(double simpleMixingAirChangesPerHour);
  void resetSimpleMixingAirChangesPerHour();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
