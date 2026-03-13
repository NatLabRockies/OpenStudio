/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYPHASECHANGE_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYPHASECHANGE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API MaterialPropertyPhaseChange_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~MaterialPropertyPhaseChange_Impl() override = default;

      /** Temperature coefficient for thermal conductivity. */
      double temperatureCoefficientforThermalConductivity() const;
      bool isTemperatureCoefficientforThermalConductivityDefaulted() const;
      bool setTemperatureCoefficientforThermalConductivity(double temperatureCoefficientforThermalConductivity);
      void resetTemperatureCoefficientforThermalConductivity();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
