/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_HPP
#define EPMODEL_ZONEHVACBASEBOARDCONVECTIVEELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACBaseboardConvectiveElectric_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardConvectiveElectric : public ModelObject
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
    // - API: nominalCapacity/isNominalCapacityAutosized/autosizeNominalCapacity map to EnergyPlus ZoneHVAC:Baseboard:Convective:Electric Heating Design Capacity via ForwardTranslateZoneHVACBaseboardConvectiveElectric.cpp.
    // - API: efficiency/isEfficiencyDefaulted/resetEfficiency map to the EnergyPlus Efficiency field (default 1.0).
    // - Availability Schedule is a relationship field and remains excluded from scalar accessors until a relationship API exists.
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
