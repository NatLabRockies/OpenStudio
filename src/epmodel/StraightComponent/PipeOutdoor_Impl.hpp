/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEOUTDOOR_IMPL_HPP
#define EPMODEL_PIPEOUTDOOR_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API PipeOutdoor_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PipeOutdoor_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      /** @name Pipe Inside Diameter */
      //@{
      double pipeInsideDiameter() const;
      bool setPipeInsideDiameter(double pipeInsideDiameter);
      //@}

      /** @name Pipe Length */
      //@{
      double pipeLength() const;
      bool setPipeLength(double pipeLength);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
