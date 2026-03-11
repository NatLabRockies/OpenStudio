/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONCOMPLEXFENESTRATIONSTATE_HPP
#define EPMODEL_CONSTRUCTIONCOMPLEXFENESTRATIONSTATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ConstructionComplexFenestrationState_Impl;
}

class EPMODEL_API ConstructionComplexFenestrationState : public ModelObject
{
 public:
  explicit ConstructionComplexFenestrationState(const Model& model);

  virtual ~ConstructionComplexFenestrationState() override = default;
  ConstructionComplexFenestrationState(const ConstructionComplexFenestrationState& other) = default;
  ConstructionComplexFenestrationState(ConstructionComplexFenestrationState&& other) = default;
  ConstructionComplexFenestrationState& operator=(const ConstructionComplexFenestrationState&) = default;
  ConstructionComplexFenestrationState& operator=(ConstructionComplexFenestrationState&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> basisTypeValues();
  static std::vector<std::string> basisSymmetryTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: basisType and basisSymmetryType map directly to EnergyPlus
  //   Construction:ComplexFenestrationState fields Basis Type and Basis Symmetry Type.
  // - Field Mapping: Name remains available via base ModelObject API.
  // - Field Mapping: Window Thermal Model, Basis Matrix Name, Solar/Visible matrix names, and all extensible layer/gap
  //   fields are object-list relationship fields and are intentionally excluded from simple scalar accessors.
  // - TODO(parity): Add typed relationship/extensible helpers after scalar scaffold saturation.
  std::string basisType() const;
  bool isBasisTypeDefaulted() const;
  bool setBasisType(const std::string& basisType);
  void resetBasisType();

  std::string basisSymmetryType() const;
  bool isBasisSymmetryTypeDefaulted() const;
  bool setBasisSymmetryType(const std::string& basisSymmetryType);
  void resetBasisSymmetryType();

 protected:
  using ImplType = detail::ConstructionComplexFenestrationState_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ConstructionComplexFenestrationState(std::shared_ptr<detail::ConstructionComplexFenestrationState_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
