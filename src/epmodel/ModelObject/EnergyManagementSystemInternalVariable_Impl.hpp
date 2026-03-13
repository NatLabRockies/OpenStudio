/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMINTERNALVARIABLE_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMINTERNALVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API EnergyManagementSystemInternalVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~EnergyManagementSystemInternalVariable_Impl() override = default;

      // Internal Data Index Key Name
      std::string internalDataIndexKeyName() const;
      bool setInternalDataIndexKeyName(const std::string& internalDataIndexKeyName);
      void resetInternalDataIndexKeyName();

      // Internal Data Type
      std::string internalDataType() const;
      bool setInternalDataType(const std::string& internalDataType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
