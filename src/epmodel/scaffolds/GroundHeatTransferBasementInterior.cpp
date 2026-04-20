/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementInterior.hpp"
#include "GroundHeatTransferBasementInterior_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_Interior_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementInterior::GroundHeatTransferBasementInterior(const Model& model)
    : ModelObject(GroundHeatTransferBasementInterior::iddObjectType(), model) {}

  GroundHeatTransferBasementInterior::GroundHeatTransferBasementInterior(std::shared_ptr<detail::GroundHeatTransferBasementInterior_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementInterior::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_Interior;
  }

  bool GroundHeatTransferBasementInterior::cONDFlagIsthebasementconditioned() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->cONDFlagIsthebasementconditioned();
  }

  bool GroundHeatTransferBasementInterior::isCONDFlagIsthebasementconditionedDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->isCONDFlagIsthebasementconditionedDefaulted();
  }

  bool GroundHeatTransferBasementInterior::setCONDFlagIsthebasementconditioned(bool cONDFlagIsthebasementconditioned) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setCONDFlagIsthebasementconditioned(cONDFlagIsthebasementconditioned);
  }

  void GroundHeatTransferBasementInterior::resetCONDFlagIsthebasementconditioned() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetCONDFlagIsthebasementconditioned();
  }

  double GroundHeatTransferBasementInterior::hINDownwardconvectiononlyheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->hINDownwardconvectiononlyheattransfercoefficient();
  }

  bool GroundHeatTransferBasementInterior::isHINDownwardconvectiononlyheattransfercoefficientDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->isHINDownwardconvectiononlyheattransfercoefficientDefaulted();
  }

  bool
    GroundHeatTransferBasementInterior::setHINDownwardconvectiononlyheattransfercoefficient(double hINDownwardconvectiononlyheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setHINDownwardconvectiononlyheattransfercoefficient(
      hINDownwardconvectiononlyheattransfercoefficient);
  }

  void GroundHeatTransferBasementInterior::resetHINDownwardconvectiononlyheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetHINDownwardconvectiononlyheattransfercoefficient();
  }

  double GroundHeatTransferBasementInterior::hINUpwardconvectiononlyheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->hINUpwardconvectiononlyheattransfercoefficient();
  }

  bool GroundHeatTransferBasementInterior::isHINUpwardconvectiononlyheattransfercoefficientDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->isHINUpwardconvectiononlyheattransfercoefficientDefaulted();
  }

  bool GroundHeatTransferBasementInterior::setHINUpwardconvectiononlyheattransfercoefficient(double hINUpwardconvectiononlyheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setHINUpwardconvectiononlyheattransfercoefficient(
      hINUpwardconvectiononlyheattransfercoefficient);
  }

  void GroundHeatTransferBasementInterior::resetHINUpwardconvectiononlyheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetHINUpwardconvectiononlyheattransfercoefficient();
  }

  double GroundHeatTransferBasementInterior::hINHorizontalconvectiononlyheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->hINHorizontalconvectiononlyheattransfercoefficient();
  }

  bool GroundHeatTransferBasementInterior::isHINHorizontalconvectiononlyheattransfercoefficientDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->isHINHorizontalconvectiononlyheattransfercoefficientDefaulted();
  }

  bool GroundHeatTransferBasementInterior::setHINHorizontalconvectiononlyheattransfercoefficient(
    double hINHorizontalconvectiononlyheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setHINHorizontalconvectiononlyheattransfercoefficient(
      hINHorizontalconvectiononlyheattransfercoefficient);
  }

  void GroundHeatTransferBasementInterior::resetHINHorizontalconvectiononlyheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetHINHorizontalconvectiononlyheattransfercoefficient();
  }

  double GroundHeatTransferBasementInterior::hINDownwardcombinedconvectionandradiationheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->hINDownwardcombinedconvectionandradiationheattransfercoefficient();
  }

  bool GroundHeatTransferBasementInterior::isHINDownwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->isHINDownwardcombinedconvectionandradiationheattransfercoefficientDefaulted();
  }

  bool GroundHeatTransferBasementInterior::setHINDownwardcombinedconvectionandradiationheattransfercoefficient(
    double hINDownwardcombinedconvectionandradiationheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setHINDownwardcombinedconvectionandradiationheattransfercoefficient(
      hINDownwardcombinedconvectionandradiationheattransfercoefficient);
  }

  void GroundHeatTransferBasementInterior::resetHINDownwardcombinedconvectionandradiationheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetHINDownwardcombinedconvectionandradiationheattransfercoefficient();
  }

  double GroundHeatTransferBasementInterior::hINUpwardcombinedconvectionandradiationheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->hINUpwardcombinedconvectionandradiationheattransfercoefficient();
  }

  bool GroundHeatTransferBasementInterior::isHINUpwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->isHINUpwardcombinedconvectionandradiationheattransfercoefficientDefaulted();
  }

  bool GroundHeatTransferBasementInterior::setHINUpwardcombinedconvectionandradiationheattransfercoefficient(
    double hINUpwardcombinedconvectionandradiationheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setHINUpwardcombinedconvectionandradiationheattransfercoefficient(
      hINUpwardcombinedconvectionandradiationheattransfercoefficient);
  }

  void GroundHeatTransferBasementInterior::resetHINUpwardcombinedconvectionandradiationheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetHINUpwardcombinedconvectionandradiationheattransfercoefficient();
  }

  double GroundHeatTransferBasementInterior::hINHorizontalcombinedconvectionandradiationheattransfercoefficient() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->hINHorizontalcombinedconvectionandradiationheattransfercoefficient();
  }

  bool GroundHeatTransferBasementInterior::isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()
      ->isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted();
  }

  bool GroundHeatTransferBasementInterior::setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(
    double hINHorizontalcombinedconvectionandradiationheattransfercoefficient) {
    return getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(
      hINHorizontalcombinedconvectionandradiationheattransfercoefficient);
  }

  void GroundHeatTransferBasementInterior::resetHINHorizontalcombinedconvectionandradiationheattransfercoefficient() {
    getImpl<detail::GroundHeatTransferBasementInterior_Impl>()->resetHINHorizontalcombinedconvectionandradiationheattransfercoefficient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool GroundHeatTransferBasementInterior_Impl::cONDFlagIsthebasementconditioned() const {
      const auto value = getString(openstudio::GroundHeatTransfer_Basement_InteriorFields::COND_Flag_Isthebasementconditioned, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "TRUE");
    }

    bool GroundHeatTransferBasementInterior_Impl::isCONDFlagIsthebasementconditionedDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::COND_Flag_Isthebasementconditioned);
    }

    bool GroundHeatTransferBasementInterior_Impl::setCONDFlagIsthebasementconditioned(bool cONDFlagIsthebasementconditioned) {
      const bool result = setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::COND_Flag_Isthebasementconditioned,
                                    cONDFlagIsthebasementconditioned ? "TRUE" : "FALSE");
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementInterior_Impl::resetCONDFlagIsthebasementconditioned() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::COND_Flag_Isthebasementconditioned, ""));
    }

    double GroundHeatTransferBasementInterior_Impl::hINDownwardconvectiononlyheattransfercoefficient() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardconvectiononlyheattransfercoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementInterior_Impl::isHINDownwardconvectiononlyheattransfercoefficientDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardconvectiononlyheattransfercoefficient);
    }

    bool GroundHeatTransferBasementInterior_Impl::setHINDownwardconvectiononlyheattransfercoefficient(
      double hINDownwardconvectiononlyheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardconvectiononlyheattransfercoefficient,
                       hINDownwardconvectiononlyheattransfercoefficient);
    }

    void GroundHeatTransferBasementInterior_Impl::resetHINDownwardconvectiononlyheattransfercoefficient() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardconvectiononlyheattransfercoefficient, ""));
    }

    double GroundHeatTransferBasementInterior_Impl::hINUpwardconvectiononlyheattransfercoefficient() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardconvectiononlyheattransfercoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementInterior_Impl::isHINUpwardconvectiononlyheattransfercoefficientDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardconvectiononlyheattransfercoefficient);
    }

    bool GroundHeatTransferBasementInterior_Impl::setHINUpwardconvectiononlyheattransfercoefficient(
      double hINUpwardconvectiononlyheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardconvectiononlyheattransfercoefficient,
                       hINUpwardconvectiononlyheattransfercoefficient);
    }

    void GroundHeatTransferBasementInterior_Impl::resetHINUpwardconvectiononlyheattransfercoefficient() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardconvectiononlyheattransfercoefficient, ""));
    }

    double GroundHeatTransferBasementInterior_Impl::hINHorizontalconvectiononlyheattransfercoefficient() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalconvectiononlyheattransfercoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementInterior_Impl::isHINHorizontalconvectiononlyheattransfercoefficientDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalconvectiononlyheattransfercoefficient);
    }

    bool GroundHeatTransferBasementInterior_Impl::setHINHorizontalconvectiononlyheattransfercoefficient(
      double hINHorizontalconvectiononlyheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalconvectiononlyheattransfercoefficient,
                       hINHorizontalconvectiononlyheattransfercoefficient);
    }

    void GroundHeatTransferBasementInterior_Impl::resetHINHorizontalconvectiononlyheattransfercoefficient() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalconvectiononlyheattransfercoefficient, ""));
    }

    double GroundHeatTransferBasementInterior_Impl::hINDownwardcombinedconvectionandradiationheattransfercoefficient() const {
      const auto value =
        getDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardcombined_convectionandradiation_heattransfercoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementInterior_Impl::isHINDownwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardcombined_convectionandradiation_heattransfercoefficient);
    }

    bool GroundHeatTransferBasementInterior_Impl::setHINDownwardcombinedconvectionandradiationheattransfercoefficient(
      double hINDownwardcombinedconvectionandradiationheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardcombined_convectionandradiation_heattransfercoefficient,
                       hINDownwardcombinedconvectionandradiationheattransfercoefficient);
    }

    void GroundHeatTransferBasementInterior_Impl::resetHINDownwardcombinedconvectionandradiationheattransfercoefficient() {
      OS_ASSERT(
        setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardcombined_convectionandradiation_heattransfercoefficient, ""));
    }

    double GroundHeatTransferBasementInterior_Impl::hINUpwardcombinedconvectionandradiationheattransfercoefficient() const {
      const auto value =
        getDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardcombined_convectionandradiation_heattransfercoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementInterior_Impl::isHINUpwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardcombined_convectionandradiation_heattransfercoefficient);
    }

    bool GroundHeatTransferBasementInterior_Impl::setHINUpwardcombinedconvectionandradiationheattransfercoefficient(
      double hINUpwardcombinedconvectionandradiationheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardcombined_convectionandradiation_heattransfercoefficient,
                       hINUpwardcombinedconvectionandradiationheattransfercoefficient);
    }

    void GroundHeatTransferBasementInterior_Impl::resetHINUpwardcombinedconvectionandradiationheattransfercoefficient() {
      OS_ASSERT(
        setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardcombined_convectionandradiation_heattransfercoefficient, ""));
    }

    double GroundHeatTransferBasementInterior_Impl::hINHorizontalcombinedconvectionandradiationheattransfercoefficient() const {
      const auto value = getDouble(
        openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementInterior_Impl::isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient);
    }

    bool GroundHeatTransferBasementInterior_Impl::setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(
      double hINHorizontalcombinedconvectionandradiationheattransfercoefficient) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient,
                       hINHorizontalcombinedconvectionandradiationheattransfercoefficient);
    }

    void GroundHeatTransferBasementInterior_Impl::resetHINHorizontalcombinedconvectionandradiationheattransfercoefficient() {
      OS_ASSERT(
        setString(openstudio::GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
