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
    // - Status: Scalar Parity. The two scalar field groups are exposed with canonical-style accessors, and the remaining public surface is intentionally small.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardConvectiveElectric.
    // - Implemented Parity: `nominalCapacity` and `efficiency` map directly to the matching EnergyPlus ZoneHVAC:Baseboard:Convective:Electric fields, including the autosize/default helpers.
    // - Documented Delta: There are no meaningful relationship or topology helpers on this wrapper yet, so the public API stays scalar-only.
    // - Field/Storage Mapping: EnergyPlus-backed storage is read and written through the scalar field accessors, with no additional child objects to synchronize.
    // - Evidence: `src/model/ZoneHVACBaseboardConvectiveElectric.hpp`, `src/model/ZoneHVACBaseboardConvectiveElectric.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardConvectiveElectric.cpp`, and `src/epmodel/test/ZoneHVACBaseboardConvectiveElectric_GTest.cpp`.
    // - Remaining Parity Work: None beyond keeping the scalar API aligned with future canonical changes.
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
