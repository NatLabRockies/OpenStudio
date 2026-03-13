/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDEVICETUBULAR_IMPL_HPP
#define EPMODEL_DAYLIGHTINGDEVICETUBULAR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API DaylightingDeviceTubular_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DaylightingDeviceTubular_Impl() override = default;

      double diameter() const;
      bool setDiameter(double diameter);

      double totalLength() const;
      bool setTotalLength(double totalLength);

      double effectiveThermalResistance() const;
      bool setEffectiveThermalResistance(double effectiveThermalResistance);
      bool isEffectiveThermalResistanceDefaulted() const;
      void resetEffectiveThermalResistance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
