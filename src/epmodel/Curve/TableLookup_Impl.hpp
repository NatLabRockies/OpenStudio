/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLELOOKUP_IMPL_HPP
#define EPMODEL_TABLELOOKUP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API TableLookup_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~TableLookup_Impl() override = default;

      std::string normalizationMethod() const;
      double normalizationDivisor() const;

      boost::optional<double> minimumOutput() const;
      boost::optional<double> maximumOutput() const;

      std::string outputUnitType() const;

      bool setNormalizationMethod(const std::string& normalizationMethod);
      bool setNormalizationDivisor(double normalizationDivisor);
      bool setMinimumOutput(double minimumOutput);
      void resetMinimumOutput();
      bool setMaximumOutput(double maximumOutput);
      void resetMaximumOutput();
      bool setOutputUnitType(const std::string& outputUnitType);

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
