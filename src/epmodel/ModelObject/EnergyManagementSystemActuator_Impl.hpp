/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMACTUATOR_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMACTUATOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API EnergyManagementSystemActuator_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~EnergyManagementSystemActuator_Impl() override = default;

      boost::optional<ModelObject> actuatedComponent() const;
      bool setActuatedComponent(const ModelObject& actuatedComponent);

      std::string actuatedComponentControlType() const;
      bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

      std::string actuatedComponentType() const;
      bool setActuatedComponentType(const std::string& actuatedComponentType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
