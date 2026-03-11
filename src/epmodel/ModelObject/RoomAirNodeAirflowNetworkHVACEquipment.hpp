/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORKHVACEQUIPMENT_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORKHVACEQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirNodeAirflowNetworkHVACEquipment_Impl;
  }

  class EPMODEL_API RoomAirNodeAirflowNetworkHVACEquipment : public ModelObject
  {
   public:
    explicit RoomAirNodeAirflowNetworkHVACEquipment(const Model& model);

    virtual ~RoomAirNodeAirflowNetworkHVACEquipment() override = default;
    RoomAirNodeAirflowNetworkHVACEquipment(const RoomAirNodeAirflowNetworkHVACEquipment& other) = default;
    RoomAirNodeAirflowNetworkHVACEquipment(RoomAirNodeAirflowNetworkHVACEquipment&& other) = default;
    RoomAirNodeAirflowNetworkHVACEquipment& operator=(const RoomAirNodeAirflowNetworkHVACEquipment&) = default;
    RoomAirNodeAirflowNetworkHVACEquipment& operator=(RoomAirNodeAirflowNetworkHVACEquipment&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists so the class/accessor names mirror the IDD entry RoomAir:Node:AirflowNetwork:HVACEquipment.
    // - Field Mapping: fractionOfOutputOrSupplyAirFromHVACEquipment1 maps to EnergyPlus RoomAir:Node:AirflowNetwork:HVACEquipment
    //   Fraction of Output or Supply Air from HVAC Equipment 1.
    // - Field Mapping: fractionOfInputOrReturnAirToHVACEquipment1 maps to EnergyPlus RoomAir:Node:AirflowNetwork:HVACEquipment Fraction
    //   of Input or Return Air to HVAC Equipment 1.
    // - Field Mapping: Name and the extensible ZoneHVAC or Air Terminal Equipment Object Type/Name fields remain relationship-like and
    //   are intentionally excluded from this scalar-only pass (base ModelObject name APIs still expose the Name field).
    // - TODO(parity): Add typed helpers for the extensible equipment relationships after scalar saturation.
    boost::optional<double> fractionOfOutputOrSupplyAirFromHVACEquipment1() const;
    bool setFractionOfOutputOrSupplyAirFromHVACEquipment1(double fractionOfOutputOrSupplyAirFromHVACEquipment1);
    void resetFractionOfOutputOrSupplyAirFromHVACEquipment1();

    boost::optional<double> fractionOfInputOrReturnAirToHVACEquipment1() const;
    bool setFractionOfInputOrReturnAirToHVACEquipment1(double fractionOfInputOrReturnAirToHVACEquipment1);
    void resetFractionOfInputOrReturnAirToHVACEquipment1();

   protected:
    using ImplType = detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirNodeAirflowNetworkHVACEquipment(std::shared_ptr<detail::RoomAirNodeAirflowNetworkHVACEquipment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
