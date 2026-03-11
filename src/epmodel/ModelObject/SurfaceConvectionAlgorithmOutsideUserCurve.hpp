/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEUSERCURVE_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMOUTSIDEUSERCURVE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceConvectionAlgorithmOutsideUserCurve_Impl;
  }

  class EPMODEL_API SurfaceConvectionAlgorithmOutsideUserCurve : public ModelObject
  {
   public:
    explicit SurfaceConvectionAlgorithmOutsideUserCurve(const Model& model);

    virtual ~SurfaceConvectionAlgorithmOutsideUserCurve() override = default;
    SurfaceConvectionAlgorithmOutsideUserCurve(const SurfaceConvectionAlgorithmOutsideUserCurve& other) = default;
    SurfaceConvectionAlgorithmOutsideUserCurve(SurfaceConvectionAlgorithmOutsideUserCurve&& other) = default;
    SurfaceConvectionAlgorithmOutsideUserCurve& operator=(const SurfaceConvectionAlgorithmOutsideUserCurve&) = default;
    SurfaceConvectionAlgorithmOutsideUserCurve& operator=(SurfaceConvectionAlgorithmOutsideUserCurve&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> windSpeedTypeforCurveValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: windSpeedTypeforCurve maps to SurfaceConvectionAlgorithm:Outside:UserCurve field "Wind Speed Type for Curve".
    // - Field Mapping: Hf/Hn Function curve name fields (A3-A5) are excluded as object-list relationship fields.
    // - TODO(parity): Add relationship APIs for curve linkage fields after scalar saturation.
    std::string windSpeedTypeforCurve() const;
    bool isWindSpeedTypeforCurveDefaulted() const;
    bool setWindSpeedTypeforCurve(const std::string& windSpeedTypeforCurve);
    void resetWindSpeedTypeforCurve();

   protected:
    using ImplType = detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceConvectionAlgorithmOutsideUserCurve(std::shared_ptr<detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
