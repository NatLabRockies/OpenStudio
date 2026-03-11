/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneContaminantSourceAndSinkGenericDepositionRateSink.hpp"
#include "ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneContaminantSourceAndSink_Generic_DepositionRateSink_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

  ZoneContaminantSourceAndSinkGenericDepositionRateSink::ZoneContaminantSourceAndSinkGenericDepositionRateSink(const Model& model)
    : ModelObject(ZoneContaminantSourceAndSinkGenericDepositionRateSink::iddObjectType(), model) {}

  ZoneContaminantSourceAndSinkGenericDepositionRateSink::ZoneContaminantSourceAndSinkGenericDepositionRateSink(
    std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneContaminantSourceAndSinkGenericDepositionRateSink::iddObjectType() {
    return IddObjectType::ZoneContaminantSourceAndSink_Generic_DepositionRateSink;
  }

  boost::optional<double> ZoneContaminantSourceAndSinkGenericDepositionRateSink::depositionRate() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl>()->depositionRate();
  }

  bool ZoneContaminantSourceAndSinkGenericDepositionRateSink::setDepositionRate(double depositionRate) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl>()->setDepositionRate(depositionRate);
  }

  void ZoneContaminantSourceAndSinkGenericDepositionRateSink::resetDepositionRate() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl>()->resetDepositionRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl::depositionRate() const {
      return getDouble(ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::DepositionRate, true);
    }

    bool ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl::setDepositionRate(double depositionRate) {
      return setDouble(ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::DepositionRate, depositionRate);
    }

    void ZoneContaminantSourceAndSinkGenericDepositionRateSink_Impl::resetDepositionRate() {
      const bool result = setString(ZoneContaminantSourceAndSink_Generic_DepositionRateSinkFields::DepositionRate, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
