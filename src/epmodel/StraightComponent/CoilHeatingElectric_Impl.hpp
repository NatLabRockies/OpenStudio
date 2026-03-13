/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGELECTRIC_IMPL_HPP
#define EPMODEL_COILHEATINGELECTRIC_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API CoilHeatingElectric_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingElectric_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      double efficiency() const;
      bool isEfficiencyDefaulted() const;
      bool setEfficiency(double efficiency);
      void resetEfficiency();

      boost::optional<double> nominalCapacity() const;
      bool isNominalCapacityDefaulted() const;
      bool isNominalCapacityAutosized() const;
      bool setNominalCapacity(double nominalCapacity);
      void resetNominalCapacity();
      void autosizeNominalCapacity();
      boost::optional<double> autosizedNominalCapacity() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
