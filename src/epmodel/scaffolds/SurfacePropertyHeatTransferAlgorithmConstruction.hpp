/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMCONSTRUCTION_HPP
#define EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMCONSTRUCTION_HPP

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
    class SurfacePropertyHeatTransferAlgorithmConstruction_Impl;
  }

  class EPMODEL_API SurfacePropertyHeatTransferAlgorithmConstruction : public ModelObject
  {
   public:
    explicit SurfacePropertyHeatTransferAlgorithmConstruction(const Model& model);

    virtual ~SurfacePropertyHeatTransferAlgorithmConstruction() override = default;
    SurfacePropertyHeatTransferAlgorithmConstruction(const SurfacePropertyHeatTransferAlgorithmConstruction& other) = default;
    SurfacePropertyHeatTransferAlgorithmConstruction(SurfacePropertyHeatTransferAlgorithmConstruction&& other) = default;
    SurfacePropertyHeatTransferAlgorithmConstruction& operator=(const SurfacePropertyHeatTransferAlgorithmConstruction&) = default;
    SurfacePropertyHeatTransferAlgorithmConstruction& operator=(SurfacePropertyHeatTransferAlgorithmConstruction&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> algorithmValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the IDD-derived SurfacePropertyHeatTransferAlgorithmConstruction naming is preserved.
    // - Field Mapping: Construction Name is an object-list (ConstructionNames) and therefore excluded from the scalar API.
    // - Field Mapping: Scalar algorithm APIs map directly to SurfaceProperty:HeatTransferAlgorithm:Construction Algorithm.
    std::string algorithm() const;
    bool setAlgorithm(const std::string& algorithm);
    bool isAlgorithmDefaulted() const;
    void resetAlgorithm();

   protected:
    using ImplType = detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyHeatTransferAlgorithmConstruction(std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
