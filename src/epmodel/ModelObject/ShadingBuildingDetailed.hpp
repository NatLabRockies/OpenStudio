/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGBUILDINGDETAILED_HPP
#define EPMODEL_SHADINGBUILDINGDETAILED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingBuildingDetailed_Impl;
}

class EPMODEL_API ShadingBuildingDetailed : public ModelObject
{
 public:
  explicit ShadingBuildingDetailed(const Model& model);

  virtual ~ShadingBuildingDetailed() override = default;
  ShadingBuildingDetailed(const ShadingBuildingDetailed& other) = default;
  ShadingBuildingDetailed(ShadingBuildingDetailed&& other) = default;
  ShadingBuildingDetailed& operator=(const ShadingBuildingDetailed&) = default;
  ShadingBuildingDetailed& operator=(ShadingBuildingDetailed&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: numberofVertices maps directly to EnergyPlus Shading:Building:Detailed / Number of Vertices.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Building:Detailed / Name.
  // - Field Mapping: Transmittance Schedule Name is a relationship field and is intentionally excluded from scalar accessors.
  // - Field Mapping: Extensible Vertex X/Y/Z coordinate groups are non-scalar geometry data and are intentionally excluded.
  // - ForwardTranslator Evidence: ShadingSurface translation writes Name/Transmittance Schedule Name, while geometry
  //   translation and reverse translation read/write Number of Vertices with extensible vertices.
  // - TODO(parity): Add relationship/extensible geometry APIs after scalar scaffold saturation.
  boost::optional<int> numberofVertices() const;
  bool setNumberofVertices(int numberofVertices);
  bool isNumberofVerticesAutocalculated() const;
  void autocalculateNumberofVertices();
  void resetNumberofVertices();

 protected:
  using ImplType = detail::ShadingBuildingDetailed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingBuildingDetailed(std::shared_ptr<detail::ShadingBuildingDetailed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
