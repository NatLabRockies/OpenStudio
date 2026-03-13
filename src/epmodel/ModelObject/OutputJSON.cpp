/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/OutputJSON.hpp"
#include "ModelObject/OutputJSON_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Output_JSON_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputJSON::OutputJSON(const Model& model) : ModelObject(OutputJSON::iddObjectType(), model) {
    bool ok = setOptionType("TimeSeriesAndTabular");
    OS_ASSERT(ok);

    ok = setOutputJSON(true);
    OS_ASSERT(ok);

    ok = setOutputCBOR(false);
    OS_ASSERT(ok);

    ok = setOutputMessagePack(false);
    OS_ASSERT(ok);
  }

  OutputJSON::OutputJSON(std::shared_ptr<detail::OutputJSON_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputJSON::iddObjectType() {
    return IddObjectType::Output_JSON;
  }

  std::vector<std::string> OutputJSON::optionTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Output_JSONFields::OptionType);
  }

  std::string OutputJSON::optionType() const {
    return getImpl<detail::OutputJSON_Impl>()->optionType();
  }

  bool OutputJSON::setOptionType(const std::string& optionType) {
    return getImpl<detail::OutputJSON_Impl>()->setOptionType(optionType);
  }

  bool OutputJSON::outputJSON() const {
    return getImpl<detail::OutputJSON_Impl>()->outputJSON();
  }

  bool OutputJSON::setOutputJSON(bool outputJSON) {
    return getImpl<detail::OutputJSON_Impl>()->setOutputJSON(outputJSON);
  }

  bool OutputJSON::outputCBOR() const {
    return getImpl<detail::OutputJSON_Impl>()->outputCBOR();
  }

  bool OutputJSON::setOutputCBOR(bool outputCBOR) {
    return getImpl<detail::OutputJSON_Impl>()->setOutputCBOR(outputCBOR);
  }

  bool OutputJSON::outputMessagePack() const {
    return getImpl<detail::OutputJSON_Impl>()->outputMessagePack();
  }

  bool OutputJSON::setOutputMessagePack(bool outputMessagePack) {
    return getImpl<detail::OutputJSON_Impl>()->setOutputMessagePack(outputMessagePack);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OutputJSON_Impl::optionType() const {
      const auto value = getString(openstudio::Output_JSONFields::OptionType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutputJSON_Impl::setOptionType(const std::string& optionType) {
      return setString(openstudio::Output_JSONFields::OptionType, optionType);
    }

    bool OutputJSON_Impl::outputJSON() const {
      if (const auto value = getString(openstudio::Output_JSONFields::OutputJSON, true)) {
        return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
      }
      return false;
    }

    bool OutputJSON_Impl::setOutputJSON(bool outputJSON) {
      const bool result = setString(openstudio::Output_JSONFields::OutputJSON, outputJSON ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    bool OutputJSON_Impl::outputCBOR() const {
      if (const auto value = getString(openstudio::Output_JSONFields::OutputCBOR, true)) {
        return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
      }
      return false;
    }

    bool OutputJSON_Impl::setOutputCBOR(bool outputCBOR) {
      const bool result = setString(openstudio::Output_JSONFields::OutputCBOR, outputCBOR ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    bool OutputJSON_Impl::outputMessagePack() const {
      if (const auto value = getString(openstudio::Output_JSONFields::OutputMessagePack, true)) {
        return openstudio::istringEqual(*value, "Yes") || openstudio::istringEqual(*value, "True");
      }
      return false;
    }

    bool OutputJSON_Impl::setOutputMessagePack(bool outputMessagePack) {
      const bool result = setString(openstudio::Output_JSONFields::OutputMessagePack, outputMessagePack ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    std::vector<std::string> OutputJSON_Impl::optionTypeValues() const {
      return openstudio::epmodel::OutputJSON::optionTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
