/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_OUTPUTTABLEMONTHLY_HPP
#define MODEL_OUTPUTTABLEMONTHLY_HPP

#include <model/ModelAPI.hpp>
#include "ModelObject.hpp"

namespace openstudio {
namespace model {

  namespace detail {

    class OutputTableMonthly_Impl;

  }  // namespace detail

  class MODEL_API MonthlyVariableGroup
  {
   public:
    MonthlyVariableGroup(std::string variableOrMeterName, std::string aggregationType = "SumOrAverage");

    std::string variableOrMeterName() const;
    std::string aggregationType() const;

    bool isAggregationTypeAdvanced() const;

    bool operator==(const MonthlyVariableGroup& other) const;
    bool operator!=(const MonthlyVariableGroup& other) const;

   private:
    std::string m_variableOrMeterName;
    std::string m_aggregationType;
    REGISTER_LOGGER("openstudio.model.MonthlyVariableGroup");
  };

  // Overload operator<<
  MODEL_API std::ostream& operator<<(std::ostream& out, const openstudio::model::MonthlyVariableGroup& monthlyVariableGroup);

  /** OutputTableMonthly is a ModelObject that wraps the OpenStudio IDD object 'OS:Output:Table:Monthly'. */
  class MODEL_API OutputTableMonthly : public ModelObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit OutputTableMonthly(const Model& model);

    virtual ~OutputTableMonthly() override = default;
    // Default the copy and move operators because the virtual dtor is explicit
    OutputTableMonthly(const OutputTableMonthly& other) = default;
    OutputTableMonthly(OutputTableMonthly&& other) = default;
    OutputTableMonthly& operator=(const OutputTableMonthly&) = default;
    OutputTableMonthly& operator=(OutputTableMonthly&&) = default;

    //@}

    static IddObjectType iddObjectType();

    static std::vector<std::string> aggregationTypeValues();
    static std::vector<std::string> validAggregationTypes();
    static bool isAggregationTypeValid(const std::string& aggregationType);
    static bool isAggregationTypeAdvanced(const std::string& aggregationType);
    static const std::vector<std::string>& advancedAggregationTypes();

    /// Factory method to create a OutputTableMonthly by looking up characteristics in the embedded  database (from E+ datasets/StandardReports.idf)
    /// by its name.
    /// Please use the OutputTableMonthly::validStandardReportNames() static method to look up the valid names
    // as it will throw if it cannot find it
    static OutputTableMonthly fromStandardReports(const Model& model, const std::string& standardReportName);
    static const std::vector<std::string>& validStandardReportNames();

    /** @name Getters */
    //@{

    int digitsAfterDecimal() const;

    //@}
    /** @name Setters */
    //@{

    bool setDigitsAfterDecimal(int digitsAfterDecimal);

    //@}
    /** @name Other */
    //@{

    // Handle this object's extensible fields.

    std::vector<MonthlyVariableGroup> monthlyVariableGroups() const;

    unsigned int numberofMonthlyVariableGroups() const;

    boost::optional<unsigned> monthlyVariableGroupIndex(const MonthlyVariableGroup& monthlyVariableGroup) const;
    boost::optional<MonthlyVariableGroup> getMonthlyVariableGroup(unsigned groupIndex) const;

    bool addMonthlyVariableGroup(const MonthlyVariableGroup& monthlyVariableGroup);

    // Convenience fucntion that will create a MonthlyVariableGroup
    bool addMonthlyVariableGroup(std::string variableOrMeterName, std::string aggregationType = "SumOrAverage");

    bool addMonthlyVariableGroups(const std::vector<MonthlyVariableGroup>& monthlyVariableGroups);
    bool removeMonthlyVariableGroup(unsigned groupIndex);
    void removeAllMonthlyVariableGroups();

    //@}
   protected:
    /// @cond
    using ImplType = detail::OutputTableMonthly_Impl;

    explicit OutputTableMonthly(std::shared_ptr<detail::OutputTableMonthly_Impl> impl);

    friend class detail::OutputTableMonthly_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.OutputTableMonthly");
  };

  /** \relates OutputTableMonthly*/
  using OptionalOutputTableMonthly = boost::optional<OutputTableMonthly>;

  /** \relates OutputTableMonthly*/
  using OutputTableMonthlyVector = std::vector<OutputTableMonthly>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_OUTPUTTABLEMONTHLY_HPP
