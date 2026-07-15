/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTFROMVARIABLE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTFROMVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ExternalInterfaceFunctionalMockupUnitImportFromVariable_Impl() override = default;

      std::string outputVariableIndexKeyName() const;
      bool setOutputVariableIndexKeyName(const std::string& outputVariableIndexKeyName);

      std::string outputVariableName() const;
      bool setOutputVariableName(const std::string& outputVariableName);

      std::string fMUInstanceName() const;
      bool setFMUInstanceName(const std::string& fMUInstanceName);

      std::string fMUVariableName() const;
      bool setFMUVariableName(const std::string& fMUVariableName);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
