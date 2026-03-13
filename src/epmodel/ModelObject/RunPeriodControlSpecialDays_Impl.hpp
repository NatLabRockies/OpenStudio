/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLSPECIALDAYS_IMPL_HPP
#define EPMODEL_RUNPERIODCONTROLSPECIALDAYS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RunPeriodControlSpecialDays_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RunPeriodControlSpecialDays_Impl() override = default;

      std::vector<std::string> specialDayTypeValues() const;
      std::vector<std::string> validSpecialDayTypeValues() const;

      std::string startDate() const;
      bool setStartDate(const std::string& startDate);

      unsigned duration() const;
      bool setDuration(unsigned duration);

      std::string specialDayType() const;
      bool setSpecialDayType(const std::string& specialDayType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
