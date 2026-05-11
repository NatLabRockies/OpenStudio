/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRGAP_IMPL_HPP
#define EPMODEL_AIRGAP_IMPL_HPP

#include "Material/Material_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirGap_Impl : public Material_Impl
    {
     public:
      using Material_Impl::Material_Impl;
      virtual ~AirGap_Impl() override = default;

      double thermalResistance() const;

      bool setThermalResistance(double thermalResistance);
      void resetThermalResistance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
