/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HYBRIDMODELZONE_IMPL_HPP
#define EPMODEL_HYBRIDMODELZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HybridModelZone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HybridModelZone_Impl() override = default;

      bool calculateZoneInternalThermalMass() const;
      bool isCalculateZoneInternalThermalMassDefaulted() const;
      bool setCalculateZoneInternalThermalMass(bool calculateZoneInternalThermalMass);
      void resetCalculateZoneInternalThermalMass();

      bool calculateZoneAirInfiltrationRate() const;
      bool isCalculateZoneAirInfiltrationRateDefaulted() const;
      bool setCalculateZoneAirInfiltrationRate(bool calculateZoneAirInfiltrationRate);
      void resetCalculateZoneAirInfiltrationRate();

      bool calculateZonePeopleCount() const;
      bool isCalculateZonePeopleCountDefaulted() const;
      bool setCalculateZonePeopleCount(bool calculateZonePeopleCount);
      void resetCalculateZonePeopleCount();

      int beginMonth() const;
      bool setBeginMonth(int beginMonth);

      int beginDayofMonth() const;
      bool setBeginDayofMonth(int beginDayofMonth);

      int endMonth() const;
      bool setEndMonth(int endMonth);

      int endDayofMonth() const;
      bool setEndDayofMonth(int endDayofMonth);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
