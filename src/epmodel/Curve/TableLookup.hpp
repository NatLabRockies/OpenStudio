/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLELOOKUP_HPP
#define EPMODEL_TABLELOOKUP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class TableLookup_Impl;
  }

  class EPMODEL_API TableLookup : public ModelObject
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
    // - Field Mapping: IndependentVariableListName and Output Value extensibles remain relationship-like and are intentionally excluded from this scalar-only run.

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
