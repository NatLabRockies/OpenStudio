/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRCONTAMINANTBALANCE_HPP
#define EPMODEL_ZONEAIRCONTAMINANTBALANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneAirContaminantBalance_Impl;
  }

  /** \brief ZoneAirContaminantBalance.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#zoneaircontaminantbalance,ZoneAirContaminantBalance}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneAirContaminantBalance</code>. EPModel adds <code>genericContaminantConcentration()</code> and its setter/reset/default helpers. Model's <code>outdoorCarbonDioxideSchedule()</code>, <code>setOutdoorCarbonDioxideSchedule()</code>, and <code>resetOutdoorCarbonDioxideSchedule()</code> are not available.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneAirContaminantBalance : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~ZoneAirContaminantBalance() override = default;
    ZoneAirContaminantBalance(const ZoneAirContaminantBalance& other) = default;
    ZoneAirContaminantBalance(ZoneAirContaminantBalance&& other) = default;
    ZoneAirContaminantBalance& operator=(const ZoneAirContaminantBalance&) = default;
    ZoneAirContaminantBalance& operator=(ZoneAirContaminantBalance&&) = default;

    static IddObjectType iddObjectType();
    bool carbonDioxideConcentration() const;
    bool isCarbonDioxideConcentrationDefaulted() const;
    bool setCarbonDioxideConcentration(bool carbonDioxideConcentration);
    void setCarbonDioxideConcentrationNoFail(bool carbonDioxideConcentration);
    void resetCarbonDioxideConcentration();

    bool genericContaminantConcentration() const;
    bool isGenericContaminantConcentrationDefaulted() const;
    bool setGenericContaminantConcentration(bool genericContaminantConcentration);
    void resetGenericContaminantConcentration();

   protected:
    explicit ZoneAirContaminantBalance(const Model& model);

    using ImplType = detail::ZoneAirContaminantBalance_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneAirContaminantBalance(std::shared_ptr<detail::ZoneAirContaminantBalance_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
