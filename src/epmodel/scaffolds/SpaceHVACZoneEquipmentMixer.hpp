/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEHVACZONEEQUIPMENTMIXER_HPP
#define EPMODEL_SPACEHVACZONEEQUIPMENTMIXER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SpaceHVACZoneEquipmentMixer_Impl;
  }

  class EPMODEL_API SpaceHVACZoneEquipmentMixer : public ModelObject
  {
   public:
    explicit SpaceHVACZoneEquipmentMixer(const Model& model);

    virtual ~SpaceHVACZoneEquipmentMixer() override = default;
    SpaceHVACZoneEquipmentMixer(const SpaceHVACZoneEquipmentMixer& other) = default;
    SpaceHVACZoneEquipmentMixer(SpaceHVACZoneEquipmentMixer&& other) = default;
    SpaceHVACZoneEquipmentMixer& operator=(const SpaceHVACZoneEquipmentMixer&) = default;
    SpaceHVACZoneEquipmentMixer& operator=(SpaceHVACZoneEquipmentMixer&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Zone Name, Zone Equipment Inlet Node Name, Space 1 Name, and extensible Space n Node Name
    //   fields are relationship-like link fields and excluded from scalar accessors.
    // - Field Mapping: Extensible Space Name / Space Fraction / Space Node Name groups are intentionally kept on
    //   generic extensible APIs in this scalar-only pass.
    // - TODO(parity): Add relationship/non-scalar extensible helper APIs incrementally after scalar saturation.

   protected:
    using ImplType = detail::SpaceHVACZoneEquipmentMixer_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceHVACZoneEquipmentMixer(std::shared_ptr<detail::SpaceHVACZoneEquipmentMixer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
