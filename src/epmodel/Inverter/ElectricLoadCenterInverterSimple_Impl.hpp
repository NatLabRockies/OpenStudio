/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERSIMPLE_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERSIMPLE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ElectricLoadCenterInverterSimple_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ElectricLoadCenterInverterSimple_Impl() override = default;

      boost::optional<double> radiativeFraction() const;
      bool setRadiativeFraction(double radiativeFraction);
      void resetRadiativeFraction();

      boost::optional<double> inverterEfficiency() const;
      bool setInverterEfficiency(double inverterEfficiency);
      void resetInverterEfficiency();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
