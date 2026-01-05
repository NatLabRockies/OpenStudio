/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputTableAnnual.hpp"
#include "OutputTableAnnual_Impl.hpp"

#include "ModelExtensibleGroup.hpp"

#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "ScheduleTypeLimits.hpp"
#include "ScheduleTypeRegistry.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OS_Output_Table_Annual_FieldEnums.hxx>
#include <fmt/format.h>
#include <fmt/ranges.h>

namespace openstudio {
namespace model {

  AnnualVariableGroup::AnnualVariableGroup(std::string variableorMeterorEMSVariableorField, std::string aggregationType, int digitsAfterDecimal)
    : m_variableorMeterorEMSVariableorField(std::move(variableorMeterorEMSVariableorField)),
      m_aggregationType(std::move(aggregationType)),
      m_digitsAfterDecimal(digitsAfterDecimal) {
    if (m_variableorMeterorEMSVariableorField.empty()) {
      LOG_AND_THROW("Variable or Meter or EMSVariable or Field Name can't be empty");
    }
    if (!OutputTableAnnual::isAggregationTypeValid(m_aggregationType)) {
      LOG_AND_THROW(fmt::format("Invalid aggregation type '{}': {}", m_aggregationType, OutputTableAnnual::aggregationTypeValues()));
    }
  }

  std::string AnnualVariableGroup::variableorMeterorEMSVariableorField() const {
    return m_variableorMeterorEMSVariableorField;
  }

  std::string AnnualVariableGroup::aggregationType() const {
    return m_aggregationType;
  }

  int AnnualVariableGroup::digitsAfterDecimal() const {
    return m_digitsAfterDecimal;
  }

  bool AnnualVariableGroup::isAggregationTypeAdvanced() const {
    return OutputTableAnnual::isAggregationTypeAdvanced(m_aggregationType);
  }

  bool AnnualVariableGroup::operator==(const AnnualVariableGroup& other) const {
    return openstudio::istringEqual(variableorMeterorEMSVariableorField(), other.variableorMeterorEMSVariableorField())
           && openstudio::istringEqual(aggregationType(), other.aggregationType());
  }

  bool AnnualVariableGroup::operator!=(const AnnualVariableGroup& other) const {
    return (!operator==(other));
  }

  std::ostream& operator<<(std::ostream& out, const openstudio::model::AnnualVariableGroup& annualVariableGroup) {
    out << "(Output Variable or Meter = '" << annualVariableGroup.variableorMeterorEMSVariableorField() << "', Aggregation Type = '"
        << annualVariableGroup.aggregationType() << "', Digits After Decimal = " << annualVariableGroup.digitsAfterDecimal() << ")";
    return out;
  }

  namespace detail {

    OutputTableAnnual_Impl::OutputTableAnnual_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == OutputTableAnnual::iddObjectType());
    }

