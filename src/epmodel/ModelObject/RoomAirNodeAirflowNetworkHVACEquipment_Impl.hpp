/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORKHVACEQUIPMENT_IMPL_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORKHVACEQUIPMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <utilities/idf/IdfExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoomAirNodeAirflowNetworkHVACEquipment_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RoomAirNodeAirflowNetworkHVACEquipment_Impl() override = default;

      boost::optional<double> fractionOfOutputOrSupplyAirFromHVACEquipment1() const;
      bool setFractionOfOutputOrSupplyAirFromHVACEquipment1(double fractionOfOutputOrSupplyAirFromHVACEquipment1);
      void resetFractionOfOutputOrSupplyAirFromHVACEquipment1();

      boost::optional<double> fractionOfInputOrReturnAirToHVACEquipment1() const;
      bool setFractionOfInputOrReturnAirToHVACEquipment1(double fractionOfInputOrReturnAirToHVACEquipment1);
      void resetFractionOfInputOrReturnAirToHVACEquipment1();

      boost::optional<openstudio::IdfExtensibleGroup> equipmentGroup() const;
      openstudio::IdfExtensibleGroup ensureEquipmentGroup() const;
      void ensureRelationshipFields(openstudio::IdfExtensibleGroup& group) const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
