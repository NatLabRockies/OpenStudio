/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILUSERDEFINED_IMPL_HPP
#define EPMODEL_COILUSERDEFINED_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilUserDefined_Impl : public WaterToAirComponent_Impl
{
 public:
  using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
  virtual ~CoilUserDefined_Impl() override = default;

  unsigned airInletPort() const override;
  unsigned airOutletPort() const override;
  unsigned waterInletPort() const override;
  unsigned waterOutletPort() const override;

  int numberofAirConnections() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
