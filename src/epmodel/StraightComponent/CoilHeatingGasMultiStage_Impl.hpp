/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGGASMULTISTAGE_IMPL_HPP
#define EPMODEL_COILHEATINGGASMULTISTAGE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API CoilHeatingGasMultiStage_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilHeatingGasMultiStage_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> offCycleParasiticGasLoad() const;

  bool setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad);
  void resetOffCycleParasiticGasLoad();

  unsigned numberOfStages() const;
  bool setNumberOfStages(unsigned numberOfStages);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
