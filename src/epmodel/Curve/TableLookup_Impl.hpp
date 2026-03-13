/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLELOOKUP_IMPL_HPP
#define EPMODEL_TABLELOOKUP_IMPL_HPP

#include "Curve/Curve_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class TableIndependentVariable;

  namespace detail {

    class EPMODEL_API TableLookup_Impl : public Curve_Impl
    {
     public:
      using Curve_Impl::Curve_Impl;
      virtual ~TableLookup_Impl() override = default;

      std::string normalizationMethod() const;
      bool setNormalizationMethod(const std::string& normalizationMethod);

      double normalizationDivisor() const;
      bool setNormalizationDivisor(double normalizationDivisor);

      boost::optional<double> minimumOutput() const;
      bool setMinimumOutput(double minimumOutput);
      void resetMinimumOutput();

      boost::optional<double> maximumOutput() const;
      bool setMaximumOutput(double maximumOutput);
      void resetMaximumOutput();

      std::string outputUnitType() const;
      bool setOutputUnitType(const std::string& outputUnitType);

      bool addOutputValue(double outputValue);
      bool removeOutputValue(unsigned groupIndex);
      void removeAllOutputValues();
      std::vector<double> outputValues() const;
      unsigned numberofOutputValues() const;
      bool setOutputValues(const std::vector<double>& outputValues);

      bool addIndependentVariable(const TableIndependentVariable& tableIndependentVariable);
      bool removeIndependentVariable(const TableIndependentVariable& tableIndependentVariable);
      void removeAllIndependentVariables();
      std::vector<TableIndependentVariable> independentVariables() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
