/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEINDOOR_IMPL_HPP
#define EPMODEL_PIPEINDOOR_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API PipeIndoor_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~PipeIndoor_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  std::string environmentType() const;
  bool setEnvironmentType(const std::string& environmentType);

  double pipeInsideDiameter() const;
  bool setPipeInsideDiameter(double pipeInsideDiameter);

  double pipeLength() const;
  bool setPipeLength(double pipeLength);

  std::vector<std::string> environmentTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
