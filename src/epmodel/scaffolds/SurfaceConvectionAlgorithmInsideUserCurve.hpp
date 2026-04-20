/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMINSIDEUSERCURVE_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMINSIDEUSERCURVE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceConvectionAlgorithmInsideUserCurve_Impl;
  }

  class EPMODEL_API SurfaceConvectionAlgorithmInsideUserCurve : public ModelObject
  {
   public:
    explicit SurfaceConvectionAlgorithmInsideUserCurve(const Model& model);

    virtual ~SurfaceConvectionAlgorithmInsideUserCurve() override = default;
    SurfaceConvectionAlgorithmInsideUserCurve(const SurfaceConvectionAlgorithmInsideUserCurve& other) = default;
    SurfaceConvectionAlgorithmInsideUserCurve(SurfaceConvectionAlgorithmInsideUserCurve&& other) = default;
    SurfaceConvectionAlgorithmInsideUserCurve& operator=(const SurfaceConvectionAlgorithmInsideUserCurve&) = default;
    SurfaceConvectionAlgorithmInsideUserCurve& operator=(SurfaceConvectionAlgorithmInsideUserCurve&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> referenceTemperatureforConvectionHeatTransferValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to SurfaceConvectionAlgorithm:Inside:UserCurve choice fields.
    // - Field Mapping: Hc Function curve name fields (A3-A6) are excluded as object-list relationship fields.
    // - TODO(parity): Add relationship APIs for curve linkage fields after scalar saturation.
    /** @name Reference temperature accessors */
    //@{
    boost::optional<std::string> referenceTemperatureforConvectionHeatTransfer() const;
    bool setReferenceTemperatureforConvectionHeatTransfer(const std::string& referenceTemperatureforConvectionHeatTransfer);
    void resetReferenceTemperatureforConvectionHeatTransfer();
    //@}

   protected:
    using ImplType = detail::SurfaceConvectionAlgorithmInsideUserCurve_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceConvectionAlgorithmInsideUserCurve(std::shared_ptr<detail::SurfaceConvectionAlgorithmInsideUserCurve_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
