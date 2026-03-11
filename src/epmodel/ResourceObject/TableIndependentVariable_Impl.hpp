/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLEINDEPENDENTVARIABLE_IMPL_HPP
#define EPMODEL_TABLEINDEPENDENTVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API TableIndependentVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
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

      boost::optional<std::string> externalFileName() const;
      bool setExternalFileName(const std::string& externalFileName);
      void resetExternalFileName();

      boost::optional<int> externalFileColumnNumber() const;
      bool setExternalFileColumnNumber(int externalFileColumnNumber);
      void resetExternalFileColumnNumber();

      boost::optional<int> externalFileStartingRowNumber() const;
      bool setExternalFileStartingRowNumber(int externalFileStartingRowNumber);
      void resetExternalFileStartingRowNumber();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
