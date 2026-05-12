/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOSCHEDULE_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToSchedule_Impl : public Schedule_Impl
    {
     public:
      using Schedule_Impl::Schedule_Impl;
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

     protected:
      unsigned scheduleTypeLimitsFieldIndex() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
