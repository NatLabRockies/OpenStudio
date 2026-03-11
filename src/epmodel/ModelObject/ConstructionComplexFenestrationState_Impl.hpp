/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONCOMPLEXFENESTRATIONSTATE_IMPL_HPP
#define EPMODEL_CONSTRUCTIONCOMPLEXFENESTRATIONSTATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ConstructionComplexFenestrationState_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ConstructionComplexFenestrationState_Impl() override = default;

  std::string basisType() const;
  bool isBasisTypeDefaulted() const;
  bool setBasisType(const std::string& basisType);
  void resetBasisType();

  std::string basisSymmetryType() const;
  bool isBasisSymmetryTypeDefaulted() const;
  bool setBasisSymmetryType(const std::string& basisSymmetryType);
  void resetBasisSymmetryType();

  std::vector<std::string> basisTypeValues() const;
  std::vector<std::string> basisSymmetryTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
