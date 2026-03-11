/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneEarthtubeParameters.hpp"
#include "ZoneEarthtubeParameters_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneEarthtube_Parameters_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneEarthtubeParameters::ZoneEarthtubeParameters(const Model& model) : ModelObject(ZoneEarthtubeParameters::iddObjectType(), model) {}

  ZoneEarthtubeParameters::ZoneEarthtubeParameters(std::shared_ptr<detail::ZoneEarthtubeParameters_Impl> impl) : ModelObject(std::move(impl)) {}

  namespace {
    IddObjectType zoneEarthtubeParametersIddObjectType() {
      static const IddObjectType type = [] {
        auto optional = IddFactory::instance().getObject("ZoneEarthtube:Parameters");
        OS_ASSERT(optional);
        return optional->type();
      }();
      return type;
    }
  }  // namespace

  IddObjectType ZoneEarthtubeParameters::iddObjectType() {
    return zoneEarthtubeParametersIddObjectType();
  }

  int ZoneEarthtubeParameters::nodesAboveEarthTube() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->nodesAboveEarthTube();
  }

  bool ZoneEarthtubeParameters::isNodesAboveEarthTubeDefaulted() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->isNodesAboveEarthTubeDefaulted();
  }

  bool ZoneEarthtubeParameters::setNodesAboveEarthTube(int nodesAboveEarthTube) {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->setNodesAboveEarthTube(nodesAboveEarthTube);
  }

  void ZoneEarthtubeParameters::resetNodesAboveEarthTube() {
    getImpl<detail::ZoneEarthtubeParameters_Impl>()->resetNodesAboveEarthTube();
  }

  int ZoneEarthtubeParameters::nodesBelowEarthTube() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->nodesBelowEarthTube();
  }

  bool ZoneEarthtubeParameters::isNodesBelowEarthTubeDefaulted() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->isNodesBelowEarthTubeDefaulted();
  }

  bool ZoneEarthtubeParameters::setNodesBelowEarthTube(int nodesBelowEarthTube) {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->setNodesBelowEarthTube(nodesBelowEarthTube);
  }

  void ZoneEarthtubeParameters::resetNodesBelowEarthTube() {
    getImpl<detail::ZoneEarthtubeParameters_Impl>()->resetNodesBelowEarthTube();
  }

  double ZoneEarthtubeParameters::earthTubeDimensionlessBoundaryAbove() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->earthTubeDimensionlessBoundaryAbove();
  }

  bool ZoneEarthtubeParameters::isEarthTubeDimensionlessBoundaryAboveDefaulted() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->isEarthTubeDimensionlessBoundaryAboveDefaulted();
  }

  bool ZoneEarthtubeParameters::setEarthTubeDimensionlessBoundaryAbove(double earthTubeDimensionlessBoundaryAbove) {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->setEarthTubeDimensionlessBoundaryAbove(earthTubeDimensionlessBoundaryAbove);
  }

  void ZoneEarthtubeParameters::resetEarthTubeDimensionlessBoundaryAbove() {
    getImpl<detail::ZoneEarthtubeParameters_Impl>()->resetEarthTubeDimensionlessBoundaryAbove();
  }

  double ZoneEarthtubeParameters::earthTubeDimensionlessBoundaryBelow() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->earthTubeDimensionlessBoundaryBelow();
  }

  bool ZoneEarthtubeParameters::isEarthTubeDimensionlessBoundaryBelowDefaulted() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->isEarthTubeDimensionlessBoundaryBelowDefaulted();
  }

  bool ZoneEarthtubeParameters::setEarthTubeDimensionlessBoundaryBelow(double earthTubeDimensionlessBoundaryBelow) {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->setEarthTubeDimensionlessBoundaryBelow(earthTubeDimensionlessBoundaryBelow);
  }

  void ZoneEarthtubeParameters::resetEarthTubeDimensionlessBoundaryBelow() {
    getImpl<detail::ZoneEarthtubeParameters_Impl>()->resetEarthTubeDimensionlessBoundaryBelow();
  }

  double ZoneEarthtubeParameters::earthTubeSolutionSpaceWidth() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->earthTubeSolutionSpaceWidth();
  }

  bool ZoneEarthtubeParameters::isEarthTubeSolutionSpaceWidthDefaulted() const {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->isEarthTubeSolutionSpaceWidthDefaulted();
  }

  bool ZoneEarthtubeParameters::setEarthTubeSolutionSpaceWidth(double earthTubeSolutionSpaceWidth) {
    return getImpl<detail::ZoneEarthtubeParameters_Impl>()->setEarthTubeSolutionSpaceWidth(earthTubeSolutionSpaceWidth);
  }

  void ZoneEarthtubeParameters::resetEarthTubeSolutionSpaceWidth() {
    getImpl<detail::ZoneEarthtubeParameters_Impl>()->resetEarthTubeSolutionSpaceWidth();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int ZoneEarthtubeParameters_Impl::nodesAboveEarthTube() const {
      if (auto value = getInt(ZoneEarthtube_ParametersFields::NodesAboveEarthTube, false)) {
        return *value;
      }
      return 5;
    }

    bool ZoneEarthtubeParameters_Impl::isNodesAboveEarthTubeDefaulted() const {
      return isEmpty(ZoneEarthtube_ParametersFields::NodesAboveEarthTube);
    }

    bool ZoneEarthtubeParameters_Impl::setNodesAboveEarthTube(int nodesAboveEarthTube) {
      const bool result = setInt(ZoneEarthtube_ParametersFields::NodesAboveEarthTube, nodesAboveEarthTube);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtubeParameters_Impl::resetNodesAboveEarthTube() {
      const bool result = setString(ZoneEarthtube_ParametersFields::NodesAboveEarthTube, "");
      OS_ASSERT(result);
    }

    int ZoneEarthtubeParameters_Impl::nodesBelowEarthTube() const {
      if (auto value = getInt(ZoneEarthtube_ParametersFields::NodesBelowEarthTube, false)) {
        return *value;
      }
      return 3;
    }

    bool ZoneEarthtubeParameters_Impl::isNodesBelowEarthTubeDefaulted() const {
      return isEmpty(ZoneEarthtube_ParametersFields::NodesBelowEarthTube);
    }

    bool ZoneEarthtubeParameters_Impl::setNodesBelowEarthTube(int nodesBelowEarthTube) {
      const bool result = setInt(ZoneEarthtube_ParametersFields::NodesBelowEarthTube, nodesBelowEarthTube);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtubeParameters_Impl::resetNodesBelowEarthTube() {
      const bool result = setString(ZoneEarthtube_ParametersFields::NodesBelowEarthTube, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtubeParameters_Impl::earthTubeDimensionlessBoundaryAbove() const {
      if (auto value = getDouble(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryAbove, false)) {
        return *value;
      }
      return 1.0;
    }

    bool ZoneEarthtubeParameters_Impl::isEarthTubeDimensionlessBoundaryAboveDefaulted() const {
      return isEmpty(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryAbove);
    }

    bool ZoneEarthtubeParameters_Impl::setEarthTubeDimensionlessBoundaryAbove(double earthTubeDimensionlessBoundaryAbove) {
      const bool result = setDouble(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryAbove, earthTubeDimensionlessBoundaryAbove);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtubeParameters_Impl::resetEarthTubeDimensionlessBoundaryAbove() {
      const bool result = setString(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryAbove, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtubeParameters_Impl::earthTubeDimensionlessBoundaryBelow() const {
      if (auto value = getDouble(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryBelow, false)) {
        return *value;
      }
      return 0.25;
    }

    bool ZoneEarthtubeParameters_Impl::isEarthTubeDimensionlessBoundaryBelowDefaulted() const {
      return isEmpty(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryBelow);
    }

    bool ZoneEarthtubeParameters_Impl::setEarthTubeDimensionlessBoundaryBelow(double earthTubeDimensionlessBoundaryBelow) {
      const bool result = setDouble(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryBelow, earthTubeDimensionlessBoundaryBelow);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtubeParameters_Impl::resetEarthTubeDimensionlessBoundaryBelow() {
      const bool result = setString(ZoneEarthtube_ParametersFields::EarthTubeDimensionlessBoundaryBelow, "");
      OS_ASSERT(result);
    }

    double ZoneEarthtubeParameters_Impl::earthTubeSolutionSpaceWidth() const {
      if (auto value = getDouble(ZoneEarthtube_ParametersFields::EarthTubeSolutionSpaceWidth, false)) {
        return *value;
      }
      return 4.0;
    }

    bool ZoneEarthtubeParameters_Impl::isEarthTubeSolutionSpaceWidthDefaulted() const {
      return isEmpty(ZoneEarthtube_ParametersFields::EarthTubeSolutionSpaceWidth);
    }

    bool ZoneEarthtubeParameters_Impl::setEarthTubeSolutionSpaceWidth(double earthTubeSolutionSpaceWidth) {
      const bool result = setDouble(ZoneEarthtube_ParametersFields::EarthTubeSolutionSpaceWidth, earthTubeSolutionSpaceWidth);
      OS_ASSERT(result);
      return result;
    }

    void ZoneEarthtubeParameters_Impl::resetEarthTubeSolutionSpaceWidth() {
      const bool result = setString(ZoneEarthtube_ParametersFields::EarthTubeSolutionSpaceWidth, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
