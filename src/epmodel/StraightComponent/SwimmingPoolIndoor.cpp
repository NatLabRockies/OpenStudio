/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/SwimmingPoolIndoor.hpp"
#include "StraightComponent/SwimmingPoolIndoor_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SwimmingPool_Indoor_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SwimmingPoolIndoor::SwimmingPoolIndoor(const Model& model) : StraightComponent(SwimmingPoolIndoor::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SwimmingPoolIndoor_Impl>());

    OS_ASSERT(setAverageDepth(2.0));
    OS_ASSERT(setPoolHeatingSystemMaximumWaterFlowRate(0.1));
    OS_ASSERT(setPoolMiscellaneousEquipmentPower(0.0));
    OS_ASSERT(setMaximumNumberofPeople(15.0));
  }

  SwimmingPoolIndoor::SwimmingPoolIndoor(std::shared_ptr<detail::SwimmingPoolIndoor_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType SwimmingPoolIndoor::iddObjectType() {
    return IddObjectType::SwimmingPool_Indoor;
  }

  double SwimmingPoolIndoor::averageDepth() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->averageDepth();
  }

  bool SwimmingPoolIndoor::setAverageDepth(double averageDepth) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setAverageDepth(averageDepth);
  }

  double SwimmingPoolIndoor::coverEvaporationFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverEvaporationFactor();
  }

  bool SwimmingPoolIndoor::isCoverEvaporationFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverEvaporationFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverEvaporationFactor(double coverEvaporationFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverEvaporationFactor(coverEvaporationFactor);
  }

  void SwimmingPoolIndoor::resetCoverEvaporationFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverEvaporationFactor();
  }

  double SwimmingPoolIndoor::coverConvectionFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverConvectionFactor();
  }

  bool SwimmingPoolIndoor::isCoverConvectionFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverConvectionFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverConvectionFactor(double coverConvectionFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverConvectionFactor(coverConvectionFactor);
  }

  void SwimmingPoolIndoor::resetCoverConvectionFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverConvectionFactor();
  }

  double SwimmingPoolIndoor::coverShortWavelengthRadiationFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverShortWavelengthRadiationFactor();
  }

  bool SwimmingPoolIndoor::isCoverShortWavelengthRadiationFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverShortWavelengthRadiationFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverShortWavelengthRadiationFactor(coverShortWavelengthRadiationFactor);
  }

  void SwimmingPoolIndoor::resetCoverShortWavelengthRadiationFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverShortWavelengthRadiationFactor();
  }

  double SwimmingPoolIndoor::coverLongWavelengthRadiationFactor() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->coverLongWavelengthRadiationFactor();
  }

  bool SwimmingPoolIndoor::isCoverLongWavelengthRadiationFactorDefaulted() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->isCoverLongWavelengthRadiationFactorDefaulted();
  }

  bool SwimmingPoolIndoor::setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setCoverLongWavelengthRadiationFactor(coverLongWavelengthRadiationFactor);
  }

  void SwimmingPoolIndoor::resetCoverLongWavelengthRadiationFactor() {
    getImpl<detail::SwimmingPoolIndoor_Impl>()->resetCoverLongWavelengthRadiationFactor();
  }

  double SwimmingPoolIndoor::poolHeatingSystemMaximumWaterFlowRate() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolHeatingSystemMaximumWaterFlowRate();
  }

  bool SwimmingPoolIndoor::setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setPoolHeatingSystemMaximumWaterFlowRate(poolHeatingSystemMaximumWaterFlowRate);
  }

  double SwimmingPoolIndoor::poolMiscellaneousEquipmentPower() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolMiscellaneousEquipmentPower();
  }

  bool SwimmingPoolIndoor::setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setPoolMiscellaneousEquipmentPower(poolMiscellaneousEquipmentPower);
  }

  double SwimmingPoolIndoor::maximumNumberofPeople() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->maximumNumberofPeople();
  }

  bool SwimmingPoolIndoor::setMaximumNumberofPeople(double maximumNumberofPeople) {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->setMaximumNumberofPeople(maximumNumberofPeople);
  }

  boost::optional<Node> SwimmingPoolIndoor::poolWaterInletNode() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolWaterInletNode();
  }

  boost::optional<Node> SwimmingPoolIndoor::poolWaterOutletNode() const {
    return getImpl<detail::SwimmingPoolIndoor_Impl>()->poolWaterOutletNode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SwimmingPoolIndoor_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }
      return false;
    }

    unsigned SwimmingPoolIndoor_Impl::inletPort() const {
      return openstudio::SwimmingPool_IndoorFields::PoolWaterInletNode;
    }

    unsigned SwimmingPoolIndoor_Impl::outletPort() const {
      return openstudio::SwimmingPool_IndoorFields::PoolWaterOutletNode;
    }

    double SwimmingPoolIndoor_Impl::averageDepth() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::AverageDepth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setAverageDepth(double averageDepth) {
      const bool result = setDouble(openstudio::SwimmingPool_IndoorFields::AverageDepth, averageDepth);
      OS_ASSERT(result);
      return result;
    }

    double SwimmingPoolIndoor_Impl::coverEvaporationFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverEvaporationFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverEvaporationFactor(double coverEvaporationFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor, coverEvaporationFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverEvaporationFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverEvaporationFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::coverConvectionFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverConvectionFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverConvectionFactor(double coverConvectionFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor, coverConvectionFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverConvectionFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverConvectionFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::coverShortWavelengthRadiationFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverShortWavelengthRadiationFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, coverShortWavelengthRadiationFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverShortWavelengthRadiationFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverShortWavelengthRadiationFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::coverLongWavelengthRadiationFactor() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::isCoverLongWavelengthRadiationFactorDefaulted() const {
      return isEmpty(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor);
    }

    bool SwimmingPoolIndoor_Impl::setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, coverLongWavelengthRadiationFactor);
    }

    void SwimmingPoolIndoor_Impl::resetCoverLongWavelengthRadiationFactor() {
      OS_ASSERT(setString(openstudio::SwimmingPool_IndoorFields::CoverLongWavelengthRadiationFactor, ""));
    }

    double SwimmingPoolIndoor_Impl::poolHeatingSystemMaximumWaterFlowRate() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::PoolHeatingSystemMaximumWaterFlowRate, poolHeatingSystemMaximumWaterFlowRate);
    }

    double SwimmingPoolIndoor_Impl::poolMiscellaneousEquipmentPower() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::PoolMiscellaneousEquipmentPower, poolMiscellaneousEquipmentPower);
    }

    double SwimmingPoolIndoor_Impl::maximumNumberofPeople() const {
      const auto value = getDouble(openstudio::SwimmingPool_IndoorFields::MaximumNumberofPeople, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SwimmingPoolIndoor_Impl::setMaximumNumberofPeople(double maximumNumberofPeople) {
      return setDouble(openstudio::SwimmingPool_IndoorFields::MaximumNumberofPeople, maximumNumberofPeople);
    }

    boost::optional<Node> SwimmingPoolIndoor_Impl::poolWaterInletNode() const {
      return resolvedNodeTarget(inletPort());
    }

    boost::optional<Node> SwimmingPoolIndoor_Impl::poolWaterOutletNode() const {
      return resolvedNodeTarget(outletPort());
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
