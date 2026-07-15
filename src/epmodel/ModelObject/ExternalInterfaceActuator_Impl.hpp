/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEACTUATOR_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEACTUATOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ExternalInterfaceActuator_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ExternalInterfaceActuator_Impl() override = default;

      std::string actuatedComponentControlType() const;
      bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

      std::string actuatedComponentType() const;
      bool setActuatedComponentType(const std::string& actuatedComponentType);

      boost::optional<double> optionalInitialValue() const;
      bool setOptionalInitialValue(double optionalInitialValue);
      void resetOptionalInitialValue();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
