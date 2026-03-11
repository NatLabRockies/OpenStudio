/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostRatchet.hpp"
#include "UtilityCostRatchet_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/UtilityCost_Ratchet_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  UtilityCostRatchet::UtilityCostRatchet(const Model& model) : ModelObject(UtilityCostRatchet::iddObjectType(), model) {}

  UtilityCostRatchet::UtilityCostRatchet(std::shared_ptr<detail::UtilityCostRatchet_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostRatchet::iddObjectType() {
    return IddObjectType::UtilityCost_Ratchet;
  }

  std::vector<std::string> UtilityCostRatchet::seasonFromValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_RatchetFields::SeasonFrom);
  }

  std::vector<std::string> UtilityCostRatchet::seasonToValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_RatchetFields::SeasonTo);
  }

  std::string UtilityCostRatchet::baselineSourceVariable() const {
    return getImpl<detail::UtilityCostRatchet_Impl>()->baselineSourceVariable();
  }

  bool UtilityCostRatchet::setBaselineSourceVariable(const std::string& baselineSourceVariable) {
    return getImpl<detail::UtilityCostRatchet_Impl>()->setBaselineSourceVariable(baselineSourceVariable);
  }

  std::string UtilityCostRatchet::adjustmentSourceVariable() const {
    return getImpl<detail::UtilityCostRatchet_Impl>()->adjustmentSourceVariable();
  }

  bool UtilityCostRatchet::setAdjustmentSourceVariable(const std::string& adjustmentSourceVariable) {
    return getImpl<detail::UtilityCostRatchet_Impl>()->setAdjustmentSourceVariable(adjustmentSourceVariable);
  }

  std::string UtilityCostRatchet::seasonFrom() const {
    return getImpl<detail::UtilityCostRatchet_Impl>()->seasonFrom();
  }

  bool UtilityCostRatchet::setSeasonFrom(const std::string& seasonFrom) {
    return getImpl<detail::UtilityCostRatchet_Impl>()->setSeasonFrom(seasonFrom);
  }

  std::string UtilityCostRatchet::seasonTo() const {
    return getImpl<detail::UtilityCostRatchet_Impl>()->seasonTo();
  }

  bool UtilityCostRatchet::setSeasonTo(const std::string& seasonTo) {
    return getImpl<detail::UtilityCostRatchet_Impl>()->setSeasonTo(seasonTo);
  }

  boost::optional<std::string> UtilityCostRatchet::multiplierValueorVariableName() const {
    return getImpl<detail::UtilityCostRatchet_Impl>()->multiplierValueorVariableName();
  }

  bool UtilityCostRatchet::setMultiplierValueorVariableName(const std::string& multiplierValueorVariableName) {
    return getImpl<detail::UtilityCostRatchet_Impl>()->setMultiplierValueorVariableName(multiplierValueorVariableName);
  }

  void UtilityCostRatchet::resetMultiplierValueorVariableName() {
    getImpl<detail::UtilityCostRatchet_Impl>()->resetMultiplierValueorVariableName();
  }

  boost::optional<std::string> UtilityCostRatchet::offsetValueorVariableName() const {
    return getImpl<detail::UtilityCostRatchet_Impl>()->offsetValueorVariableName();
  }

  bool UtilityCostRatchet::setOffsetValueorVariableName(const std::string& offsetValueorVariableName) {
    return getImpl<detail::UtilityCostRatchet_Impl>()->setOffsetValueorVariableName(offsetValueorVariableName);
  }

  void UtilityCostRatchet::resetOffsetValueorVariableName() {
    getImpl<detail::UtilityCostRatchet_Impl>()->resetOffsetValueorVariableName();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      bool setAlphaField(UtilityCostRatchet_Impl* impl, unsigned fieldIndex, const std::string& value) {
        if (impl->setString(fieldIndex, value)) {
          return true;
        }
        return impl->setString(fieldIndex, value, false);
      }
    }  // namespace

    std::string UtilityCostRatchet_Impl::baselineSourceVariable() const {
      const boost::optional<std::string> value = getString(openstudio::UtilityCost_RatchetFields::BaselineSourceVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostRatchet_Impl::setBaselineSourceVariable(const std::string& baselineSourceVariable) {
      return setAlphaField(this, openstudio::UtilityCost_RatchetFields::BaselineSourceVariable, baselineSourceVariable);
    }

    std::string UtilityCostRatchet_Impl::adjustmentSourceVariable() const {
      const boost::optional<std::string> value = getString(openstudio::UtilityCost_RatchetFields::AdjustmentSourceVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostRatchet_Impl::setAdjustmentSourceVariable(const std::string& adjustmentSourceVariable) {
      return setAlphaField(this, openstudio::UtilityCost_RatchetFields::AdjustmentSourceVariable, adjustmentSourceVariable);
    }

    std::string UtilityCostRatchet_Impl::seasonFrom() const {
      const boost::optional<std::string> value = getString(openstudio::UtilityCost_RatchetFields::SeasonFrom, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostRatchet_Impl::setSeasonFrom(const std::string& seasonFrom) {
      return setAlphaField(this, openstudio::UtilityCost_RatchetFields::SeasonFrom, seasonFrom);
    }

    std::string UtilityCostRatchet_Impl::seasonTo() const {
      const boost::optional<std::string> value = getString(openstudio::UtilityCost_RatchetFields::SeasonTo, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostRatchet_Impl::setSeasonTo(const std::string& seasonTo) {
      return setAlphaField(this, openstudio::UtilityCost_RatchetFields::SeasonTo, seasonTo);
    }

    boost::optional<std::string> UtilityCostRatchet_Impl::multiplierValueorVariableName() const {
      return getString(openstudio::UtilityCost_RatchetFields::MultiplierValueorVariableName, true);
    }

    bool UtilityCostRatchet_Impl::setMultiplierValueorVariableName(const std::string& multiplierValueorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_RatchetFields::MultiplierValueorVariableName, multiplierValueorVariableName);
    }

    void UtilityCostRatchet_Impl::resetMultiplierValueorVariableName() {
      const bool result = setString(openstudio::UtilityCost_RatchetFields::MultiplierValueorVariableName, "");
      OS_ASSERT(result);
    }

    boost::optional<std::string> UtilityCostRatchet_Impl::offsetValueorVariableName() const {
      return getString(openstudio::UtilityCost_RatchetFields::OffsetValueorVariableName, true);
    }

    bool UtilityCostRatchet_Impl::setOffsetValueorVariableName(const std::string& offsetValueorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_RatchetFields::OffsetValueorVariableName, offsetValueorVariableName);
    }

    void UtilityCostRatchet_Impl::resetOffsetValueorVariableName() {
      const bool result = setString(openstudio::UtilityCost_RatchetFields::OffsetValueorVariableName, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
