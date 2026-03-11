/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceContaminantSourceAndSinkGenericPressureDriven.hpp"
#include "SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceContaminantSourceAndSink_Generic_PressureDriven_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceContaminantSourceAndSinkGenericPressureDriven::SurfaceContaminantSourceAndSinkGenericPressureDriven(const Model& model)
    : ModelObject(SurfaceContaminantSourceAndSinkGenericPressureDriven::iddObjectType(), model) {}

  SurfaceContaminantSourceAndSinkGenericPressureDriven::SurfaceContaminantSourceAndSinkGenericPressureDriven(
    std::shared_ptr<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceContaminantSourceAndSinkGenericPressureDriven::iddObjectType() {
    return IddObjectType::SurfaceContaminantSourceAndSink_Generic_PressureDriven;
  }

  boost::optional<double> SurfaceContaminantSourceAndSinkGenericPressureDriven::designGenerationRateCoefficient() const {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>()->designGenerationRateCoefficient();
  }

  bool SurfaceContaminantSourceAndSinkGenericPressureDriven::setDesignGenerationRateCoefficient(double designGenerationRateCoefficient) {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>()->setDesignGenerationRateCoefficient(
      designGenerationRateCoefficient);
  }

  void SurfaceContaminantSourceAndSinkGenericPressureDriven::resetDesignGenerationRateCoefficient() {
    getImpl<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>()->resetDesignGenerationRateCoefficient();
  }

  boost::optional<double> SurfaceContaminantSourceAndSinkGenericPressureDriven::generationExponent() const {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>()->generationExponent();
  }

  bool SurfaceContaminantSourceAndSinkGenericPressureDriven::setGenerationExponent(double generationExponent) {
    return getImpl<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>()->setGenerationExponent(generationExponent);
  }

  void SurfaceContaminantSourceAndSinkGenericPressureDriven::resetGenerationExponent() {
    getImpl<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl>()->resetGenerationExponent();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl::designGenerationRateCoefficient() const {
      return getDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_PressureDrivenFields::DesignGenerationRateCoefficient, true);
    }

    bool SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl::setDesignGenerationRateCoefficient(double designGenerationRateCoefficient) {
      return setDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_PressureDrivenFields::DesignGenerationRateCoefficient,
                       designGenerationRateCoefficient);
    }

    void SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl::resetDesignGenerationRateCoefficient() {
      OS_ASSERT(setString(openstudio::SurfaceContaminantSourceAndSink_Generic_PressureDrivenFields::DesignGenerationRateCoefficient, ""));
    }

    boost::optional<double> SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl::generationExponent() const {
      return getDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_PressureDrivenFields::GenerationExponent, true);
    }

    bool SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl::setGenerationExponent(double generationExponent) {
      return setDouble(openstudio::SurfaceContaminantSourceAndSink_Generic_PressureDrivenFields::GenerationExponent, generationExponent);
    }

    void SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl::resetGenerationExponent() {
      OS_ASSERT(setString(openstudio::SurfaceContaminantSourceAndSink_Generic_PressureDrivenFields::GenerationExponent, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
