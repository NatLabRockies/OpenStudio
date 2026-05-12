/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOSCHEDULE_IMPL_HPP

#include "Schedule/Schedule_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToSchedule_Impl : public Schedule_Impl
    {
     public:
      using Schedule_Impl::Schedule_Impl;
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

     protected:
      boost::optional<unsigned> scheduleTypeLimitsFieldIndex() const override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
