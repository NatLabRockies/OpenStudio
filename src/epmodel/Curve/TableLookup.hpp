/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLELOOKUP_HPP
#define EPMODEL_TABLELOOKUP_HPP

#include "EPModelAPI.hpp"
#include "Curve.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;
  class TableIndependentVariable;

  namespace detail {
    class TableLookup_Impl;
  }

  class EPMODEL_API TableLookup : public Curve
  {
   public:
    explicit TableLookup(const Model& model);

    virtual ~TableLookup() override = default;
    TableLookup(const TableLookup& other) = default;
    TableLookup(TableLookup&& other) = default;
    TableLookup& operator=(const TableLookup&) = default;
    TableLookup& operator=(TableLookup&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> normalizationMethodValues();
    static std::vector<std::string> validNormalizationMethodValues();

    static std::vector<std::string> outputUnitTypeValues();
    static std::vector<std::string> validOutputUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model TableLookup scalar accessor names/signatures.
    // - Field Mapping: Scalars map directly to Table:Lookup fields via Table_LookupFields and ForwardTranslateTableLookup.cpp writes the same fields.
    // - Field Mapping: IndependentVariableListName and Output Value extensibles are represented with typed object/extensible APIs.

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

   protected:
    using ImplType = detail::TableLookup_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit TableLookup(std::shared_ptr<detail::TableLookup_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
