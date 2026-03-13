/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGDESUPERHEATER_IMPL_HPP
#define EPMODEL_COILHEATINGDESUPERHEATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API CoilHeatingDesuperheater_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingDesuperheater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      double heatReclaimRecoveryEfficiency() const;
      bool isHeatReclaimRecoveryEfficiencyDefaulted() const;
      bool setHeatReclaimRecoveryEfficiency(double heatReclaimRecoveryEfficiency);
      void resetHeatReclaimRecoveryEfficiency();

      double parasiticElectricLoad() const;
      bool isParasiticElectricLoadDefaulted() const;
      bool setParasiticElectricLoad(double parasiticElectricLoad);
      void resetParasiticElectricLoad();

      double onCycleParasiticElectricLoad() const;
      bool isOnCycleParasiticElectricLoadDefaulted() const;
      bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
      void resetOnCycleParasiticElectricLoad();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
