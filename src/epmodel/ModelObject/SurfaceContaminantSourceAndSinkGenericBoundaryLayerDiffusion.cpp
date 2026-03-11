/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion.hpp"
#include "SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusion_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion(const Model& model)
    : ModelObject(SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::iddObjectType(), model) {}

  SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion(
    std::shared_ptr<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::iddObjectType() {
    return IddObjectType::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusion;
  }

  boost::optional<double> SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::massTransferCoefficient() const {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>()->massTransferCoefficient();
  }

  bool SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::setMassTransferCoefficient(double massTransferCoefficient) {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>()->setMassTransferCoefficient(massTransferCoefficient);
  }

  void SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::resetMassTransferCoefficient() {
    getImpl<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>()->resetMassTransferCoefficient();
  }

  boost::optional<double> SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::henryAdsorptionConstantorPartitionCoefficient() const {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>()->henryAdsorptionConstantorPartitionCoefficient();
  }

  bool SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::setHenryAdsorptionConstantorPartitionCoefficient(
    double henryAdsorptionConstantorPartitionCoefficient) {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>()->setHenryAdsorptionConstantorPartitionCoefficient(
      henryAdsorptionConstantorPartitionCoefficient);
  }

  void SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion::resetHenryAdsorptionConstantorPartitionCoefficient() {
    getImpl<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl>()->resetHenryAdsorptionConstantorPartitionCoefficient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl::massTransferCoefficient() const {
      return getDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::MassTransferCoefficient, true);
    }

    bool SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl::setMassTransferCoefficient(double massTransferCoefficient) {
      return setDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::MassTransferCoefficient,
                       massTransferCoefficient);
    }

    void SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl::resetMassTransferCoefficient() {
      OS_ASSERT(setString(openstudio::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::MassTransferCoefficient, ""));
    }

    boost::optional<double> SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl::henryAdsorptionConstantorPartitionCoefficient() const {
      return getDouble(
        openstudio::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::HenryAdsorptionConstantorPartitionCoefficient, true);
    }

    bool SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl::setHenryAdsorptionConstantorPartitionCoefficient(
      double henryAdsorptionConstantorPartitionCoefficient) {
      return setDouble(
        openstudio::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::HenryAdsorptionConstantorPartitionCoefficient,
        henryAdsorptionConstantorPartitionCoefficient);
    }

    void SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl::resetHenryAdsorptionConstantorPartitionCoefficient() {
      OS_ASSERT(setString(
        openstudio::SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::HenryAdsorptionConstantorPartitionCoefficient, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
