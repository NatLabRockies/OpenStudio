/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTLIST_HPP
#define EPMODEL_ZONEHVACEQUIPMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACEquipmentList_Impl;
  }

  class EPMODEL_API ZoneHVACEquipmentList : public ModelObject
  {
   public:
    explicit ZoneHVACEquipmentList(const Model& model);

    virtual ~ZoneHVACEquipmentList() override = default;
    ZoneHVACEquipmentList(const ZoneHVACEquipmentList& other) = default;
    ZoneHVACEquipmentList(ZoneHVACEquipmentList&& other) = default;
    ZoneHVACEquipmentList& operator=(const ZoneHVACEquipmentList&) = default;
    ZoneHVACEquipmentList& operator=(ZoneHVACEquipmentList&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> loadDistributionSchemeValues();
    static std::vector<std::string> validLoadDistributionSchemeValues();

    // Schema Alignment Notes:
    // - API: loadDistributionScheme()/setLoadDistributionScheme()/resetLoadDistributionScheme() map directly to the E+ ZoneHVAC:EquipmentList
    //   field 'Load Distribution Scheme'.
    // - Field Mapping: default semantics are preserved via isLoadDistributionSchemeDefaulted() and resetLoadDistributionScheme().
    std::string loadDistributionScheme() const;
    bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
    bool isLoadDistributionSchemeDefaulted() const;
    void resetLoadDistributionScheme();

   protected:
    using ImplType = detail::ZoneHVACEquipmentList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class openstudio::epmodel::Model;

    explicit ZoneHVACEquipmentList(std::shared_ptr<detail::ZoneHVACEquipmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
