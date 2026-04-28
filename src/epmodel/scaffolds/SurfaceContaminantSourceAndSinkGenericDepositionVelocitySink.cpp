/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink.hpp"
#include "SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySink_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink(const Model& model)
    : ModelObject(SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::iddObjectType(), model) {}

  SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink(
    std::shared_ptr<detail::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::iddObjectType() {
    return IddObjectType::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySink;
  }

  boost::optional<double> SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::depositionVelocity() const {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl>()->depositionVelocity();
  }

  bool SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::setDepositionVelocity(double depositionVelocity) {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl>()->setDepositionVelocity(depositionVelocity);
  }

  void SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink::resetDepositionVelocity() {
    getImpl<detail::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl>()->resetDepositionVelocity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl::depositionVelocity() const {
      return getDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySinkFields::DepositionVelocity, true);
    }

    bool SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl::setDepositionVelocity(double depositionVelocity) {
      return setDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySinkFields::DepositionVelocity, depositionVelocity);
    }

    void SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl::resetDepositionVelocity() {
      OS_ASSERT(setString(openstudio::SurfaceContaminantSourceAndSink_Generic_DepositionVelocitySinkFields::DepositionVelocity, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
