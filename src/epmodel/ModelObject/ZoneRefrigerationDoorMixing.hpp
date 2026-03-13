/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEREFRIGERATIONDOORMIXING_HPP
#define EPMODEL_ZONEREFRIGERATIONDOORMIXING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
class Model;

namespace epmodel {

  namespace detail {
    class ZoneRefrigerationDoorMixing_Impl;
  }

  class EPMODEL_API ZoneRefrigerationDoorMixing : public ModelObject
  {
   public:
    explicit ZoneRefrigerationDoorMixing(const Model& model);
    virtual ~ZoneRefrigerationDoorMixing() override = default;
    ZoneRefrigerationDoorMixing(const ZoneRefrigerationDoorMixing& other) = default;
    ZoneRefrigerationDoorMixing(ZoneRefrigerationDoorMixing&& other) = default;
    ZoneRefrigerationDoorMixing& operator=(const ZoneRefrigerationDoorMixing&) = default;
    ZoneRefrigerationDoorMixing& operator=(ZoneRefrigerationDoorMixing&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> doorProtectionTypeValues();

    // Schema Alignment Notes:
    // - API: doorHeight(), doorArea(), and doorProtectionType() wrap the EnergyPlus ZoneRefrigerationDoorMixing
    //   fields Door Height, Door Area, and Door Protection Type.
    // - Field Mapping: the Zone/Space Name 1, Zone/Space Name 2, and Schedule Name relationships remain object-list
    //   targets and are intentionally excluded from this scalar-only API.
    double doorHeight() const;
    bool isDoorHeightDefaulted() const;
    bool setDoorHeight(double doorHeight);
    void resetDoorHeight();

    double doorArea() const;
    bool isDoorAreaDefaulted() const;
    bool setDoorArea(double doorArea);
    void resetDoorArea();

    std::string doorProtectionType() const;
    bool isDoorProtectionTypeDefaulted() const;
    bool setDoorProtectionType(const std::string& doorProtectionType);
    void resetDoorProtectionType();

   protected:
    using ImplType = detail::ZoneRefrigerationDoorMixing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneRefrigerationDoorMixing(std::shared_ptr<detail::ZoneRefrigerationDoorMixing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
