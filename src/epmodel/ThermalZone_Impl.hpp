/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALZONE_IMPL_HPP
#define EPMODEL_THERMALZONE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ZoneHVACEquipmentConnections;
  class ZoneHVACEquipmentList;
  class SizingZone;

  namespace detail {

    class EPMODEL_API ThermalZone_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ThermalZone_Impl() override = default;

      boost::optional<openstudio::epmodel::ZoneHVACEquipmentConnections> zoneHVACEquipmentConnections() const;
      openstudio::epmodel::ZoneHVACEquipmentConnections getZoneHVACEquipmentConnections();

      boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> zoneHVACEquipmentList() const;

      boost::optional<openstudio::epmodel::SizingZone> optionalSizingZone() const;
      openstudio::epmodel::SizingZone sizingZone();

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
