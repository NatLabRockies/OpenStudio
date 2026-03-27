/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardConvectiveElectric_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACBaseboardConvectiveElectric_Impl() override = default;

      boost::optional<double> nominalCapacity() const;
      bool setNominalCapacity(double nominalCapacity);
      bool isNominalCapacityAutosized() const;
      void autosizeNominalCapacity();

      boost::optional<double> efficiency() const;
      bool setEfficiency(double efficiency);
      bool isEfficiencyDefaulted() const;
      void resetEfficiency();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
