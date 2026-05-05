/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API EnergyManagementSystemMeteredOutputVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~EnergyManagementSystemMeteredOutputVariable_Impl() override = default;

      std::vector<std::string> updateFrequencyValues() const;
      std::vector<std::string> resourceTypeValues() const;
      std::vector<std::string> groupTypeValues() const;
      std::vector<std::string> endUseCategoryValues() const;

      std::string emsVariableName() const;
      bool setEMSVariableName(const std::string& eMSVariableName);

      std::string updateFrequency() const;
      bool setUpdateFrequency(const std::string& updateFrequency);

      std::string resourceType() const;
      bool setResourceType(const std::string& resourceType);

      std::string groupType() const;
      bool setGroupType(const std::string& groupType);

      std::string endUseCategory() const;
      bool setEndUseCategory(const std::string& endUseCategory);

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      std::string units() const;
      bool setUnits(const std::string& units);
      void resetUnits();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
