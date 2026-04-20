/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatExchangerSurface.hpp"
#include "GroundHeatExchangerSurface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_Surface_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GroundHeatExchangerSurface::GroundHeatExchangerSurface(const Model& model) : ModelObject(GroundHeatExchangerSurface::iddObjectType(), model) {}

  GroundHeatExchangerSurface::GroundHeatExchangerSurface(std::shared_ptr<detail::GroundHeatExchangerSurface_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatExchangerSurface::iddObjectType() {
    return IddObjectType::GroundHeatExchanger_Surface;
  }

  std::vector<std::string> GroundHeatExchangerSurface::lowerSurfaceEnvironmentValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::GroundHeatExchanger_SurfaceFields::LowerSurfaceEnvironment);
  }

  boost::optional<double> GroundHeatExchangerSurface::hydronicTubingInsideDiameter() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->hydronicTubingInsideDiameter();
  }

  bool GroundHeatExchangerSurface::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
  }

  void GroundHeatExchangerSurface::resetHydronicTubingInsideDiameter() {
    getImpl<detail::GroundHeatExchangerSurface_Impl>()->resetHydronicTubingInsideDiameter();
  }

  boost::optional<int> GroundHeatExchangerSurface::numberofTubingCircuits() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->numberofTubingCircuits();
  }

  bool GroundHeatExchangerSurface::setNumberofTubingCircuits(int numberofTubingCircuits) {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->setNumberofTubingCircuits(numberofTubingCircuits);
  }

  void GroundHeatExchangerSurface::resetNumberofTubingCircuits() {
    getImpl<detail::GroundHeatExchangerSurface_Impl>()->resetNumberofTubingCircuits();
  }

  boost::optional<double> GroundHeatExchangerSurface::hydronicTubeSpacing() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->hydronicTubeSpacing();
  }

  bool GroundHeatExchangerSurface::setHydronicTubeSpacing(double hydronicTubeSpacing) {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->setHydronicTubeSpacing(hydronicTubeSpacing);
  }

  void GroundHeatExchangerSurface::resetHydronicTubeSpacing() {
    getImpl<detail::GroundHeatExchangerSurface_Impl>()->resetHydronicTubeSpacing();
  }

  boost::optional<double> GroundHeatExchangerSurface::surfaceLength() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->surfaceLength();
  }

  bool GroundHeatExchangerSurface::setSurfaceLength(double surfaceLength) {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->setSurfaceLength(surfaceLength);
  }

  void GroundHeatExchangerSurface::resetSurfaceLength() {
    getImpl<detail::GroundHeatExchangerSurface_Impl>()->resetSurfaceLength();
  }

  boost::optional<double> GroundHeatExchangerSurface::surfaceWidth() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->surfaceWidth();
  }

  bool GroundHeatExchangerSurface::setSurfaceWidth(double surfaceWidth) {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->setSurfaceWidth(surfaceWidth);
  }

  void GroundHeatExchangerSurface::resetSurfaceWidth() {
    getImpl<detail::GroundHeatExchangerSurface_Impl>()->resetSurfaceWidth();
  }

  std::string GroundHeatExchangerSurface::lowerSurfaceEnvironment() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->lowerSurfaceEnvironment();
  }

  bool GroundHeatExchangerSurface::isLowerSurfaceEnvironmentDefaulted() const {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->isLowerSurfaceEnvironmentDefaulted();
  }

  bool GroundHeatExchangerSurface::setLowerSurfaceEnvironment(const std::string& lowerSurfaceEnvironment) {
    return getImpl<detail::GroundHeatExchangerSurface_Impl>()->setLowerSurfaceEnvironment(lowerSurfaceEnvironment);
  }

  void GroundHeatExchangerSurface::resetLowerSurfaceEnvironment() {
    getImpl<detail::GroundHeatExchangerSurface_Impl>()->resetLowerSurfaceEnvironment();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> GroundHeatExchangerSurface_Impl::hydronicTubingInsideDiameter() const {
      return getDouble(openstudio::GroundHeatExchanger_SurfaceFields::HydronicTubingInsideDiameter, true);
    }

    bool GroundHeatExchangerSurface_Impl::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
      return setDouble(openstudio::GroundHeatExchanger_SurfaceFields::HydronicTubingInsideDiameter, hydronicTubingInsideDiameter);
    }

    void GroundHeatExchangerSurface_Impl::resetHydronicTubingInsideDiameter() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SurfaceFields::HydronicTubingInsideDiameter, ""));
    }

    boost::optional<int> GroundHeatExchangerSurface_Impl::numberofTubingCircuits() const {
      return getInt(openstudio::GroundHeatExchanger_SurfaceFields::NumberofTubingCircuits, true);
    }

    bool GroundHeatExchangerSurface_Impl::setNumberofTubingCircuits(int numberofTubingCircuits) {
      return setInt(openstudio::GroundHeatExchanger_SurfaceFields::NumberofTubingCircuits, numberofTubingCircuits);
    }

    void GroundHeatExchangerSurface_Impl::resetNumberofTubingCircuits() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SurfaceFields::NumberofTubingCircuits, ""));
    }

    boost::optional<double> GroundHeatExchangerSurface_Impl::hydronicTubeSpacing() const {
      return getDouble(openstudio::GroundHeatExchanger_SurfaceFields::HydronicTubeSpacing, true);
    }

    bool GroundHeatExchangerSurface_Impl::setHydronicTubeSpacing(double hydronicTubeSpacing) {
      return setDouble(openstudio::GroundHeatExchanger_SurfaceFields::HydronicTubeSpacing, hydronicTubeSpacing);
    }

    void GroundHeatExchangerSurface_Impl::resetHydronicTubeSpacing() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SurfaceFields::HydronicTubeSpacing, ""));
    }

    boost::optional<double> GroundHeatExchangerSurface_Impl::surfaceLength() const {
      return getDouble(openstudio::GroundHeatExchanger_SurfaceFields::SurfaceLength, true);
    }

    bool GroundHeatExchangerSurface_Impl::setSurfaceLength(double surfaceLength) {
      return setDouble(openstudio::GroundHeatExchanger_SurfaceFields::SurfaceLength, surfaceLength);
    }

    void GroundHeatExchangerSurface_Impl::resetSurfaceLength() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SurfaceFields::SurfaceLength, ""));
    }

    boost::optional<double> GroundHeatExchangerSurface_Impl::surfaceWidth() const {
      return getDouble(openstudio::GroundHeatExchanger_SurfaceFields::SurfaceWidth, true);
    }

    bool GroundHeatExchangerSurface_Impl::setSurfaceWidth(double surfaceWidth) {
      return setDouble(openstudio::GroundHeatExchanger_SurfaceFields::SurfaceWidth, surfaceWidth);
    }

    void GroundHeatExchangerSurface_Impl::resetSurfaceWidth() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SurfaceFields::SurfaceWidth, ""));
    }

    std::string GroundHeatExchangerSurface_Impl::lowerSurfaceEnvironment() const {
      const auto value = getString(openstudio::GroundHeatExchanger_SurfaceFields::LowerSurfaceEnvironment, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatExchangerSurface_Impl::isLowerSurfaceEnvironmentDefaulted() const {
      return isEmpty(openstudio::GroundHeatExchanger_SurfaceFields::LowerSurfaceEnvironment);
    }

    bool GroundHeatExchangerSurface_Impl::setLowerSurfaceEnvironment(const std::string& lowerSurfaceEnvironment) {
      return setString(openstudio::GroundHeatExchanger_SurfaceFields::LowerSurfaceEnvironment, lowerSurfaceEnvironment);
    }

    void GroundHeatExchangerSurface_Impl::resetLowerSurfaceEnvironment() {
      OS_ASSERT(setString(openstudio::GroundHeatExchanger_SurfaceFields::LowerSurfaceEnvironment, ""));
    }

    std::vector<std::string> GroundHeatExchangerSurface_Impl::lowerSurfaceEnvironmentValues() const {
      return openstudio::epmodel::GroundHeatExchangerSurface::lowerSurfaceEnvironmentValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
