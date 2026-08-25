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

/** \brief An electric convective baseboard heater serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvacbaseboardconvectiveelectric,ZoneHVAC:Baseboard:Convective:Electric}
 *
 * \par Important behavior
 * Availability, nominal-capacity, efficiency, autosizing, and thermal-zone attachment methods are available.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACBaseboardConvectiveElectric</code>.
 * Model also provides <code>autosizedNominalCapacity()</code> and its inherited
 * thermal-zone convenience methods; EPModel exposes the autosize operation but
 * does not provide the SQL-backed result query.
 *
 * \par Known limitations
 * No additional type-specific topology is represented beyond shared zone-equipment attachment, and SQL sizing results are unavailable.
 */
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
