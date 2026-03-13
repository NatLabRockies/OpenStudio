/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementMatlProps.hpp"
#include "GroundHeatTransferBasementMatlProps_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_MatlProps_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementMatlProps::GroundHeatTransferBasementMatlProps(const Model& model)
    : ModelObject(GroundHeatTransferBasementMatlProps::iddObjectType(), model) {}

  GroundHeatTransferBasementMatlProps::GroundHeatTransferBasementMatlProps(std::shared_ptr<detail::GroundHeatTransferBasementMatlProps_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementMatlProps::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_MatlProps;
  }

  double GroundHeatTransferBasementMatlProps::nMATNumberofmaterialsinthisdomain() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->nMATNumberofmaterialsinthisdomain();
  }

  bool GroundHeatTransferBasementMatlProps::setNMATNumberofmaterialsinthisdomain(double nMATNumberofmaterialsinthisdomain) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setNMATNumberofmaterialsinthisdomain(nMATNumberofmaterialsinthisdomain);
  }

  double GroundHeatTransferBasementMatlProps::densityforFoundationWall() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->densityforFoundationWall();
  }

  bool GroundHeatTransferBasementMatlProps::isDensityforFoundationWallDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isDensityforFoundationWallDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setDensityforFoundationWall(double densityforFoundationWall) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setDensityforFoundationWall(densityforFoundationWall);
  }

  void GroundHeatTransferBasementMatlProps::resetDensityforFoundationWall() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetDensityforFoundationWall();
  }

  double GroundHeatTransferBasementMatlProps::densityforFloorSlab() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->densityforFloorSlab();
  }

  bool GroundHeatTransferBasementMatlProps::isDensityforFloorSlabDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isDensityforFloorSlabDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setDensityforFloorSlab(double densityforFloorSlab) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setDensityforFloorSlab(densityforFloorSlab);
  }

  void GroundHeatTransferBasementMatlProps::resetDensityforFloorSlab() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetDensityforFloorSlab();
  }

  double GroundHeatTransferBasementMatlProps::densityforCeiling() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->densityforCeiling();
  }

  bool GroundHeatTransferBasementMatlProps::isDensityforCeilingDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isDensityforCeilingDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setDensityforCeiling(double densityforCeiling) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setDensityforCeiling(densityforCeiling);
  }

  void GroundHeatTransferBasementMatlProps::resetDensityforCeiling() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetDensityforCeiling();
  }

  double GroundHeatTransferBasementMatlProps::densityforSoil() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->densityforSoil();
  }

  bool GroundHeatTransferBasementMatlProps::isDensityforSoilDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isDensityforSoilDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setDensityforSoil(double densityforSoil) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setDensityforSoil(densityforSoil);
  }

  void GroundHeatTransferBasementMatlProps::resetDensityforSoil() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetDensityforSoil();
  }

  double GroundHeatTransferBasementMatlProps::densityforGravel() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->densityforGravel();
  }

  bool GroundHeatTransferBasementMatlProps::isDensityforGravelDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isDensityforGravelDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setDensityforGravel(double densityforGravel) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setDensityforGravel(densityforGravel);
  }

  void GroundHeatTransferBasementMatlProps::resetDensityforGravel() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetDensityforGravel();
  }

  double GroundHeatTransferBasementMatlProps::densityforWood() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->densityforWood();
  }

  bool GroundHeatTransferBasementMatlProps::isDensityforWoodDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isDensityforWoodDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setDensityforWood(double densityforWood) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setDensityforWood(densityforWood);
  }

  void GroundHeatTransferBasementMatlProps::resetDensityforWood() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetDensityforWood();
  }

  double GroundHeatTransferBasementMatlProps::specificheatforfoundationwall() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->specificheatforfoundationwall();
  }

  bool GroundHeatTransferBasementMatlProps::isSpecificheatforfoundationwallDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isSpecificheatforfoundationwallDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setSpecificheatforfoundationwall(double specificheatforfoundationwall) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setSpecificheatforfoundationwall(specificheatforfoundationwall);
  }

  void GroundHeatTransferBasementMatlProps::resetSpecificheatforfoundationwall() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetSpecificheatforfoundationwall();
  }

  double GroundHeatTransferBasementMatlProps::specificheatforfloorslab() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->specificheatforfloorslab();
  }

  bool GroundHeatTransferBasementMatlProps::isSpecificheatforfloorslabDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isSpecificheatforfloorslabDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setSpecificheatforfloorslab(double specificheatforfloorslab) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setSpecificheatforfloorslab(specificheatforfloorslab);
  }

  void GroundHeatTransferBasementMatlProps::resetSpecificheatforfloorslab() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetSpecificheatforfloorslab();
  }

  double GroundHeatTransferBasementMatlProps::specificheatforceiling() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->specificheatforceiling();
  }

  bool GroundHeatTransferBasementMatlProps::isSpecificheatforceilingDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isSpecificheatforceilingDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setSpecificheatforceiling(double specificheatforceiling) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setSpecificheatforceiling(specificheatforceiling);
  }

  void GroundHeatTransferBasementMatlProps::resetSpecificheatforceiling() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetSpecificheatforceiling();
  }

  double GroundHeatTransferBasementMatlProps::specificheatforsoil() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->specificheatforsoil();
  }

  bool GroundHeatTransferBasementMatlProps::isSpecificheatforsoilDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isSpecificheatforsoilDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setSpecificheatforsoil(double specificheatforsoil) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setSpecificheatforsoil(specificheatforsoil);
  }

  void GroundHeatTransferBasementMatlProps::resetSpecificheatforsoil() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetSpecificheatforsoil();
  }

  double GroundHeatTransferBasementMatlProps::specificheatforgravel() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->specificheatforgravel();
  }

  bool GroundHeatTransferBasementMatlProps::isSpecificheatforgravelDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isSpecificheatforgravelDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setSpecificheatforgravel(double specificheatforgravel) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setSpecificheatforgravel(specificheatforgravel);
  }

  void GroundHeatTransferBasementMatlProps::resetSpecificheatforgravel() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetSpecificheatforgravel();
  }

  double GroundHeatTransferBasementMatlProps::specificheatforwood() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->specificheatforwood();
  }

  bool GroundHeatTransferBasementMatlProps::isSpecificheatforwoodDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isSpecificheatforwoodDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setSpecificheatforwood(double specificheatforwood) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setSpecificheatforwood(specificheatforwood);
  }

  void GroundHeatTransferBasementMatlProps::resetSpecificheatforwood() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetSpecificheatforwood();
  }

  double GroundHeatTransferBasementMatlProps::thermalconductivityforfoundationwall() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->thermalconductivityforfoundationwall();
  }

  bool GroundHeatTransferBasementMatlProps::isThermalconductivityforfoundationwallDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isThermalconductivityforfoundationwallDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setThermalconductivityforfoundationwall(double thermalconductivityforfoundationwall) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setThermalconductivityforfoundationwall(thermalconductivityforfoundationwall);
  }

  void GroundHeatTransferBasementMatlProps::resetThermalconductivityforfoundationwall() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetThermalconductivityforfoundationwall();
  }

  double GroundHeatTransferBasementMatlProps::thermalconductivityforfloorslab() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->thermalconductivityforfloorslab();
  }

  bool GroundHeatTransferBasementMatlProps::isThermalconductivityforfloorslabDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isThermalconductivityforfloorslabDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setThermalconductivityforfloorslab(double thermalconductivityforfloorslab) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setThermalconductivityforfloorslab(thermalconductivityforfloorslab);
  }

  void GroundHeatTransferBasementMatlProps::resetThermalconductivityforfloorslab() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetThermalconductivityforfloorslab();
  }

  double GroundHeatTransferBasementMatlProps::thermalconductivityforceiling() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->thermalconductivityforceiling();
  }

  bool GroundHeatTransferBasementMatlProps::isThermalconductivityforceilingDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isThermalconductivityforceilingDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setThermalconductivityforceiling(double thermalconductivityforceiling) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setThermalconductivityforceiling(thermalconductivityforceiling);
  }

  void GroundHeatTransferBasementMatlProps::resetThermalconductivityforceiling() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetThermalconductivityforceiling();
  }

  double GroundHeatTransferBasementMatlProps::thermalconductivityforsoil() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->thermalconductivityforsoil();
  }

  bool GroundHeatTransferBasementMatlProps::isThermalconductivityforsoilDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isThermalconductivityforsoilDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setThermalconductivityforsoil(double thermalconductivityforsoil) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setThermalconductivityforsoil(thermalconductivityforsoil);
  }

  void GroundHeatTransferBasementMatlProps::resetThermalconductivityforsoil() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetThermalconductivityforsoil();
  }

  double GroundHeatTransferBasementMatlProps::thermalconductivityforgravel() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->thermalconductivityforgravel();
  }

  bool GroundHeatTransferBasementMatlProps::isThermalconductivityforgravelDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isThermalconductivityforgravelDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setThermalconductivityforgravel(double thermalconductivityforgravel) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setThermalconductivityforgravel(thermalconductivityforgravel);
  }

  void GroundHeatTransferBasementMatlProps::resetThermalconductivityforgravel() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetThermalconductivityforgravel();
  }

  double GroundHeatTransferBasementMatlProps::thermalconductivityforwood() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->thermalconductivityforwood();
  }

  bool GroundHeatTransferBasementMatlProps::isThermalconductivityforwoodDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->isThermalconductivityforwoodDefaulted();
  }

  bool GroundHeatTransferBasementMatlProps::setThermalconductivityforwood(double thermalconductivityforwood) {
    return getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->setThermalconductivityforwood(thermalconductivityforwood);
  }

  void GroundHeatTransferBasementMatlProps::resetThermalconductivityforwood() {
    getImpl<detail::GroundHeatTransferBasementMatlProps_Impl>()->resetThermalconductivityforwood();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatTransferBasementMatlProps_Impl::nMATNumberofmaterialsinthisdomain() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::NMAT_Numberofmaterialsinthisdomain, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::densityforFoundationWall() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::DensityforFoundationWall, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::densityforFloorSlab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforFloorSlab, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::densityforCeiling() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforCeiling, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::densityforSoil() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforSoil, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::densityforGravel() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforGravel, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::densityforWood() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforWood, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::specificheatforfoundationwall() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfoundationwall, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::specificheatforfloorslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfloorslab, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::specificheatforceiling() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforceiling, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::specificheatforsoil() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforsoil, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::specificheatforgravel() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforgravel, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::specificheatforwood() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforwood, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::thermalconductivityforfoundationwall() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfoundationwall, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::thermalconductivityforfloorslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfloorslab, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::thermalconductivityforceiling() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforceiling, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::thermalconductivityforsoil() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforsoil, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::thermalconductivityforgravel() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforgravel, true);
      OS_ASSERT(value);
      return *value;
    }

    double GroundHeatTransferBasementMatlProps_Impl::thermalconductivityforwood() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforwood, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isDensityforFoundationWallDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::DensityforFoundationWall);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isDensityforFloorSlabDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforFloorSlab);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isDensityforCeilingDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforCeiling);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isDensityforSoilDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforSoil);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isDensityforGravelDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforGravel);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isDensityforWoodDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforWood);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isSpecificheatforfoundationwallDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfoundationwall);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isSpecificheatforfloorslabDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfloorslab);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isSpecificheatforceilingDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforceiling);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isSpecificheatforsoilDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforsoil);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isSpecificheatforgravelDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforgravel);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isSpecificheatforwoodDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforwood);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isThermalconductivityforfoundationwallDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfoundationwall);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isThermalconductivityforfloorslabDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfloorslab);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isThermalconductivityforceilingDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforceiling);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isThermalconductivityforsoilDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforsoil);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isThermalconductivityforgravelDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforgravel);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::isThermalconductivityforwoodDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforwood);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setNMATNumberofmaterialsinthisdomain(double nMATNumberofmaterialsinthisdomain) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::NMAT_Numberofmaterialsinthisdomain,
                       nMATNumberofmaterialsinthisdomain);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setDensityforFoundationWall(double densityforFoundationWall) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::DensityforFoundationWall, densityforFoundationWall);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setDensityforFloorSlab(double densityforFloorSlab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforFloorSlab, densityforFloorSlab);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setDensityforCeiling(double densityforCeiling) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforCeiling, densityforCeiling);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setDensityforSoil(double densityforSoil) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforSoil, densityforSoil);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setDensityforGravel(double densityforGravel) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforGravel, densityforGravel);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setDensityforWood(double densityforWood) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforWood, densityforWood);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setSpecificheatforfoundationwall(double specificheatforfoundationwall) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfoundationwall, specificheatforfoundationwall);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setSpecificheatforfloorslab(double specificheatforfloorslab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfloorslab, specificheatforfloorslab);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setSpecificheatforceiling(double specificheatforceiling) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforceiling, specificheatforceiling);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setSpecificheatforsoil(double specificheatforsoil) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforsoil, specificheatforsoil);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setSpecificheatforgravel(double specificheatforgravel) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforgravel, specificheatforgravel);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setSpecificheatforwood(double specificheatforwood) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforwood, specificheatforwood);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setThermalconductivityforfoundationwall(double thermalconductivityforfoundationwall) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfoundationwall,
                       thermalconductivityforfoundationwall);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setThermalconductivityforfloorslab(double thermalconductivityforfloorslab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfloorslab, thermalconductivityforfloorslab);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setThermalconductivityforceiling(double thermalconductivityforceiling) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforceiling, thermalconductivityforceiling);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setThermalconductivityforsoil(double thermalconductivityforsoil) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforsoil, thermalconductivityforsoil);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setThermalconductivityforgravel(double thermalconductivityforgravel) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforgravel, thermalconductivityforgravel);
    }

    bool GroundHeatTransferBasementMatlProps_Impl::setThermalconductivityforwood(double thermalconductivityforwood) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforwood, thermalconductivityforwood);
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetDensityforFoundationWall() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::DensityforFoundationWall, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetDensityforFloorSlab() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforFloorSlab, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetDensityforCeiling() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforCeiling, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetDensityforSoil() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforSoil, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetDensityforGravel() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforGravel, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetDensityforWood() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::densityforWood, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetSpecificheatforfoundationwall() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfoundationwall, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetSpecificheatforfloorslab() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforfloorslab, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetSpecificheatforceiling() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforceiling, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetSpecificheatforsoil() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforsoil, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetSpecificheatforgravel() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforgravel, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetSpecificheatforwood() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Specificheatforwood, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetThermalconductivityforfoundationwall() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfoundationwall, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetThermalconductivityforfloorslab() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforfloorslab, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetThermalconductivityforceiling() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::Thermalconductivityforceiling, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetThermalconductivityforsoil() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforsoil, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetThermalconductivityforgravel() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforgravel, ""));
    }

    void GroundHeatTransferBasementMatlProps_Impl::resetThermalconductivityforwood() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_MatlPropsFields::thermalconductivityforwood, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
