/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRGAP_IMPL_HPP
#define EPMODEL_AIRGAP_IMPL_HPP

#include "OpaqueMaterial/OpaqueMaterial_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirGap_Impl : public OpaqueMaterial_Impl
    {
     public:
      using OpaqueMaterial_Impl::OpaqueMaterial_Impl;
      virtual ~AirGap_Impl() override = default;

      double thermalResistance() const override;

      bool setThermalResistance(double thermalResistance) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
