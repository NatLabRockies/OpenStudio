/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEAIRBALANCEOUTDOORAIR_HPP
#define EPMODEL_ZONEAIRBALANCEOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
class Model;

namespace epmodel {

  namespace detail {
    class ZoneAirBalanceOutdoorAir_Impl;
  }

  class EPMODEL_API ZoneAirBalanceOutdoorAir : public ModelObject
  {
   public:
    explicit ZoneAirBalanceOutdoorAir(const Model& model);

    virtual ~ZoneAirBalanceOutdoorAir() override = default;
    ZoneAirBalanceOutdoorAir(const ZoneAirBalanceOutdoorAir& other) = default;
    ZoneAirBalanceOutdoorAir(ZoneAirBalanceOutdoorAir&& other) = default;
    ZoneAirBalanceOutdoorAir& operator=(const ZoneAirBalanceOutdoorAir&) = default;
    ZoneAirBalanceOutdoorAir& operator=(ZoneAirBalanceOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists so IDD-derived scalar naming is preserved for this type.
    // - Field Mapping: airBalanceMethod() wraps the Air Balance Method field and inducedOutdoorAirDueToUnbalancedDuctLeakage()
    //   wraps the Induced Outdoor Air Due to Unbalanced Duct Leakage field on ZoneAirBalance:OutdoorAir.
    // - Field Mapping: Zone Name and Induced Outdoor Air Schedule Name remain object-list/schedule relationships and
    //   are intentionally excluded from the scalar API.
    // - TODO(parity): Add relationship helpers once downstream needs emerge.
    std::string airBalanceMethod() const;
    bool isAirBalanceMethodDefaulted() const;
    bool setAirBalanceMethod(const std::string& airBalanceMethod);
    void resetAirBalanceMethod();

    double inducedOutdoorAirDueToUnbalancedDuctLeakage() const;
    bool isInducedOutdoorAirDueToUnbalancedDuctLeakageDefaulted() const;
    bool setInducedOutdoorAirDueToUnbalancedDuctLeakage(double inducedOutdoorAirDueToUnbalancedDuctLeakage);
    void resetInducedOutdoorAirDueToUnbalancedDuctLeakage();

    static std::vector<std::string> airBalanceMethodValues();

   protected:
    using ImplType = detail::ZoneAirBalanceOutdoorAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneAirBalanceOutdoorAir(std::shared_ptr<detail::ZoneAirBalanceOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
