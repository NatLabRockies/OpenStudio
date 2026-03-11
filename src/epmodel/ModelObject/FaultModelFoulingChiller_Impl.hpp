/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGCHILLER_IMPL_HPP
#define EPMODEL_FAULTMODELFOULINGCHILLER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelFoulingChiller_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelFoulingChiller_Impl() override = default;

  std::string chillerObjectType() const;
  bool setChillerObjectType(const std::string& chillerObjectType);

  double foulingFactor() const;
  bool isFoulingFactorDefaulted() const;
  bool setFoulingFactor(double foulingFactor);
  void resetFoulingFactor();

  std::vector<std::string> chillerObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
