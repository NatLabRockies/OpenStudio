/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLEINDEPENDENTVARIABLE_IMPL_HPP
#define EPMODEL_TABLEINDEPENDENTVARIABLE_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class TableLookup;

  namespace detail {

    class EPMODEL_API TableIndependentVariable_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~TableIndependentVariable_Impl() override = default;

      std::string interpolationMethod() const;
      bool isInterpolationMethodDefaulted() const;
      bool setInterpolationMethod(const std::string& interpolationMethod);
      void resetInterpolationMethod();

      std::string extrapolationMethod() const;
      bool isExtrapolationMethodDefaulted() const;
      bool setExtrapolationMethod(const std::string& extrapolationMethod);
      void resetExtrapolationMethod();

      boost::optional<double> minimumValue() const;
      bool setMinimumValue(double minimumValue);
      void resetMinimumValue();

      boost::optional<double> maximumValue() const;
      bool setMaximumValue(double maximumValue);
      void resetMaximumValue();

      boost::optional<double> normalizationReferenceValue() const;
      bool setNormalizationReferenceValue(double normalizationReferenceValue);
      void resetNormalizationReferenceValue();

      std::string unitType() const;
      bool isUnitTypeDefaulted() const;
      bool setUnitType(const std::string& unitType);
      void resetUnitType();

      std::vector<TableLookup> tableLookups() const;

      bool addValue(double value);
      bool removeValue(unsigned groupIndex);
      void removeAllValues();
      std::vector<double> values() const;
      bool setValues(const std::vector<double>& values);
      unsigned numberofValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
