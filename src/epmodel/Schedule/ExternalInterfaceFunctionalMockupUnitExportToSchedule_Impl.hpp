/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl() override = default;

      /** @name FMU Variable Name */
      //@{
      std::string fMUVariableName() const;
      bool setFMUVariableName(const std::string& fMUVariableName);
      //@}

      /** @name Initial Value */
      //@{
      boost::optional<double> initialValue() const;
      bool setInitialValue(double initialValue);
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
