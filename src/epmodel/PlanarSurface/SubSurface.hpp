/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACE_HPP
#define EPMODEL_SUBSURFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SubSurface_Impl;
}

class EPMODEL_API SubSurface : public ModelObject
{
 public:
  explicit SubSurface(const Model& model);

  virtual ~SubSurface() override = default;
  SubSurface(const SubSurface& other) = default;
  SubSurface(SubSurface&& other) = default;
  SubSurface& operator=(const SubSurface&) = default;
  SubSurface& operator=(SubSurface&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validSubSurfaceTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::SubSurface scalar accessor names/signatures.
  // - Field Mapping: These APIs map to FenestrationSurface:Detailed fields in the EnergyPlus schema.
  // - Field Mapping: Construction Name, Building Surface Name, Outside Boundary Condition Object,
  //   Frame and Divider Name, and extensible vertex coordinates are relationship/non-scalar fields and are excluded.
  // - ForwardTranslator evidence: ForwardTranslateSubSurface.cpp maps subSurfaceType, viewFactortoGround,
  //   and multiplier directly to FenestrationSurface:Detailed.
  // - TODO(parity): Add geometry and typed relationship APIs in later parity milestones.
  std::string subSurfaceType() const;
  bool isSubSurfaceTypeDefaulted() const;

  boost::optional<double> viewFactortoGround() const;
  bool isViewFactortoGroundDefaulted() const;
  bool isViewFactortoGroundAutocalculated() const;

  double multiplier() const;
  bool isMultiplierDefaulted() const;

  boost::optional<double> numberofVertices() const;
  bool isNumberofVerticesDefaulted() const;
  bool isNumberofVerticesAutocalculated() const;

  bool setSubSurfaceType(const std::string& subSurfaceType);
  void resetSubSurfaceType();

  bool setViewFactortoGround(boost::optional<double> viewFactortoGround);
  bool setViewFactortoGround(double viewFactortoGround);
  void resetViewFactortoGround();
  void autocalculateViewFactortoGround();

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  bool setNumberofVertices(boost::optional<double> numberofVertices);
  bool setNumberofVertices(double numberofVertices);
  void resetNumberofVertices();
  void autocalculateNumberofVertices();

 protected:
  using ImplType = detail::SubSurface_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SubSurface(std::shared_ptr<detail::SubSurface_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
