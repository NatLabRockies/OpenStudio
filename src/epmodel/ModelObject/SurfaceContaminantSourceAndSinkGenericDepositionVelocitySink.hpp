/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONVELOCITYSINK_HPP
#define EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONVELOCITYSINK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl;
  }

  class EPMODEL_API SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink : public ModelObject
  {
   public:
    explicit SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink(const Model& model);

    virtual ~SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink() override = default;
    SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink(const SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink& other) = default;
    SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink(SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink&& other) = default;
    SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink&
      operator=(const SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink&) = default;
    SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink& operator=(SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to SurfaceContaminantSourceAndSink:Generic:DepositionVelocitySink numeric fields.
    // - Field Mapping: Surface Name and Schedule Name linkage fields remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    boost::optional<double> depositionVelocity() const;
    bool setDepositionVelocity(double depositionVelocity);
    void resetDepositionVelocity();

   protected:
    using ImplType = detail::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink(
      std::shared_ptr<detail::SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
