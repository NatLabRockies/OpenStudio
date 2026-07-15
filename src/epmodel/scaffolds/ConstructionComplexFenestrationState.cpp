/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionComplexFenestrationState.hpp"
#include "ConstructionComplexFenestrationState_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Construction_ComplexFenestrationState_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  ConstructionComplexFenestrationState::ConstructionComplexFenestrationState(const Model& model)
    : ModelObject(ConstructionComplexFenestrationState::iddObjectType(), model) {}

  ConstructionComplexFenestrationState::ConstructionComplexFenestrationState(std::shared_ptr<detail::ConstructionComplexFenestrationState_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ConstructionComplexFenestrationState::iddObjectType() {
    return IddObjectType::Construction_ComplexFenestrationState;
  }

  std::vector<std::string> ConstructionComplexFenestrationState::basisTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Construction_ComplexFenestrationStateFields::BasisType);
  }

  std::vector<std::string> ConstructionComplexFenestrationState::basisSymmetryTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Construction_ComplexFenestrationStateFields::BasisSymmetryType);
  }

  std::string ConstructionComplexFenestrationState::basisType() const {
    return getImpl<detail::ConstructionComplexFenestrationState_Impl>()->basisType();
  }

  bool ConstructionComplexFenestrationState::isBasisTypeDefaulted() const {
    return getImpl<detail::ConstructionComplexFenestrationState_Impl>()->isBasisTypeDefaulted();
  }

  bool ConstructionComplexFenestrationState::setBasisType(const std::string& basisType) {
    return getImpl<detail::ConstructionComplexFenestrationState_Impl>()->setBasisType(basisType);
  }

  void ConstructionComplexFenestrationState::resetBasisType() {
    getImpl<detail::ConstructionComplexFenestrationState_Impl>()->resetBasisType();
  }

  std::string ConstructionComplexFenestrationState::basisSymmetryType() const {
    return getImpl<detail::ConstructionComplexFenestrationState_Impl>()->basisSymmetryType();
  }

  bool ConstructionComplexFenestrationState::isBasisSymmetryTypeDefaulted() const {
    return getImpl<detail::ConstructionComplexFenestrationState_Impl>()->isBasisSymmetryTypeDefaulted();
  }

  bool ConstructionComplexFenestrationState::setBasisSymmetryType(const std::string& basisSymmetryType) {
    return getImpl<detail::ConstructionComplexFenestrationState_Impl>()->setBasisSymmetryType(basisSymmetryType);
  }

  void ConstructionComplexFenestrationState::resetBasisSymmetryType() {
    getImpl<detail::ConstructionComplexFenestrationState_Impl>()->resetBasisSymmetryType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ConstructionComplexFenestrationState_Impl::basisType() const {
      const auto value = getString(openstudio::Construction_ComplexFenestrationStateFields::BasisType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConstructionComplexFenestrationState_Impl::isBasisTypeDefaulted() const {
      return isEmpty(openstudio::Construction_ComplexFenestrationStateFields::BasisType);
    }

    bool ConstructionComplexFenestrationState_Impl::setBasisType(const std::string& basisType) {
      return setString(openstudio::Construction_ComplexFenestrationStateFields::BasisType, basisType);
    }

    void ConstructionComplexFenestrationState_Impl::resetBasisType() {
      OS_ASSERT(setString(openstudio::Construction_ComplexFenestrationStateFields::BasisType, ""));
    }

    std::string ConstructionComplexFenestrationState_Impl::basisSymmetryType() const {
      const auto value = getString(openstudio::Construction_ComplexFenestrationStateFields::BasisSymmetryType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ConstructionComplexFenestrationState_Impl::isBasisSymmetryTypeDefaulted() const {
      return isEmpty(openstudio::Construction_ComplexFenestrationStateFields::BasisSymmetryType);
    }

    bool ConstructionComplexFenestrationState_Impl::setBasisSymmetryType(const std::string& basisSymmetryType) {
      return setString(openstudio::Construction_ComplexFenestrationStateFields::BasisSymmetryType, basisSymmetryType);
    }

    void ConstructionComplexFenestrationState_Impl::resetBasisSymmetryType() {
      OS_ASSERT(setString(openstudio::Construction_ComplexFenestrationStateFields::BasisSymmetryType, ""));
    }

    std::vector<std::string> ConstructionComplexFenestrationState_Impl::basisTypeValues() const {
      return openstudio::epmodel::ConstructionComplexFenestrationState::basisTypeValues();
    }

    std::vector<std::string> ConstructionComplexFenestrationState_Impl::basisSymmetryTypeValues() const {
      return openstudio::epmodel::ConstructionComplexFenestrationState::basisSymmetryTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
