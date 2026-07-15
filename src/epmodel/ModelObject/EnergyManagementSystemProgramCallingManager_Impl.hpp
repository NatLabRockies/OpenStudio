/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_IMPL_HPP
#define EPMODEL_ENERGYMANAGEMENTSYSTEMPROGRAMCALLINGMANAGER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class EnergyManagementSystemProgram;

  namespace detail {

    class EPMODEL_API EnergyManagementSystemProgramCallingManager_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~EnergyManagementSystemProgramCallingManager_Impl() override = default;

      std::vector<std::string> validCallingPointValues() const;

      std::string callingPoint() const;
      bool setCallingPoint(const std::string& callingPoint);

      std::vector<EnergyManagementSystemProgram> programs() const;
      boost::optional<EnergyManagementSystemProgram> getProgram(unsigned index) const;

      bool eraseProgram(unsigned index);
      void erasePrograms();
      bool addProgram(const EnergyManagementSystemProgram& program);
      bool setProgram(const EnergyManagementSystemProgram& program, unsigned index);
      bool setPrograms(const std::vector<EnergyManagementSystemProgram>& programs);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
