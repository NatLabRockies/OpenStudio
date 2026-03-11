/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACBaseboardConvectiveElectric_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACBaseboardConvectiveElectric_Impl() override = default;

      boost::optional<double> nominalCapacity() const;
      bool isNominalCapacityAutosized() const;
      bool setNominalCapacity(double nominalCapacity);
      void autosizeNominalCapacity();

      boost::optional<double> efficiency() const;
      bool isEfficiencyDefaulted() const;
      bool setEfficiency(double efficiency);
      void resetEfficiency();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
