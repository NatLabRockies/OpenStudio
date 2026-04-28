/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostChargeSimple.hpp"
#include "UtilityCostChargeSimple_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/UtilityCost_Charge_Simple_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  UtilityCostChargeSimple::UtilityCostChargeSimple(const Model& model) : ModelObject(UtilityCostChargeSimple::iddObjectType(), model) {}

  UtilityCostChargeSimple::UtilityCostChargeSimple(std::shared_ptr<detail::UtilityCostChargeSimple_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostChargeSimple::iddObjectType() {
    return IddObjectType::UtilityCost_Charge_Simple;
  }

  std::vector<std::string> UtilityCostChargeSimple::seasonValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_Charge_SimpleFields::Season);
  }

  std::vector<std::string> UtilityCostChargeSimple::categoryVariableNameValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_Charge_SimpleFields::CategoryVariableName);
  }

  std::string UtilityCostChargeSimple::sourceVariable() const {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->sourceVariable();
  }

  bool UtilityCostChargeSimple::setSourceVariable(const std::string& sourceVariable) {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->setSourceVariable(sourceVariable);
  }

  boost::optional<std::string> UtilityCostChargeSimple::season() const {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->season();
  }

  bool UtilityCostChargeSimple::setSeason(const std::string& season) {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->setSeason(season);
  }

  void UtilityCostChargeSimple::resetSeason() {
    getImpl<detail::UtilityCostChargeSimple_Impl>()->resetSeason();
  }

  std::string UtilityCostChargeSimple::categoryVariableName() const {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->categoryVariableName();
  }

  bool UtilityCostChargeSimple::setCategoryVariableName(const std::string& categoryVariableName) {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->setCategoryVariableName(categoryVariableName);
  }

  std::string UtilityCostChargeSimple::costPerUnitValueorVariableName() const {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->costPerUnitValueorVariableName();
  }

  bool UtilityCostChargeSimple::setCostPerUnitValueorVariableName(const std::string& costPerUnitValueorVariableName) {
    return getImpl<detail::UtilityCostChargeSimple_Impl>()->setCostPerUnitValueorVariableName(costPerUnitValueorVariableName);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      bool setAlphaField(UtilityCostChargeSimple_Impl* impl, unsigned fieldIndex, const std::string& value) {
        if (impl->setString(fieldIndex, value)) {
          return true;
        }
        return impl->setString(fieldIndex, value, false);
      }
    }  // namespace

    std::string UtilityCostChargeSimple_Impl::sourceVariable() const {
      const auto value = getString(openstudio::UtilityCost_Charge_SimpleFields::SourceVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostChargeSimple_Impl::setSourceVariable(const std::string& sourceVariable) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_SimpleFields::SourceVariable, sourceVariable);
    }

    boost::optional<std::string> UtilityCostChargeSimple_Impl::season() const {
      const auto value = getString(openstudio::UtilityCost_Charge_SimpleFields::Season, true);
      if (value && !value->empty()) {
        return {*value};
      }
      return boost::none;
    }

    bool UtilityCostChargeSimple_Impl::setSeason(const std::string& season) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_SimpleFields::Season, season);
    }

    void UtilityCostChargeSimple_Impl::resetSeason() {
      OS_ASSERT(setString(openstudio::UtilityCost_Charge_SimpleFields::Season, ""));
    }

    std::string UtilityCostChargeSimple_Impl::categoryVariableName() const {
      const auto value = getString(openstudio::UtilityCost_Charge_SimpleFields::CategoryVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostChargeSimple_Impl::setCategoryVariableName(const std::string& categoryVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_SimpleFields::CategoryVariableName, categoryVariableName);
    }

    std::string UtilityCostChargeSimple_Impl::costPerUnitValueorVariableName() const {
      const auto value = getString(openstudio::UtilityCost_Charge_SimpleFields::CostperUnitValueorVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostChargeSimple_Impl::setCostPerUnitValueorVariableName(const std::string& costPerUnitValueorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_SimpleFields::CostperUnitValueorVariableName, costPerUnitValueorVariableName);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
