/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputControlIlluminanceMapStyle.hpp"
#include "OutputControlIlluminanceMapStyle_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutputControl_IlluminanceMap_Style_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputControlIlluminanceMapStyle::OutputControlIlluminanceMapStyle(const Model& model)
    : ModelObject(OutputControlIlluminanceMapStyle::iddObjectType(), model) {}

  OutputControlIlluminanceMapStyle::OutputControlIlluminanceMapStyle(std::shared_ptr<detail::OutputControlIlluminanceMapStyle_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType OutputControlIlluminanceMapStyle::iddObjectType() {
    return IddObjectType::OutputControl_IlluminanceMap_Style;
  }

  std::vector<std::string> OutputControlIlluminanceMapStyle::columnSeparatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::OutputControl_IlluminanceMap_StyleFields::ColumnSeparator);
  }

  std::string OutputControlIlluminanceMapStyle::columnSeparator() const {
    return getImpl<detail::OutputControlIlluminanceMapStyle_Impl>()->columnSeparator();
  }

  bool OutputControlIlluminanceMapStyle::isColumnSeparatorDefaulted() const {
    return getImpl<detail::OutputControlIlluminanceMapStyle_Impl>()->isColumnSeparatorDefaulted();
  }

  bool OutputControlIlluminanceMapStyle::setColumnSeparator(const std::string& columnSeparator) {
    return getImpl<detail::OutputControlIlluminanceMapStyle_Impl>()->setColumnSeparator(columnSeparator);
  }

  void OutputControlIlluminanceMapStyle::resetColumnSeparator() {
    getImpl<detail::OutputControlIlluminanceMapStyle_Impl>()->resetColumnSeparator();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> OutputControlIlluminanceMapStyle_Impl::columnSeparatorValues() const {
      return openstudio::epmodel::OutputControlIlluminanceMapStyle::columnSeparatorValues();
    }

    std::string OutputControlIlluminanceMapStyle_Impl::columnSeparator() const {
      if (auto value = getString(openstudio::OutputControl_IlluminanceMap_StyleFields::ColumnSeparator, false)) {
        if (!value->empty()) {
          return *value;
        }
      }
      return "Comma";
    }

    bool OutputControlIlluminanceMapStyle_Impl::isColumnSeparatorDefaulted() const {
      return isEmpty(openstudio::OutputControl_IlluminanceMap_StyleFields::ColumnSeparator);
    }

    bool OutputControlIlluminanceMapStyle_Impl::setColumnSeparator(const std::string& columnSeparator) {
      return setString(openstudio::OutputControl_IlluminanceMap_StyleFields::ColumnSeparator, columnSeparator);
    }

    void OutputControlIlluminanceMapStyle_Impl::resetColumnSeparator() {
      OS_ASSERT(setString(openstudio::OutputControl_IlluminanceMap_StyleFields::ColumnSeparator, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
