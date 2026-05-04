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

  class EPMODEL_API ZoneAirContaminantBalance : public ModelObject
  {
   public:
    virtual ~ZoneAirContaminantBalance() override = default;
    ZoneAirContaminantBalance(const ZoneAirContaminantBalance& other) = default;
    ZoneAirContaminantBalance(ZoneAirContaminantBalance&& other) = default;
    ZoneAirContaminantBalance& operator=(const ZoneAirContaminantBalance&) = default;
    ZoneAirContaminantBalance& operator=(ZoneAirContaminantBalance&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve the openstudio::model carbon dioxide boolean accessors while mapping to the EnergyPlus ZoneAirContaminantBalance
    //   fields written by ForwardTranslateZoneAirContaminantBalance.cpp.
    // - Field Mapping: Generic contaminant concentration is an additional EnergyPlus scalar with the usual Yes/No semantics.
    // - Field Mapping: Outdoor Carbon Dioxide/Generic Contaminant Schedule Name fields remain object-list relationships and are intentionally
    //   excluded from this scalar-only scaffold.
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
