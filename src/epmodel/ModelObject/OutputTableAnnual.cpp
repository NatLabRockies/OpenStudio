/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutputTableAnnual.hpp"
#include "OutputTableAnnual_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Output_Table_Annual_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  OutputTableAnnual::OutputTableAnnual(const Model& model) : ModelObject(OutputTableAnnual::iddObjectType(), model) {}

  OutputTableAnnual::OutputTableAnnual(std::shared_ptr<detail::OutputTableAnnual_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType OutputTableAnnual::iddObjectType() {
    return IddObjectType::Output_Table_Annual;
  }

  // Filter scalar accessor pairings
  boost::optional<std::string> OutputTableAnnual::filter() const {
    return getImpl<detail::OutputTableAnnual_Impl>()->filter();
  }

  bool OutputTableAnnual::setFilter(const std::string& filter) {
    return getImpl<detail::OutputTableAnnual_Impl>()->setFilter(filter);
  }

  void OutputTableAnnual::resetFilter() {
    getImpl<detail::OutputTableAnnual_Impl>()->resetFilter();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    // Filter scalar accessor pairings
    boost::optional<std::string> OutputTableAnnual_Impl::filter() const {
      if (isEmpty(openstudio::Output_Table_AnnualFields::Filter)) {
        return boost::none;
      }
      return getString(openstudio::Output_Table_AnnualFields::Filter, true);
    }

    bool OutputTableAnnual_Impl::setFilter(const std::string& filter) {
      return setString(openstudio::Output_Table_AnnualFields::Filter, filter);
    }

    void OutputTableAnnual_Impl::resetFilter() {
      const bool result = setString(openstudio::Output_Table_AnnualFields::Filter, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
