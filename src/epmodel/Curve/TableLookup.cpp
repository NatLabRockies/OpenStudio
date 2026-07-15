/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/TableLookup.hpp"
#include "Curve/TableLookup_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ResourceObject/TableIndependentVariable.hpp"
#include "ResourceObject/TableIndependentVariable_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Table_IndependentVariableList_FieldEnums.hxx>
#include <utilities/idd/Table_IndependentVariable_FieldEnums.hxx>
#include <utilities/idd/Table_Lookup_FieldEnums.hxx>

#include <algorithm>
#include <limits>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    namespace {

      boost::optional<ModelObject> independentVariableListObject(const TableLookup_Impl& impl) {
        return impl.getObject<ModelObject>().getModelObjectTarget<ModelObject>(Table_LookupFields::IndependentVariableListName);
      }

      ModelObject ensureIndependentVariableListObject(TableLookup_Impl& impl) {
        if (auto existing = independentVariableListObject(impl)) {
          return *existing;
        }

        auto listObject = ModelObject::create(IddObjectType::Table_IndependentVariableList, impl.model(), true);
        auto tableLookup = impl.getObject<TableLookup>();
        const auto tableName = tableLookup.nameString();
        if (!tableName.empty()) {
          listObject.setName(tableName + " Independent Variable List");
        }
        OS_ASSERT(tableLookup.setPointer(Table_LookupFields::IndependentVariableListName, listObject.handle()));
        return listObject;
      }

    }  // namespace

    std::string TableLookup_Impl::normalizationMethod() const {
      auto value = getString(Table_LookupFields::NormalizationMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool TableLookup_Impl::setNormalizationMethod(const std::string& normalizationMethod) {
      return setString(Table_LookupFields::NormalizationMethod, normalizationMethod);
    }

    double TableLookup_Impl::normalizationDivisor() const {
      auto value = getDouble(Table_LookupFields::NormalizationDivisor, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool TableLookup_Impl::setNormalizationDivisor(double normalizationDivisor) {
      if (std::abs(normalizationDivisor) < std::numeric_limits<double>::min()) {
        LOG_FREE(Warn, "openstudio.epmodel.TableLookup", "Unable to set " << briefDescription() << "'s normalization divisor to zero.");
        return false;
      }
      return setDouble(Table_LookupFields::NormalizationDivisor, normalizationDivisor);
    }

    boost::optional<double> TableLookup_Impl::minimumOutput() const {
      return getDouble(Table_LookupFields::MinimumOutput, true);
    }

    bool TableLookup_Impl::setMinimumOutput(double minimumOutput) {
      return setDouble(Table_LookupFields::MinimumOutput, minimumOutput);
    }

    void TableLookup_Impl::resetMinimumOutput() {
      OS_ASSERT(setString(Table_LookupFields::MinimumOutput, ""));
    }

    boost::optional<double> TableLookup_Impl::maximumOutput() const {
      return getDouble(Table_LookupFields::MaximumOutput, true);
    }

    bool TableLookup_Impl::setMaximumOutput(double maximumOutput) {
      return setDouble(Table_LookupFields::MaximumOutput, maximumOutput);
    }

    void TableLookup_Impl::resetMaximumOutput() {
      OS_ASSERT(setString(Table_LookupFields::MaximumOutput, ""));
    }

    std::string TableLookup_Impl::outputUnitType() const {
      auto value = getString(Table_LookupFields::OutputUnitType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool TableLookup_Impl::setOutputUnitType(const std::string& outputUnitType) {
      return setString(Table_LookupFields::OutputUnitType, outputUnitType);
    }

    bool TableLookup_Impl::addOutputValue(double outputValue) {
      auto group = getObject<ModelObject>().pushExtensibleGroup();
      const bool result = group.setDouble(Table_LookupExtensibleFields::OutputValue, outputValue);
      if (!result) {
        getObject<ModelObject>().eraseExtensibleGroup(group.groupIndex());
      }
      return result;
    }

    bool TableLookup_Impl::removeOutputValue(unsigned groupIndex) {
      if (groupIndex >= numberofOutputValues()) {
        return false;
      }
      getObject<ModelObject>().eraseExtensibleGroup(groupIndex);
      return true;
    }

    void TableLookup_Impl::removeAllOutputValues() {
      clearExtensibleGroups();
    }

    std::vector<double> TableLookup_Impl::outputValues() const {
      std::vector<double> result;
      for (const auto& group : extensibleGroups()) {
        auto value = group.getDouble(Table_LookupExtensibleFields::OutputValue);
        OS_ASSERT(value);
        result.push_back(value.get());
      }
      return result;
    }

    unsigned TableLookup_Impl::numberofOutputValues() const {
      return numExtensibleGroups();
    }

    bool TableLookup_Impl::setOutputValues(const std::vector<double>& outputValues) {
      clearExtensibleGroups();
      bool result = true;
      for (double outputValue : outputValues) {
        result &= addOutputValue(outputValue);
      }
      return result;
    }

    bool TableLookup_Impl::addIndependentVariable(const TableIndependentVariable& tableIndependentVariable) {
      auto listObject = ensureIndependentVariableListObject(*this);
      for (const auto& group : listObject.extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<WorkspaceExtensibleGroup>();
        if (workspaceGroup && workspaceGroup->getTarget(Table_IndependentVariableListExtensibleFields::IndependentVariableName)) {
          auto target = workspaceGroup->getTarget(Table_IndependentVariableListExtensibleFields::IndependentVariableName);
          if (target->handle() == tableIndependentVariable.handle()) {
            return false;
          }
        }
      }

      auto group = listObject.pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
      if (!group.setPointer(Table_IndependentVariableListExtensibleFields::IndependentVariableName, tableIndependentVariable.handle())) {
        listObject.eraseExtensibleGroup(group.groupIndex());
        return false;
      }
      return true;
    }

    bool TableLookup_Impl::removeIndependentVariable(const TableIndependentVariable& tableIndependentVariable) {
      auto listObject = independentVariableListObject(*this);
      if (!listObject) {
        return false;
      }

      const auto groups = listObject->extensibleGroups();
      for (const auto& group : groups) {
        auto workspaceGroup = group.optionalCast<WorkspaceExtensibleGroup>();
        if (workspaceGroup && workspaceGroup->getTarget(Table_IndependentVariableListExtensibleFields::IndependentVariableName)) {
          auto target = workspaceGroup->getTarget(Table_IndependentVariableListExtensibleFields::IndependentVariableName);
          if (target->handle() == tableIndependentVariable.handle()) {
            listObject->eraseExtensibleGroup(group.groupIndex());
            return true;
          }
        }
      }
      return false;
    }

    void TableLookup_Impl::removeAllIndependentVariables() {
      if (auto listObject = independentVariableListObject(*this)) {
        listObject->clearExtensibleGroups();
      }
    }

    std::vector<TableIndependentVariable> TableLookup_Impl::independentVariables() const {
      std::vector<TableIndependentVariable> result;
      auto listObject = independentVariableListObject(*this);
      if (!listObject) {
        return result;
      }

      for (const auto& group : listObject->extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<WorkspaceExtensibleGroup>();
        if (workspaceGroup) {
          auto target = workspaceGroup->getTarget(Table_IndependentVariableListExtensibleFields::IndependentVariableName);
          if (target) {
            auto typed = target->optionalCast<TableIndependentVariable>();
            if (typed) {
              result.push_back(*typed);
            }
          }
        }
      }
      return result;
    }

  }  // namespace detail

  TableLookup::TableLookup(const Model& model) : Curve(TableLookup::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::TableLookup_Impl>());

    bool ok = true;
    ok = setNormalizationMethod("None");
    OS_ASSERT(ok);
    ok = setNormalizationDivisor(1.0);
    OS_ASSERT(ok);
    ok = setOutputUnitType("Dimensionless");
    OS_ASSERT(ok);
    getImpl<detail::TableLookup_Impl>()->removeAllIndependentVariables();
    getImpl<detail::TableLookup_Impl>()->removeAllOutputValues();
  }

  TableLookup::TableLookup(std::shared_ptr<detail::TableLookup_Impl> impl) : Curve(std::move(impl)) {}

  IddObjectType TableLookup::iddObjectType() {
    return IddObjectType::Table_Lookup;
  }

  std::vector<std::string> TableLookup::normalizationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_LookupFields::NormalizationMethod);
  }

  std::vector<std::string> TableLookup::validNormalizationMethodValues() {
    return normalizationMethodValues();
  }

  std::vector<std::string> TableLookup::outputUnitTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), Table_LookupFields::OutputUnitType);
  }

  std::vector<std::string> TableLookup::validOutputUnitTypeValues() {
    return outputUnitTypeValues();
  }

  std::string TableLookup::normalizationMethod() const {
    return getImpl<detail::TableLookup_Impl>()->normalizationMethod();
  }

  bool TableLookup::setNormalizationMethod(const std::string& normalizationMethod) {
    return getImpl<detail::TableLookup_Impl>()->setNormalizationMethod(normalizationMethod);
  }

  double TableLookup::normalizationDivisor() const {
    return getImpl<detail::TableLookup_Impl>()->normalizationDivisor();
  }

  bool TableLookup::setNormalizationDivisor(double normalizationDivisor) {
    return getImpl<detail::TableLookup_Impl>()->setNormalizationDivisor(normalizationDivisor);
  }

  boost::optional<double> TableLookup::minimumOutput() const {
    return getImpl<detail::TableLookup_Impl>()->minimumOutput();
  }

  bool TableLookup::setMinimumOutput(double minimumOutput) {
    return getImpl<detail::TableLookup_Impl>()->setMinimumOutput(minimumOutput);
  }

  void TableLookup::resetMinimumOutput() {
    getImpl<detail::TableLookup_Impl>()->resetMinimumOutput();
  }

  boost::optional<double> TableLookup::maximumOutput() const {
    return getImpl<detail::TableLookup_Impl>()->maximumOutput();
  }

  bool TableLookup::setMaximumOutput(double maximumOutput) {
    return getImpl<detail::TableLookup_Impl>()->setMaximumOutput(maximumOutput);
  }

  void TableLookup::resetMaximumOutput() {
    getImpl<detail::TableLookup_Impl>()->resetMaximumOutput();
  }

  std::string TableLookup::outputUnitType() const {
    return getImpl<detail::TableLookup_Impl>()->outputUnitType();
  }

  bool TableLookup::setOutputUnitType(const std::string& outputUnitType) {
    return getImpl<detail::TableLookup_Impl>()->setOutputUnitType(outputUnitType);
  }

  bool TableLookup::addOutputValue(double outputValue) {
    return getImpl<detail::TableLookup_Impl>()->addOutputValue(outputValue);
  }

  bool TableLookup::removeOutputValue(unsigned groupIndex) {
    return getImpl<detail::TableLookup_Impl>()->removeOutputValue(groupIndex);
  }

  void TableLookup::removeAllOutputValues() {
    getImpl<detail::TableLookup_Impl>()->removeAllOutputValues();
  }

  std::vector<double> TableLookup::outputValues() const {
    return getImpl<detail::TableLookup_Impl>()->outputValues();
  }

  unsigned TableLookup::numberofOutputValues() const {
    return getImpl<detail::TableLookup_Impl>()->numberofOutputValues();
  }

  bool TableLookup::setOutputValues(const std::vector<double>& outputValues) {
    return getImpl<detail::TableLookup_Impl>()->setOutputValues(outputValues);
  }

  bool TableLookup::addIndependentVariable(const TableIndependentVariable& tableIndependentVariable) {
    return getImpl<detail::TableLookup_Impl>()->addIndependentVariable(tableIndependentVariable);
  }

  bool TableLookup::removeIndependentVariable(const TableIndependentVariable& tableIndependentVariable) {
    return getImpl<detail::TableLookup_Impl>()->removeIndependentVariable(tableIndependentVariable);
  }

  void TableLookup::removeAllIndependentVariables() {
    getImpl<detail::TableLookup_Impl>()->removeAllIndependentVariables();
  }

  std::vector<TableIndependentVariable> TableLookup::independentVariables() const {
    return getImpl<detail::TableLookup_Impl>()->independentVariables();
  }

}  // namespace epmodel
}  // namespace openstudio
