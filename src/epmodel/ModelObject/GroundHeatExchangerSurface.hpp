/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERSURFACE_HPP
#define EPMODEL_GROUNDHEATEXCHANGERSURFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatExchangerSurface_Impl;
  }

  class EPMODEL_API GroundHeatExchangerSurface : public ModelObject
  {
   public:
    explicit GroundHeatExchangerSurface(const Model& model);

    virtual ~GroundHeatExchangerSurface() override = default;
    GroundHeatExchangerSurface(const GroundHeatExchangerSurface& other) = default;
    GroundHeatExchangerSurface(GroundHeatExchangerSurface&& other) = default;
    GroundHeatExchangerSurface& operator=(const GroundHeatExchangerSurface&) = default;
    GroundHeatExchangerSurface& operator=(GroundHeatExchangerSurface&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> lowerSurfaceEnvironmentValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatExchanger:Surface numeric/choice fields.
    // - Field Mapping: Construction Name, Fluid Inlet Node Name, and Fluid Outlet Node Name are relationship-like fields and excluded.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

    boost::optional<double> hydronicTubingInsideDiameter() const;
    bool setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter);
    void resetHydronicTubingInsideDiameter();

    boost::optional<int> numberofTubingCircuits() const;
    bool setNumberofTubingCircuits(int numberofTubingCircuits);
    void resetNumberofTubingCircuits();

    boost::optional<double> hydronicTubeSpacing() const;
    bool setHydronicTubeSpacing(double hydronicTubeSpacing);
    void resetHydronicTubeSpacing();

    boost::optional<double> surfaceLength() const;
    bool setSurfaceLength(double surfaceLength);
    void resetSurfaceLength();

    boost::optional<double> surfaceWidth() const;
    bool setSurfaceWidth(double surfaceWidth);
    void resetSurfaceWidth();

    std::string lowerSurfaceEnvironment() const;
    bool isLowerSurfaceEnvironmentDefaulted() const;
    bool setLowerSurfaceEnvironment(const std::string& lowerSurfaceEnvironment);
    void resetLowerSurfaceEnvironment();

   protected:
    using ImplType = detail::GroundHeatExchangerSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerSurface(std::shared_ptr<detail::GroundHeatExchangerSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
