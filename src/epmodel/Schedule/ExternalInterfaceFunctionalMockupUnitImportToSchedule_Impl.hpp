/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl() override = default;

      /** @name FMU Instance Name */
      //@{
      std::string fMUInstanceName() const;
      bool setFMUInstanceName(const std::string& fMUInstanceName);
      //@}

      /** @name FMU Variable Name */
      //@{
      std::string fMUVariableName() const;
      bool setFMUVariableName(const std::string& fMUVariableName);
      //@}

      /** @name Initial Value */
      //@{
      double initialValue() const;
      bool setInitialValue(double initialValue);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
