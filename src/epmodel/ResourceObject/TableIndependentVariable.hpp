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

  /** \brief Defines one independent-variable axis for a table lookup.
   *
   * \par EnergyPlus object
   * \epobject{group-performance-tables.html#tableindependentvariable,Table:IndependentVariable}.
   *
   * \par Important behavior
   * Values are stored as extensible EnergyPlus groups. The
   * <code>tableLookups()</code> method finds table objects that reference this
   * variable; it does not transfer ownership of them. Values can be replaced
   * as a group with <code>setValues()</code>.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::TableIndependentVariable</code>. EPModel exposes
   * the same value and table-lookup methods and additionally exposes explicit
   * default-state queries and resets for interpolation, extrapolation, and
   * unit type.
   *
   * \par Known limitations
   * Table lookup reverse navigation is limited to persisted references; this
   * wrapper does not create or update the referencing table objects.
   */
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
