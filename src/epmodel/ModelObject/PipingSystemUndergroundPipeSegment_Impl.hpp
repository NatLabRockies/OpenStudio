/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPESEGMENT_IMPL_HPP
#define EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPESEGMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API PipingSystemUndergroundPipeSegment_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~PipingSystemUndergroundPipeSegment_Impl() override = default;

  double xPosition() const;
  double yPosition() const;
  std::string flowDirection() const;

  bool setXPosition(double xPosition);
  bool setYPosition(double yPosition);
  bool setFlowDirection(const std::string& flowDirection);

  std::vector<std::string> flowDirectionValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
