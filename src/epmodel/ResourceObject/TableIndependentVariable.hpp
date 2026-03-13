/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TABLEINDEPENDENTVARIABLE_HPP
#define EPMODEL_TABLEINDEPENDENTVARIABLE_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  class Model;
  class TableLookup;

  namespace detail {
    class TableIndependentVariable_Impl;
  }

  class EPMODEL_API TableIndependentVariable : public ResourceObject
  {
   public:
    explicit TableIndependentVariable(const Model& model);

    virtual ~TableIndependentVariable() override = default;
    TableIndependentVariable(const TableIndependentVariable& other) = default;
    TableIndependentVariable(TableIndependentVariable&& other) = default;
    TableIndependentVariable& operator=(const TableIndependentVariable&) = default;
    TableIndependentVariable& operator=(TableIndependentVariable&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> interpolationMethodValues();
    static std::vector<std::string> validInterpolationMethodValues();
    static std::vector<std::string> extrapolationMethodValues();
    static std::vector<std::string> validExtrapolationMethodValues();
    static std::vector<std::string> unitTypeValues();
    static std::vector<std::string> validUnitTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for TableIndependentVariable.
    // - Field Mapping: Each scalar maps directly to the corresponding Table:IndependentVariable field via Table_IndependentVariableFields enums.
    // - ForwardTranslator evidence: ForwardTranslateTableIndependentVariable.cpp writes the same Table:IndependentVariable fields while feeding Table:Lookup via extensible Value lines.
    // - Field Mapping: Value extensibles are represented with typed extensible-group APIs.

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

   protected:
    using ImplType = detail::TableIndependentVariable_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit TableIndependentVariable(std::shared_ptr<detail::TableIndependentVariable_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
