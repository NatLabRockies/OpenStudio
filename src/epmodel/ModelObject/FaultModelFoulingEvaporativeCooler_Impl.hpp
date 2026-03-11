/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGEVAPORATIVECOOLER_IMPL_HPP
#define EPMODEL_FAULTMODELFOULINGEVAPORATIVECOOLER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelFoulingEvaporativeCooler_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelFoulingEvaporativeCooler_Impl() override = default;

  std::string evaporativeCoolerObjectType() const;
  bool setEvaporativeCoolerObjectType(const std::string& evaporativeCoolerObjectType);

  double foulingFactor() const;
  bool isFoulingFactorDefaulted() const;
  bool setFoulingFactor(double foulingFactor);
  void resetFoulingFactor();

  std::vector<std::string> evaporativeCoolerObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