    OutputTableAnnual_Impl::OutputTableAnnual_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == OutputTableAnnual::iddObjectType());
    }

    OutputTableAnnual_Impl::OutputTableAnnual_Impl(const OutputTableAnnual_Impl& other, Model_Impl* model, bool keepHandle)
      : ModelObject_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& OutputTableAnnual_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    IddObjectType OutputTableAnnual_Impl::iddObjectType() const {
      return OutputTableAnnual::iddObjectType();
    }

    std::vector<ScheduleTypeKey> OutputTableAnnual_Impl::getScheduleTypeKeys(const Schedule& schedule) const {
      std::vector<ScheduleTypeKey> result;
      const UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
      if (std::find(fieldIndices.cbegin(), fieldIndices.cend(), OS_Output_Table_AnnualFields::ScheduleName) != fieldIndices.cend()) {
        result.emplace_back("OutputTableAnnual", "Output Table Annual");
      }
      return result;
    }

    boost::optional<std::string> OutputTableAnnual_Impl::filter() const {
      return getString(OS_Output_Table_AnnualFields::Filter, true, true);
    }

    boost::optional<Schedule> OutputTableAnnual_Impl::schedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Output_Table_AnnualFields::ScheduleName);
    }

    bool OutputTableAnnual_Impl::setFilter(const std::string& filter) {
      const bool result = setString(OS_Output_Table_AnnualFields::Filter, filter);
      OS_ASSERT(result);
      return result;
    }

    void OutputTableAnnual_Impl::resetFilter() {
      const bool result = setString(OS_Output_Table_AnnualFields::Filter, "");
      OS_ASSERT(result);
    }

    bool OutputTableAnnual_Impl::setSchedule(Schedule& schedule) {
      const bool result =
        ModelObject_Impl::setSchedule(OS_Output_Table_AnnualFields::ScheduleName, "OutputTableAnnual", "Output Table Annual", schedule);
      return result;
    }

    void OutputTableAnnual_Impl::resetSchedule() {
      const bool result = setString(OS_Output_Table_AnnualFields::ScheduleName, "");
      OS_ASSERT(result);
    }

    unsigned int OutputTableAnnual_Impl::numberofAnnualVariableGroups() const {
      return numExtensibleGroups();
    }

    std::vector<AnnualVariableGroup> OutputTableAnnual_Impl::annualVariableGroups() const {
      std::vector<AnnualVariableGroup> result;

      for (unsigned i = 0; i < numberofAnnualVariableGroups(); ++i) {

        boost::optional<AnnualVariableGroup> group_ = getAnnualVariableGroup(i);

        // getAnnualVariableGroup is responsible for handling error and issuing Error log messages.
        // Here we add it to the result array if it worked, and if it didn't, we keep going
        // We just issue a message about index so user can delete it easily
        if (group_) {
          result.push_back(std::move(*group_));
        } else {
          LOG(Error, briefDescription() << " has an invalid AnnualVariableGroup group at index " << i);
        }
      }

      return result;
    }

    boost::optional<unsigned> OutputTableAnnual_Impl::annualVariableGroupIndex(const AnnualVariableGroup& annualVariableGroup) const {
      const std::vector<AnnualVariableGroup> groups = annualVariableGroups();
      auto it = std::find(groups.cbegin(), groups.cend(), annualVariableGroup);
      if (it != groups.end()) {
        return static_cast<unsigned>(std::distance(groups.cbegin(), it));
      }
      return boost::none;
    }

    boost::optional<AnnualVariableGroup> OutputTableAnnual_Impl::getAnnualVariableGroup(unsigned groupIndex) const {
      if (groupIndex >= numberofAnnualVariableGroups()) {
        LOG(Error, "Asked to get AnnualVariableGroup with index " << groupIndex << ", but " << briefDescription() << " has just "
                                                                  << numberofAnnualVariableGroups() << " AnnualVariableGroups.");
        return boost::none;
      }
      auto group = getExtensibleGroup(groupIndex).cast<ModelExtensibleGroup>();

      boost::optional<std::string> variableorMeterorEMSVariableorField_ =
        group.getString(OS_Output_Table_AnnualExtensibleFields::VariableorMeterorEMSVariableorFieldName);
      boost::optional<std::string> aggregationType_ = group.getString(OS_Output_Table_AnnualExtensibleFields::AggregationTypeforVariableorMeter);
      int digitsAfterDecimal = group.getInt(OS_Output_Table_AnnualExtensibleFields::DigitsAfterDecimal).value_or(2);

      if (!variableorMeterorEMSVariableorField_) {
        LOG(Error, "Could not retrieve VariableorMeterName_ for extensible group " << group.groupIndex() << ".");
        return boost::none;
      }
      if (!aggregationType_) {
        LOG(Error, "Could not retrieve Aggregation Type for extensible group " << group.groupIndex() << ".");
        return boost::none;
      }

      return {AnnualVariableGroup(std::move(*variableorMeterorEMSVariableorField_), std::move(*aggregationType_), digitsAfterDecimal)};
    }

    bool OutputTableAnnual_Impl::addAnnualVariableGroup(const AnnualVariableGroup& annualVariableGroup) {
      boost::optional<unsigned> existingIndex_;
      if (!annualVariableGroup.isAggregationTypeAdvanced()) {
        existingIndex_ = annualVariableGroupIndex(annualVariableGroup);
        if (existingIndex_) {
          boost::optional<AnnualVariableGroup> group_ = getAnnualVariableGroup(existingIndex_.get());
          OS_ASSERT(group_);
          LOG(Warn, "For " << briefDescription()
                           << ", AnnualVariableGroup already exists and is not an Advanced Aggregation Type, will be modified in place from "
                           << group_.get() << " to " << annualVariableGroup << ".");
        }
      }

      // If existing, get it, otherwise Push an extensible group. ModelExtensibleGroup cannot be default-constructed, so use a ternary operator
      IdfExtensibleGroup eg = (existingIndex_ ? getExtensibleGroup(existingIndex_.get()) : pushExtensibleGroup({}, false));
      eg.setString(OS_Output_Table_AnnualExtensibleFields::VariableorMeterorEMSVariableorFieldName,
                   annualVariableGroup.variableorMeterorEMSVariableorField());
      eg.setString(OS_Output_Table_AnnualExtensibleFields::AggregationTypeforVariableorMeter, annualVariableGroup.aggregationType());
      eg.setInt(OS_Output_Table_AnnualExtensibleFields::DigitsAfterDecimal, annualVariableGroup.digitsAfterDecimal());
      return true;
    }

    bool OutputTableAnnual_Impl::addAnnualVariableGroups(const std::vector<AnnualVariableGroup>& annualVariableGroups) {
      bool result = true;

      for (const auto& annualVariableGroup : annualVariableGroups) {
        bool thisResult = addAnnualVariableGroup(annualVariableGroup);
        // cppcheck-suppress knownConditionTrueFalse
        if (!thisResult) {
          LOG(Error, "Could not add AnnualVariableGroup " << annualVariableGroup << " to " << briefDescription() << ". Continuing with others.");
          // OS_ASSERT(false);
          // result = false;
        }
      }

      return result;
    }

    bool OutputTableAnnual_Impl::removeAnnualVariableGroup(unsigned groupIndex) {
      bool result = false;

      unsigned int num = numberofAnnualVariableGroups();
      if (groupIndex < num) {
        getObject<ModelObject>().eraseExtensibleGroup(groupIndex);
        result = true;
      }
      return result;
    }

    void OutputTableAnnual_Impl::removeAllAnnualVariableGroups() {
      getObject<ModelObject>().clearExtensibleGroups();
    }

  }  // namespace detail

  OutputTableAnnual::OutputTableAnnual(const Model& model) : ModelObject(OutputTableAnnual::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::OutputTableAnnual_Impl>());
  }

  std::vector<std::string> OutputTableAnnual::aggregationTypeValues() {
    IddObject obj = IddFactory::instance().getObject(iddObjectType()).get();
    // Return IddKeyNames in extensible portion
    return getIddKeyNames(obj, obj.numFields() + OS_Output_Table_AnnualExtensibleFields::AggregationTypeforVariableorMeter);
  }

  std::vector<std::string> OutputTableAnnual::validAggregationTypes() {
    return aggregationTypeValues();
  }

  bool OutputTableAnnual::isAggregationTypeValid(const std::string& aggregationType) {
    const auto vals = aggregationTypeValues();
    return std::find_if(vals.cbegin(), vals.cend(),
                        [&aggregationType](const std::string& choice) { return openstudio::istringEqual(aggregationType, choice); })
           != vals.cend();
  }

  bool OutputTableAnnual::isAggregationTypeAdvanced(const std::string& aggregationType) {
    auto const& vals = advancedAggregationTypes();
    return std::find_if(vals.cbegin(), vals.cend(),
                        [&aggregationType](const std::string& choice) { return openstudio::istringEqual(aggregationType, choice); })
           != vals.cend();
  }

  const std::vector<std::string>& OutputTableAnnual::advancedAggregationTypes() {
    static std::vector<std::string> result;
    if (result.empty()) {
      result = {"ValueWhenMaximumOrMinimum", "SumOrAverageDuringHoursShown", "MaximumDuringHoursShown", "MinimumDuringHoursShown"};
    }
    return result;
  }

  IddObjectType OutputTableAnnual::iddObjectType() {
    return {IddObjectType::OS_Output_Table_Annual};
  }

  boost::optional<std::string> OutputTableAnnual::filter() const {
    return getImpl<detail::OutputTableAnnual_Impl>()->filter();
  }

  boost::optional<Schedule> OutputTableAnnual::schedule() const {
    return getImpl<detail::OutputTableAnnual_Impl>()->schedule();
  }

  bool OutputTableAnnual::setFilter(const std::string& filter) {
    return getImpl<detail::OutputTableAnnual_Impl>()->setFilter(filter);
  }

  void OutputTableAnnual::resetFilter() {
    getImpl<detail::OutputTableAnnual_Impl>()->resetFilter();
  }

  bool OutputTableAnnual::setSchedule(Schedule& schedule) {
    return getImpl<detail::OutputTableAnnual_Impl>()->setSchedule(schedule);
  }

  void OutputTableAnnual::resetSchedule() {
    getImpl<detail::OutputTableAnnual_Impl>()->resetSchedule();
  }

  std::vector<AnnualVariableGroup> OutputTableAnnual::annualVariableGroups() const {
    return getImpl<detail::OutputTableAnnual_Impl>()->annualVariableGroups();
  }

  unsigned int OutputTableAnnual::numberofAnnualVariableGroups() const {
    return getImpl<detail::OutputTableAnnual_Impl>()->numberofAnnualVariableGroups();
  }

  boost::optional<unsigned> OutputTableAnnual::annualVariableGroupIndex(const AnnualVariableGroup& annualVariableGroup) const {
    return getImpl<detail::OutputTableAnnual_Impl>()->annualVariableGroupIndex(annualVariableGroup);
  }

  boost::optional<AnnualVariableGroup> OutputTableAnnual::getAnnualVariableGroup(unsigned groupIndex) const {
    return getImpl<detail::OutputTableAnnual_Impl>()->getAnnualVariableGroup(groupIndex);
  }

  bool OutputTableAnnual::addAnnualVariableGroup(const AnnualVariableGroup& annualVariableGroup) {
    return getImpl<detail::OutputTableAnnual_Impl>()->addAnnualVariableGroup(annualVariableGroup);
  }

  bool OutputTableAnnual::addAnnualVariableGroup(std::string variableorMeterorEMSVariableorField, std::string aggregationType,
                                                 int digitsAfterDecimal) {
    return addAnnualVariableGroup(
      AnnualVariableGroup(std::move(variableorMeterorEMSVariableorField), std::move(aggregationType), digitsAfterDecimal));
  }

  bool OutputTableAnnual::addAnnualVariableGroups(const std::vector<AnnualVariableGroup>& annualVariableGroups) {
    return getImpl<detail::OutputTableAnnual_Impl>()->addAnnualVariableGroups(annualVariableGroups);
  }

  bool OutputTableAnnual::removeAnnualVariableGroup(unsigned groupIndex) {
    return getImpl<detail::OutputTableAnnual_Impl>()->removeAnnualVariableGroup(groupIndex);
  }

  void OutputTableAnnual::removeAllAnnualVariableGroups() {
    getImpl<detail::OutputTableAnnual_Impl>()->removeAllAnnualVariableGroups();
  }

  /// @cond
  OutputTableAnnual::OutputTableAnnual(std::shared_ptr<detail::OutputTableAnnual_Impl> impl) : ModelObject(std::move(impl)) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
