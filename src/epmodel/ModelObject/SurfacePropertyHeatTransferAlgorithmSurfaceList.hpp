/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMSURFACELIST_HPP
#define EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMSURFACELIST_HPP

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
    class SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl;
  }

  class EPMODEL_API SurfacePropertyHeatTransferAlgorithmSurfaceList : public ModelObject
  {
   public:
    explicit SurfacePropertyHeatTransferAlgorithmSurfaceList(const Model& model);

    virtual ~SurfacePropertyHeatTransferAlgorithmSurfaceList() override = default;
    SurfacePropertyHeatTransferAlgorithmSurfaceList(const SurfacePropertyHeatTransferAlgorithmSurfaceList& other) = default;
    SurfacePropertyHeatTransferAlgorithmSurfaceList(SurfacePropertyHeatTransferAlgorithmSurfaceList&& other) = default;
    SurfacePropertyHeatTransferAlgorithmSurfaceList& operator=(const SurfacePropertyHeatTransferAlgorithmSurfaceList&) = default;
    SurfacePropertyHeatTransferAlgorithmSurfaceList& operator=(SurfacePropertyHeatTransferAlgorithmSurfaceList&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> algorithmValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so the IDD-derived SurfacePropertyHeatTransferAlgorithmSurfaceList naming is preserved.
    // - Field Mapping: Surface Name is an object-list (SurfaceNames) and therefore excluded from the scalar API surface.
    // - Field Mapping: algorithm() and related helpers delegate directly to SurfaceProperty:HeatTransferAlgorithm:SurfaceList Algorithm.
    std::string algorithm() const;
    bool setAlgorithm(const std::string& algorithm);
    bool isAlgorithmDefaulted() const;
    void resetAlgorithm();

   protected:
    using ImplType = detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyHeatTransferAlgorithmSurfaceList(std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
