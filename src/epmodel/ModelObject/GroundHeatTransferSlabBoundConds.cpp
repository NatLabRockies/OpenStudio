/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabBoundConds.hpp"
#include "GroundHeatTransferSlabBoundConds_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_BoundConds_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferSlabBoundConds::GroundHeatTransferSlabBoundConds(const Model& model)
    : ModelObject(GroundHeatTransferSlabBoundConds::iddObjectType(), model) {}

  GroundHeatTransferSlabBoundConds::GroundHeatTransferSlabBoundConds(std::shared_ptr<detail::GroundHeatTransferSlabBoundConds_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferSlabBoundConds::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Slab_BoundConds;
  }

  bool GroundHeatTransferSlabBoundConds::eVTRIssurfaceevapotranspirationmodeled() const {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->eVTRIssurfaceevapotranspirationmodeled();
  }

  bool GroundHeatTransferSlabBoundConds::setEVTRIssurfaceevapotranspirationmodeled(bool eVTRIssurfaceevapotranspirationmodeled) {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->setEVTRIssurfaceevapotranspirationmodeled(
      eVTRIssurfaceevapotranspirationmodeled);
  }

  bool GroundHeatTransferSlabBoundConds::fIXBCIsthelowerboundaryatafixedtemperature() const {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->fIXBCIsthelowerboundaryatafixedtemperature();
  }

  bool GroundHeatTransferSlabBoundConds::setFIXBCIsthelowerboundaryatafixedtemperature(bool fIXBCIsthelowerboundaryatafixedtemperature) {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->setFIXBCIsthelowerboundaryatafixedtemperature(
      fIXBCIsthelowerboundaryatafixedtemperature);
  }

  boost::optional<double> GroundHeatTransferSlabBoundConds::tDEEPin() const {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->tDEEPin();
  }

  bool GroundHeatTransferSlabBoundConds::setTDEEPin(double tDEEPin) {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->setTDEEPin(tDEEPin);
  }

  void GroundHeatTransferSlabBoundConds::resetTDEEPin() {
    getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->resetTDEEPin();
  }

  bool GroundHeatTransferSlabBoundConds::uSRHflagIsthegroundsurfacehspecifiedbytheuser() const {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->uSRHflagIsthegroundsurfacehspecifiedbytheuser();
  }

  bool GroundHeatTransferSlabBoundConds::setUSRHflagIsthegroundsurfacehspecifiedbytheuser(bool uSRHflagIsthegroundsurfacehspecifiedbytheuser) {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->setUSRHflagIsthegroundsurfacehspecifiedbytheuser(
      uSRHflagIsthegroundsurfacehspecifiedbytheuser);
  }

  boost::optional<double> GroundHeatTransferSlabBoundConds::uSERHUserspecifiedgroundsurfaceheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->uSERHUserspecifiedgroundsurfaceheattransfercoefficient();
  }

  bool GroundHeatTransferSlabBoundConds::setUSERHUserspecifiedgroundsurfaceheattransfercoefficient(
    double uSERHUserspecifiedgroundsurfaceheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->setUSERHUserspecifiedgroundsurfaceheattransfercoefficient(
      uSERHUserspecifiedgroundsurfaceheattransfercoefficient);
  }

  void GroundHeatTransferSlabBoundConds::resetUSERHUserspecifiedgroundsurfaceheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferSlabBoundConds_Impl>()->resetUSERHUserspecifiedgroundsurfaceheattransfercoefficient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool GroundHeatTransferSlabBoundConds_Impl::eVTRIssurfaceevapotranspirationmodeled() const {
      const auto value = getString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::EVTR_Issurfaceevapotranspirationmodeled, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "TRUE");
    }

    bool GroundHeatTransferSlabBoundConds_Impl::setEVTRIssurfaceevapotranspirationmodeled(bool eVTRIssurfaceevapotranspirationmodeled) {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::EVTR_Issurfaceevapotranspirationmodeled,
                                    eVTRIssurfaceevapotranspirationmodeled ? "TRUE" : "FALSE");
      OS_ASSERT(result);
      return result;
    }

    bool GroundHeatTransferSlabBoundConds_Impl::fIXBCIsthelowerboundaryatafixedtemperature() const {
      const auto value = getString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::FIXBC_isthelowerboundaryatafixedtemperature, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "TRUE");
    }

    bool GroundHeatTransferSlabBoundConds_Impl::setFIXBCIsthelowerboundaryatafixedtemperature(bool fIXBCIsthelowerboundaryatafixedtemperature) {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::FIXBC_isthelowerboundaryatafixedtemperature,
                                    fIXBCIsthelowerboundaryatafixedtemperature ? "TRUE" : "FALSE");
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GroundHeatTransferSlabBoundConds_Impl::tDEEPin() const {
      return getDouble(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::TDEEPin, true);
    }

    bool GroundHeatTransferSlabBoundConds_Impl::setTDEEPin(double tDEEPin) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::TDEEPin, tDEEPin);
    }

    void GroundHeatTransferSlabBoundConds_Impl::resetTDEEPin() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::TDEEPin, ""));
    }

    bool GroundHeatTransferSlabBoundConds_Impl::uSRHflagIsthegroundsurfacehspecifiedbytheuser() const {
      const auto value = getString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::USRHflag_Isthegroundsurfacehspecifiedbytheuser, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "TRUE");
    }

    bool GroundHeatTransferSlabBoundConds_Impl::setUSRHflagIsthegroundsurfacehspecifiedbytheuser(bool uSRHflagIsthegroundsurfacehspecifiedbytheuser) {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::USRHflag_Isthegroundsurfacehspecifiedbytheuser,
                                    uSRHflagIsthegroundsurfacehspecifiedbytheuser ? "TRUE" : "FALSE");
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> GroundHeatTransferSlabBoundConds_Impl::uSERHUserspecifiedgroundsurfaceheattransfercoefficient() const {
      return getDouble(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::USERH_Userspecifiedgroundsurfaceheattransfercoefficient, true);
    }

    bool GroundHeatTransferSlabBoundConds_Impl::setUSERHUserspecifiedgroundsurfaceheattransfercoefficient(
      double uSERHUserspecifiedgroundsurfaceheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::USERH_Userspecifiedgroundsurfaceheattransfercoefficient,
                       uSERHUserspecifiedgroundsurfaceheattransfercoefficient);
    }

    void GroundHeatTransferSlabBoundConds_Impl::resetUSERHUserspecifiedgroundsurfaceheattransfercoefficient() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Slab_BoundCondsFields::USERH_Userspecifiedgroundsurfaceheattransfercoefficient, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
