/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_OUTPUTTABLEANNUAL_HPP
#define MODEL_OUTPUTTABLEANNUAL_HPP

#include <model/ModelAPI.hpp>
#include "ModelObject.hpp"

namespace openstudio {
namespace model {

  class Schedule;

  namespace detail {

    class OutputTableAnnual_Impl;

  }  // namespace detail

  class MODEL_API AnnualVariableGroup
  {
   public:
    AnnualVariableGroup(std::string variableorMeterorEMSVariableorField, std::string aggregationType = "SumOrAverage", int digitsAfterDecimal = 2);

    std::string variableorMeterorEMSVariableorField() const;
    std::string aggregationType() const;
    int digitsAfterDecimal() const;

    bool isAggregationTypeAdvanced() const;

    // Only checks on variableorMeterorEMSVariableorField and aggregationType, not digitsAfterDecimal
    bool operator==(const AnnualVariableGroup& other) const;
    bool operator!=(const AnnualVariableGroup& other) const;

   private:
    std::string m_variableorMeterorEMSVariableorField;
    std::string m_aggregationType;
    int m_digitsAfterDecimal;
    REGISTER_LOGGER("openstudio.model.AnnualVariableGroup");
  };

  // Overload operator<<
  MODEL_API std::ostream& operator<<(std::ostream& out, const openstudio::model::AnnualVariableGroup& annualVariableGroup);

  /** OutputTableAnnual is a ModelObject that wraps the OpenStudio IDD object 'OS:Output:Table:Annual'. */
  class MODEL_API OutputTableAnnual : public ModelObject
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit OutputTableAnnual(const Model& model);

    virtual ~OutputTableAnnual() override = default;
    // Default the copy and move operators because the virtual dtor is explicit
    OutputTableAnnual(const OutputTableAnnual& other) = default;
    OutputTableAnnual(OutputTableAnnual&& other) = default;
    OutputTableAnnual& operator=(const OutputTableAnnual&) = default;
    OutputTableAnnual& operator=(OutputTableAnnual&&) = default;

    //@}

    static IddObjectType iddObjectType();

    static std::vector<std::string> aggregationTypeValues();
    static std::vector<std::string> validAggregationTypes();
    static bool isAggregationTypeValid(const std::string& aggregationType);
    static bool isAggregationTypeAdvanced(const std::string& aggregationType);
    static const std::vector<std::string>& advancedAggregationTypes();

    /** @name Getters */
    //@{

    boost::optional<std::string> filter() const;

    boost::optional<Schedule> schedule() const;

    //@}
    /** @name Setters */
    //@{

    bool setFilter(const std::string& filter);

    void resetFilter();

    bool setSchedule(Schedule& schedule);

    void resetSchedule();

    //@}
    /** @name Other */
    //@{

    // Handle this object's extensible fields.

    std::vector<AnnualVariableGroup> annualVariableGroups() const;

    unsigned int numberofAnnualVariableGroups() const;

    boost::optional<unsigned> annualVariableGroupIndex(const AnnualVariableGroup& annualVariableGroup) const;
    boost::optional<AnnualVariableGroup> getAnnualVariableGroup(unsigned groupIndex) const;

    bool addAnnualVariableGroup(const AnnualVariableGroup& annualVariableGroup);

    // Convenience fucntion that will create a AnnualVariableGroup
    bool addAnnualVariableGroup(std::string variableorMeterorEMSVariableorField, std::string aggregationType = "SumOrAverage",
                                int digitsAfterDecimal = 2);

    bool addAnnualVariableGroups(const std::vector<AnnualVariableGroup>& annualVariableGroups);
    bool removeAnnualVariableGroup(unsigned groupIndex);
    void removeAllAnnualVariableGroups();

    //@}
   protected:
    /// @cond
    using ImplType = detail::OutputTableAnnual_Impl;

    explicit OutputTableAnnual(std::shared_ptr<detail::OutputTableAnnual_Impl> impl);

    friend class detail::OutputTableAnnual_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.OutputTableAnnual");
  };

  /** \relates OutputTableAnnual*/
  using OptionalOutputTableAnnual = boost::optional<OutputTableAnnual>;

  /** \relates OutputTableAnnual*/
  using OutputTableAnnualVector = std::vector<OutputTableAnnual>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_OUTPUTTABLEANNUAL_HPP
