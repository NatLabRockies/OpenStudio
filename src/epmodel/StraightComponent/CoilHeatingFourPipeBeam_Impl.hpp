/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGFOURPIPEBEAM_IMPL_HPP
#define EPMODEL_COILHEATINGFOURPIPEBEAM_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Node;
  class PlantLoop;

  namespace detail {

    class EPMODEL_API CoilHeatingFourPipeBeam_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingFourPipeBeam_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      boost::optional<openstudio::epmodel::PlantLoop> plantLoop() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
