/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULETYPELIMITS_IMPL_HPP
#define EPMODEL_SCHEDULETYPELIMITS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ScheduleTypeLimits_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ScheduleTypeLimits_Impl() override = default;

      boost::optional<double> lowerLimitValue() const;
      bool setLowerLimitValue(double lowerLimitValue);
      void resetLowerLimitValue();

      boost::optional<double> upperLimitValue() const;
      bool setUpperLimitValue(double upperLimitValue);
      void resetUpperLimitValue();

      std::vector<std::string> numericTypeValues() const;
      boost::optional<std::string> numericType() const;
      bool setNumericType(const std::string& numericType);
      void resetNumericType();

      std::vector<std::string> unitTypeValues() const;
      std::string unitType() const;
      bool isUnitTypeDefaulted() const;
      bool setUnitType(const std::string& unitType);
      void resetUnitType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
