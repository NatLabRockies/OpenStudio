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

      std::vector<std::string> flowDirectionValues() const;

      double xPosition() const;
      bool setXPosition(double xPosition);

      double yPosition() const;
      bool setYPosition(double yPosition);

      std::string flowDirection() const;
      bool setFlowDirection(const std::string& flowDirection);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
