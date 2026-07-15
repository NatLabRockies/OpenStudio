/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ExternalInterface_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ExternalInterface_Impl() override = default;

      std::string nameofExternalInterface() const;
      bool setNameofExternalInterface(const std::string& nameofExternalInterface);

      std::vector<std::string> nameofExternalInterfaceValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
