/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneContaminantSourceAndSinkGenericDecaySource.hpp"
#include "ZoneContaminantSourceAndSinkGenericDecaySource_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneContaminantSourceAndSink_Generic_DecaySource_FieldEnums.hxx>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace epmodel {

  ZoneContaminantSourceAndSinkGenericDecaySource::ZoneContaminantSourceAndSinkGenericDecaySource(const Model& model)
    : ModelObject(ZoneContaminantSourceAndSinkGenericDecaySource::iddObjectType(), model) {}

  ZoneContaminantSourceAndSinkGenericDecaySource::ZoneContaminantSourceAndSinkGenericDecaySource(
    std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneContaminantSourceAndSinkGenericDecaySource::iddObjectType() {
    return IddObjectType::ZoneContaminantSourceAndSink_Generic_DecaySource;
  }

  // Initial emission rate helpers
  boost::optional<double> ZoneContaminantSourceAndSinkGenericDecaySource::initialEmissionRate() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl>()->initialEmissionRate();
  }

  bool ZoneContaminantSourceAndSinkGenericDecaySource::setInitialEmissionRate(double initialEmissionRate) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl>()->setInitialEmissionRate(initialEmissionRate);
  }

  void ZoneContaminantSourceAndSinkGenericDecaySource::resetInitialEmissionRate() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl>()->resetInitialEmissionRate();
  }

  // Delay time constant helpers
  boost::optional<double> ZoneContaminantSourceAndSinkGenericDecaySource::delayTimeConstant() const {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl>()->delayTimeConstant();
  }

  bool ZoneContaminantSourceAndSinkGenericDecaySource::setDelayTimeConstant(double delayTimeConstant) {
    return getImpl<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl>()->setDelayTimeConstant(delayTimeConstant);
  }

  void ZoneContaminantSourceAndSinkGenericDecaySource::resetDelayTimeConstant() {
    getImpl<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl>()->resetDelayTimeConstant();
  }

  namespace detail {

    // Initial emission rate helpers
    boost::optional<double> ZoneContaminantSourceAndSinkGenericDecaySource_Impl::initialEmissionRate() const {
      return getDouble(ZoneContaminantSourceAndSink_Generic_DecaySourceFields::InitialEmissionRate, true);
    }

    bool ZoneContaminantSourceAndSinkGenericDecaySource_Impl::setInitialEmissionRate(double initialEmissionRate) {
      return setDouble(ZoneContaminantSourceAndSink_Generic_DecaySourceFields::InitialEmissionRate, initialEmissionRate);
    }

    void ZoneContaminantSourceAndSinkGenericDecaySource_Impl::resetInitialEmissionRate() {
      const bool result = setString(ZoneContaminantSourceAndSink_Generic_DecaySourceFields::InitialEmissionRate, "");
      OS_ASSERT(result);
    }

    // Delay time constant helpers
    boost::optional<double> ZoneContaminantSourceAndSinkGenericDecaySource_Impl::delayTimeConstant() const {
      return getDouble(ZoneContaminantSourceAndSink_Generic_DecaySourceFields::DelayTimeConstant, true);
    }

    bool ZoneContaminantSourceAndSinkGenericDecaySource_Impl::setDelayTimeConstant(double delayTimeConstant) {
      return setDouble(ZoneContaminantSourceAndSink_Generic_DecaySourceFields::DelayTimeConstant, delayTimeConstant);
    }

    void ZoneContaminantSourceAndSinkGenericDecaySource_Impl::resetDelayTimeConstant() {
      const bool result = setString(ZoneContaminantSourceAndSink_Generic_DecaySourceFields::DelayTimeConstant, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
