/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHM_HPP
#define EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyHeatTransferAlgorithm_Impl;
  }

  class EPMODEL_API SurfacePropertyHeatTransferAlgorithm : public ModelObject
  {
   public:
    explicit SurfacePropertyHeatTransferAlgorithm(const Model& model);

    virtual ~SurfacePropertyHeatTransferAlgorithm() override = default;
    SurfacePropertyHeatTransferAlgorithm(const SurfacePropertyHeatTransferAlgorithm& other) = default;
    SurfacePropertyHeatTransferAlgorithm(SurfacePropertyHeatTransferAlgorithm&& other) = default;
    SurfacePropertyHeatTransferAlgorithm& operator=(const SurfacePropertyHeatTransferAlgorithm&) = default;
    SurfacePropertyHeatTransferAlgorithm& operator=(SurfacePropertyHeatTransferAlgorithm&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> algorithmValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the IDD-derived SurfacePropertyHeatTransferAlgorithm naming is preserved.
    // - Field Mapping: Surface Name is an object-list of SurfaceNames and therefore omitted from the scalar API surface.
    // - Field Mapping: Scalar algorithm APIs map directly to SurfaceProperty:HeatTransferAlgorithm Algorithm.
    // - TODO(parity): Add explicit surface reference helpers once relationship wiring matures.
    std::string algorithm() const;
    bool setAlgorithm(const std::string& algorithm);
    bool isAlgorithmDefaulted() const;
    void resetAlgorithm();

   protected:
    using ImplType = detail::SurfacePropertyHeatTransferAlgorithm_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyHeatTransferAlgorithm(std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithm_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
