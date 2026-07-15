/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionBase/CFactorUndergroundWallConstruction.hpp"
#include "ConstructionBase/CFactorUndergroundWallConstruction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Construction_CfactorUndergroundWall_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CFactorUndergroundWallConstruction::CFactorUndergroundWallConstruction(const Model& model, double cFactor, double height)
    : ModelObject(CFactorUndergroundWallConstruction::iddObjectType(), model) {
    const bool okCFactor = setCFactor(cFactor);
    OS_ASSERT(okCFactor);
    const bool okHeight = setHeight(height);
    OS_ASSERT(okHeight);
  }

  CFactorUndergroundWallConstruction::CFactorUndergroundWallConstruction(std::shared_ptr<detail::CFactorUndergroundWallConstruction_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CFactorUndergroundWallConstruction::iddObjectType() {
    return IddObjectType::Construction_CfactorUndergroundWall;
  }

  double CFactorUndergroundWallConstruction::cFactor() const {
    return getImpl<detail::CFactorUndergroundWallConstruction_Impl>()->cFactor();
  }

  bool CFactorUndergroundWallConstruction::setCFactor(double cFactor) {
    return getImpl<detail::CFactorUndergroundWallConstruction_Impl>()->setCFactor(cFactor);
  }

  double CFactorUndergroundWallConstruction::height() const {
    return getImpl<detail::CFactorUndergroundWallConstruction_Impl>()->height();
  }

  bool CFactorUndergroundWallConstruction::setHeight(double height) {
    return getImpl<detail::CFactorUndergroundWallConstruction_Impl>()->setHeight(height);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double CFactorUndergroundWallConstruction_Impl::cFactor() const {
      const auto value = getDouble(openstudio::Construction_CfactorUndergroundWallFields::CFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CFactorUndergroundWallConstruction_Impl::setCFactor(double cFactor) {
      const bool result = setDouble(openstudio::Construction_CfactorUndergroundWallFields::CFactor, cFactor);
      return result;
    }

    double CFactorUndergroundWallConstruction_Impl::height() const {
      const auto value = getDouble(openstudio::Construction_CfactorUndergroundWallFields::Height, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CFactorUndergroundWallConstruction_Impl::setHeight(double height) {
      const bool result = setDouble(openstudio::Construction_CfactorUndergroundWallFields::Height, height);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
