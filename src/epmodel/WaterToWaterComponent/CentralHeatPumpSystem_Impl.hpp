/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CENTRALHEATPUMPSYSTEM_IMPL_HPP
#define EPMODEL_CENTRALHEATPUMPSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CentralHeatPumpSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CentralHeatPumpSystem_Impl() override = default;

      std::vector<std::string> controlMethodValues() const;

      std::string controlMethod() const;
      bool setControlMethod(const std::string& controlMethod);

      double ancillaryPower() const;
      bool setAncillaryPower(double ancillaryPower);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
