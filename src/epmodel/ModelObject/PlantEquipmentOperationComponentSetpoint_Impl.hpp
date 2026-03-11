/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTEQUIPMENTOPERATIONCOMPONENTSETPOINT_IMPL_HPP
#define EPMODEL_PLANTEQUIPMENTOPERATIONCOMPONENTSETPOINT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {

class IdfExtensibleGroup;

namespace epmodel {
  namespace detail {

    class EPMODEL_API PlantEquipmentOperationComponentSetpoint_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PlantEquipmentOperationComponentSetpoint_Impl() override = default;

      boost::optional<double> component1FlowRate() const;
      bool isComponent1FlowRateAutosized() const;
      bool setComponent1FlowRate(double component1FlowRate);
      void autosizeComponent1FlowRate();
      boost::optional<double> autosizedComponent1FlowRate() const;

      std::string component1OperationType() const;
      bool setComponent1OperationType(const std::string& component1OperationType);

     private:
      boost::optional<IdfExtensibleGroup> componentGroup() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
