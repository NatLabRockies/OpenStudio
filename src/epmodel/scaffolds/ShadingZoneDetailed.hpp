/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGZONEDETAILED_HPP
#define EPMODEL_SHADINGZONEDETAILED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ShadingZoneDetailed_Impl;
  }

  class EPMODEL_API ShadingZoneDetailed : public ModelObject
  {
   public:
    explicit ShadingZoneDetailed(const Model& model);

    virtual ~ShadingZoneDetailed() override = default;
    ShadingZoneDetailed(const ShadingZoneDetailed& other) = default;
    ShadingZoneDetailed(ShadingZoneDetailed&& other) = default;
    ShadingZoneDetailed& operator=(const ShadingZoneDetailed&) = default;
    ShadingZoneDetailed& operator=(ShadingZoneDetailed&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: numberofVertices maps directly to EnergyPlus Shading:Zone:Detailed / Number of Vertices.
    // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Zone:Detailed / Name.
    // - Field Mapping: Base Surface Name and Transmittance Schedule Name are relationship fields and are intentionally
    //   excluded from scalar accessors.
    // - Field Mapping: Extensible Vertex X/Y/Z coordinate groups are non-scalar geometry data and are intentionally excluded.
    // - ForwardTranslator Evidence: ShadingSurface translation writes Name/Base Surface Name/Transmittance Schedule Name to
    //   Shading:Zone:Detailed; geometry/reverse translation read/write Number of Vertices with extensible vertices.
    // - TODO(parity): Add relationship/extensible geometry APIs after scalar scaffold saturation.

    /** @name Number of Vertices */
    //@{
    boost::optional<int> numberofVertices() const;
    bool setNumberofVertices(int numberofVertices);
    bool isNumberofVerticesAutocalculated() const;
    void autocalculateNumberofVertices();
    void resetNumberofVertices();
    //@}

   protected:
    using ImplType = detail::ShadingZoneDetailed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ShadingZoneDetailed(std::shared_ptr<detail::ShadingZoneDetailed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
