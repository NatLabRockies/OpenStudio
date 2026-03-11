/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGSITEDETAILED_HPP
#define EPMODEL_SHADINGSITEDETAILED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ShadingSiteDetailed_Impl;
}

class EPMODEL_API ShadingSiteDetailed : public ModelObject
{
 public:
  explicit ShadingSiteDetailed(const Model& model);

  virtual ~ShadingSiteDetailed() override = default;
  ShadingSiteDetailed(const ShadingSiteDetailed& other) = default;
  ShadingSiteDetailed(ShadingSiteDetailed&& other) = default;
  ShadingSiteDetailed& operator=(const ShadingSiteDetailed&) = default;
  ShadingSiteDetailed& operator=(ShadingSiteDetailed&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: numberofVertices maps directly to EnergyPlus Shading:Site:Detailed / Number of Vertices.
  // - Field Mapping: Name is inherited from ModelObject scalar API and maps to Shading:Site:Detailed / Name.
  // - Field Mapping: Transmittance Schedule Name is a relationship field and is intentionally excluded from scalar accessors.
  // - Field Mapping: Extensible Vertex X/Y/Z coordinate groups are non-scalar geometry data and are intentionally excluded.
  // - ForwardTranslator Evidence: ShadingSurface translation writes Name/Transmittance Schedule Name to
  //   Shading:Site:Detailed, while geometry and reverse translation read/write Number of Vertices with extensible vertices.
  // - TODO(parity): Add relationship/extensible geometry APIs after scalar scaffold saturation.
  boost::optional<int> numberofVertices() const;
  bool setNumberofVertices(int numberofVertices);
  bool isNumberofVerticesAutocalculated() const;
  void autocalculateNumberofVertices();
  void resetNumberofVertices();

 protected:
  using ImplType = detail::ShadingSiteDetailed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ShadingSiteDetailed(std::shared_ptr<detail::ShadingSiteDetailed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
