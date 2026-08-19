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

  /** \brief Represents a multi-dimensional table lookup curve.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-tables.html#tablelookup,Table:Lookup}, together with its
   * \epobject{group-performance-tables.html#tableindependentvariablelist,Table:IndependentVariableList} and
   * \epobject{group-performance-tables.html#tableindependentvariable,Table:IndependentVariable} companion objects.
   *
   * \par Important behavior
   * Output values are stored in this object's extensible fields. Independent
   * variables are referenced by extensible rows on the companion
   * <code>Table:IndependentVariableList</code>; the typed relationship methods
   * create that list when needed and add or remove its rows.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::TableLookup</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * <code>evaluate()</code> is not implemented for table lookup curves; it
   * logs a warning and returns <code>-9999.0</code>.
   */
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
