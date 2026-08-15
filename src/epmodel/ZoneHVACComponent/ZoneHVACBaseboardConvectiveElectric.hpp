/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  namespace detail {
    class ZoneHVACBaseboardConvectiveElectric_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardConvectiveElectric : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACBaseboardConvectiveElectric(const Model& model);

    virtual ~ZoneHVACBaseboardConvectiveElectric() override = default;
    ZoneHVACBaseboardConvectiveElectric(const ZoneHVACBaseboardConvectiveElectric& other) = default;
    ZoneHVACBaseboardConvectiveElectric(ZoneHVACBaseboardConvectiveElectric&& other) = default;
    ZoneHVACBaseboardConvectiveElectric& operator=(const ZoneHVACBaseboardConvectiveElectric&) = default;
    ZoneHVACBaseboardConvectiveElectric& operator=(ZoneHVACBaseboardConvectiveElectric&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar and Schedule Parity. The canonical availability relationship and two scalar field groups are exposed, and the
    //   remaining public surface is intentionally small.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardConvectiveElectric.
    // - Implemented Parity: `availabilitySchedule` and its validated setter preserve the required canonical relationship; `nominalCapacity`
    //   and `efficiency` map directly to the matching EnergyPlus ZoneHVAC:Baseboard:Convective:Electric fields, including the
    //   autosize/default helpers.
    // - Documented Delta: The wrapper relies on the established ZoneHVACComponent thermal-zone attachment surface and adds no type-local
    //   topology behavior.
    // - Field/Storage Mapping: The schedule pointer and scalar values are stored directly in the matching EnergyPlus fields, with no child
    //   objects to synchronize.
    // - Evidence: `src/model/ZoneHVACBaseboardConvectiveElectric.hpp`, `src/model/ZoneHVACBaseboardConvectiveElectric.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardConvectiveElectric.cpp`, and `src/epmodel/test/ZoneHVACBaseboardConvectiveElectric_GTest.cpp`.
    // - Remaining Parity Work: None within the current canonical public surface.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    /** @name Nominal capacity accessors */
    //@{
    boost::optional<double> nominalCapacity() const;
    bool isNominalCapacityAutosized() const;
    bool setNominalCapacity(double nominalCapacity);
    void autosizeNominalCapacity();
    //@}

    /** @name Efficiency accessors */
    //@{
    boost::optional<double> efficiency() const;
    bool isEfficiencyDefaulted() const;
    bool setEfficiency(double efficiency);
    void resetEfficiency();
    //@}

   protected:
    using ImplType = detail::ZoneHVACBaseboardConvectiveElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardConvectiveElectric(std::shared_ptr<detail::ZoneHVACBaseboardConvectiveElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
