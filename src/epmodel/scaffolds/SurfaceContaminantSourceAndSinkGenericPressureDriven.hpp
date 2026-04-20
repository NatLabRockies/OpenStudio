/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICPRESSUREDRIVEN_HPP
#define EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICPRESSUREDRIVEN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl;
  }

  class EPMODEL_API SurfaceContaminantSourceAndSinkGenericPressureDriven : public ModelObject
  {
   public:
    explicit SurfaceContaminantSourceAndSinkGenericPressureDriven(const Model& model);

    virtual ~SurfaceContaminantSourceAndSinkGenericPressureDriven() override = default;
    SurfaceContaminantSourceAndSinkGenericPressureDriven(const SurfaceContaminantSourceAndSinkGenericPressureDriven& other) = default;
    SurfaceContaminantSourceAndSinkGenericPressureDriven(SurfaceContaminantSourceAndSinkGenericPressureDriven&& other) = default;
    SurfaceContaminantSourceAndSinkGenericPressureDriven& operator=(const SurfaceContaminantSourceAndSinkGenericPressureDriven&) = default;
    SurfaceContaminantSourceAndSinkGenericPressureDriven& operator=(SurfaceContaminantSourceAndSinkGenericPressureDriven&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to SurfaceContaminantSourceAndSink:Generic:PressureDriven numeric fields.
    // - Field Mapping: Surface Name and Generation Schedule Name linkage fields remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.

    boost::optional<double> designGenerationRateCoefficient() const;
    bool setDesignGenerationRateCoefficient(double designGenerationRateCoefficient);
    void resetDesignGenerationRateCoefficient();

    boost::optional<double> generationExponent() const;
    bool setGenerationExponent(double generationExponent);
    void resetGenerationExponent();

   protected:
    using ImplType = detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceContaminantSourceAndSinkGenericPressureDriven(
      std::shared_ptr<detail::SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
