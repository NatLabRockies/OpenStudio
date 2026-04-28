/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostChargeBlock.hpp"
#include "UtilityCostChargeBlock_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/UtilityCost_Charge_Block_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  UtilityCostChargeBlock::UtilityCostChargeBlock(const Model& model) : ModelObject(UtilityCostChargeBlock::iddObjectType(), model, true) {}

  UtilityCostChargeBlock::UtilityCostChargeBlock(std::shared_ptr<detail::UtilityCostChargeBlock_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostChargeBlock::iddObjectType() {
    return IddObjectType::UtilityCost_Charge_Block;
  }

  std::vector<std::string> UtilityCostChargeBlock::seasonValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_Charge_BlockFields::Season);
  }

  std::vector<std::string> UtilityCostChargeBlock::categoryVariableNameValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_Charge_BlockFields::CategoryVariableName);
  }

  std::string UtilityCostChargeBlock::sourceVariable() const {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->sourceVariable();
  }

  bool UtilityCostChargeBlock::setSourceVariable(const std::string& sourceVariable) {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->setSourceVariable(sourceVariable);
  }

  std::string UtilityCostChargeBlock::season() const {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->season();
  }

  bool UtilityCostChargeBlock::setSeason(const std::string& season) {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->setSeason(season);
  }

  bool UtilityCostChargeBlock::isSeasonDefaulted() const {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->isSeasonDefaulted();
  }

  void UtilityCostChargeBlock::resetSeason() {
    getImpl<detail::UtilityCostChargeBlock_Impl>()->resetSeason();
  }

  std::string UtilityCostChargeBlock::categoryVariableName() const {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->categoryVariableName();
  }

  bool UtilityCostChargeBlock::setCategoryVariableName(const std::string& categoryVariableName) {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->setCategoryVariableName(categoryVariableName);
  }

  boost::optional<std::string> UtilityCostChargeBlock::remainingIntoVariable() const {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->remainingIntoVariable();
  }

  bool UtilityCostChargeBlock::setRemainingIntoVariable(const std::string& remainingIntoVariable) {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->setRemainingIntoVariable(remainingIntoVariable);
  }

  void UtilityCostChargeBlock::resetRemainingIntoVariable() {
    getImpl<detail::UtilityCostChargeBlock_Impl>()->resetRemainingIntoVariable();
  }

  boost::optional<std::string> UtilityCostChargeBlock::blockSizeMultiplierValueorVariableName() const {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->blockSizeMultiplierValueorVariableName();
  }

  bool UtilityCostChargeBlock::setBlockSizeMultiplierValueorVariableName(const std::string& blockSizeMultiplierValueorVariableName) {
    return getImpl<detail::UtilityCostChargeBlock_Impl>()->setBlockSizeMultiplierValueorVariableName(blockSizeMultiplierValueorVariableName);
  }

  void UtilityCostChargeBlock::resetBlockSizeMultiplierValueorVariableName() {
    getImpl<detail::UtilityCostChargeBlock_Impl>()->resetBlockSizeMultiplierValueorVariableName();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      bool setAlphaField(UtilityCostChargeBlock_Impl* impl, unsigned fieldIndex, const std::string& value) {
        if (impl->setString(fieldIndex, value)) {
          return true;
        }
        return impl->setString(fieldIndex, value, false);
      }
    }  // namespace

    std::string UtilityCostChargeBlock_Impl::sourceVariable() const {
      const auto value = getString(openstudio::UtilityCost_Charge_BlockFields::SourceVariable, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostChargeBlock_Impl::setSourceVariable(const std::string& sourceVariable) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_BlockFields::SourceVariable, sourceVariable);
    }

    std::string UtilityCostChargeBlock_Impl::season() const {
      const auto value = getString(openstudio::UtilityCost_Charge_BlockFields::Season, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostChargeBlock_Impl::setSeason(const std::string& season) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_BlockFields::Season, season);
    }

    bool UtilityCostChargeBlock_Impl::isSeasonDefaulted() const {
      return isEmpty(openstudio::UtilityCost_Charge_BlockFields::Season);
    }

    void UtilityCostChargeBlock_Impl::resetSeason() {
      OS_ASSERT(setString(openstudio::UtilityCost_Charge_BlockFields::Season, ""));
    }

    std::string UtilityCostChargeBlock_Impl::categoryVariableName() const {
      const auto value = getString(openstudio::UtilityCost_Charge_BlockFields::CategoryVariableName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostChargeBlock_Impl::setCategoryVariableName(const std::string& categoryVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_BlockFields::CategoryVariableName, categoryVariableName);
    }

    boost::optional<std::string> UtilityCostChargeBlock_Impl::remainingIntoVariable() const {
      return getString(openstudio::UtilityCost_Charge_BlockFields::RemainingIntoVariable, true);
    }

    bool UtilityCostChargeBlock_Impl::setRemainingIntoVariable(const std::string& remainingIntoVariable) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_BlockFields::RemainingIntoVariable, remainingIntoVariable);
    }

    void UtilityCostChargeBlock_Impl::resetRemainingIntoVariable() {
      OS_ASSERT(setString(openstudio::UtilityCost_Charge_BlockFields::RemainingIntoVariable, ""));
    }

    boost::optional<std::string> UtilityCostChargeBlock_Impl::blockSizeMultiplierValueorVariableName() const {
      return getString(openstudio::UtilityCost_Charge_BlockFields::BlockSizeMultiplierValueorVariableName, true);
    }

    bool UtilityCostChargeBlock_Impl::setBlockSizeMultiplierValueorVariableName(const std::string& blockSizeMultiplierValueorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_Charge_BlockFields::BlockSizeMultiplierValueorVariableName,
                           blockSizeMultiplierValueorVariableName);
    }

    void UtilityCostChargeBlock_Impl::resetBlockSizeMultiplierValueorVariableName() {
      OS_ASSERT(setString(openstudio::UtilityCost_Charge_BlockFields::BlockSizeMultiplierValueorVariableName, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
