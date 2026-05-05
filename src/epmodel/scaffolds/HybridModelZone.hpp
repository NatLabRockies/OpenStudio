/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HYBRIDMODELZONE_HPP
#define EPMODEL_HYBRIDMODELZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HybridModelZone_Impl;
  }

  class EPMODEL_API HybridModelZone : public ModelObject
  {
   public:
    explicit HybridModelZone(const Model& model);

    virtual ~HybridModelZone() override = default;
    HybridModelZone(const HybridModelZone& other) = default;
    HybridModelZone(HybridModelZone&& other) = default;
    HybridModelZone& operator=(const HybridModelZone&) = default;
    HybridModelZone& operator=(HybridModelZone&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: calculateZoneInternalThermalMass, calculateZoneAirInfiltrationRate,
    //   calculateZonePeopleCount, beginMonth, beginDayofMonth, endMonth, and endDayofMonth map
    //   directly to EnergyPlus HybridModel:Zone scalar fields.
    // - Field Mapping: Zone Name and all schedule name fields are object-list relationship fields
    //   and are intentionally excluded from scalar accessors in this scaffold phase.
    // - ForwardTranslator evidence: no OpenStudio model ForwardTranslator path exists for this
    //   EP-only object, so direct IDD scalar mapping is applied.
    // - TODO(parity): Add typed relationship APIs after scalar scaffold saturation.
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

   protected:
    using ImplType = detail::HybridModelZone_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HybridModelZone(std::shared_ptr<detail::HybridModelZone_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
