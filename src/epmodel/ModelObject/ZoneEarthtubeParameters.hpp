/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEEARTHTUBEPARAMETERS_HPP
#define EPMODEL_ZONEEARTHTUBEPARAMETERS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneEarthtubeParameters_Impl;
  }

  class EPMODEL_API ZoneEarthtubeParameters : public ModelObject
  {
   public:
    explicit ZoneEarthtubeParameters(const Model& model);

    virtual ~ZoneEarthtubeParameters() override = default;
    ZoneEarthtubeParameters(const ZoneEarthtubeParameters& other) = default;
    ZoneEarthtubeParameters(ZoneEarthtubeParameters&& other) = default;
    ZoneEarthtubeParameters& operator=(const ZoneEarthtubeParameters&) = default;
    ZoneEarthtubeParameters& operator=(ZoneEarthtubeParameters&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so this class mirrors the ZoneEarthtube:Parameters IDD entry directly.
    // - Field Mapping: Earth Tube Model Parameters Name is a reference to EarthTubeParameterNames and is excluded from this scalar-only pass.
    // - Field Mapping: The remaining fields map to EnergyPlus ZoneEarthtube:Parameters basic scalars via ZoneEarthtube_ParametersFields.
    // - TODO(parity): Add relationship helpers once scalar saturation completes.
    int nodesAboveEarthTube() const;
    bool isNodesAboveEarthTubeDefaulted() const;
    bool setNodesAboveEarthTube(int nodesAboveEarthTube);
    void resetNodesAboveEarthTube();

    int nodesBelowEarthTube() const;
    bool isNodesBelowEarthTubeDefaulted() const;
    bool setNodesBelowEarthTube(int nodesBelowEarthTube);
    void resetNodesBelowEarthTube();

    double earthTubeDimensionlessBoundaryAbove() const;
    bool isEarthTubeDimensionlessBoundaryAboveDefaulted() const;
    bool setEarthTubeDimensionlessBoundaryAbove(double earthTubeDimensionlessBoundaryAbove);
    void resetEarthTubeDimensionlessBoundaryAbove();

    double earthTubeDimensionlessBoundaryBelow() const;
    bool isEarthTubeDimensionlessBoundaryBelowDefaulted() const;
    bool setEarthTubeDimensionlessBoundaryBelow(double earthTubeDimensionlessBoundaryBelow);
    void resetEarthTubeDimensionlessBoundaryBelow();

    double earthTubeSolutionSpaceWidth() const;
    bool isEarthTubeSolutionSpaceWidthDefaulted() const;
    bool setEarthTubeSolutionSpaceWidth(double earthTubeSolutionSpaceWidth);
    void resetEarthTubeSolutionSpaceWidth();

   protected:
    using ImplType = detail::ZoneEarthtubeParameters_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneEarthtubeParameters(std::shared_ptr<detail::ZoneEarthtubeParameters_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
