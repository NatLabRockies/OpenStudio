/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGESIZING_IMPL_HPP
#define EPMODEL_THERMALSTORAGESIZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ThermalStorageSizing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalStorageSizing_Impl() override = default;

      /** @name On-peak period start time accessors */
      //@{
      double onPeakPeriodStartTime() const;
      bool setOnPeakPeriodStartTime(double onPeakPeriodStartTime);
      //@}

      /** @name On-peak period end time accessors */
      //@{
      double onPeakPeriodEndTime() const;
      bool setOnPeakPeriodEndTime(double onPeakPeriodEndTime);
      //@}

      /** @name Sizing factor accessors */
      //@{
      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);
      bool isSizingFactorDefaulted() const;
      void resetSizingFactor();
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
