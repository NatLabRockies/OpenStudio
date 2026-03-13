/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEINFILTRATIONDESIGNFLOWRATE_HPP
#define EPMODEL_SPACEINFILTRATIONDESIGNFLOWRATE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SpaceInfiltrationDesignFlowRate_Impl;
  }

  class EPMODEL_API SpaceInfiltrationDesignFlowRate : public ModelObject
  {
   public:
    explicit SpaceInfiltrationDesignFlowRate(const Model& model);

    virtual ~SpaceInfiltrationDesignFlowRate() override = default;
    SpaceInfiltrationDesignFlowRate(const SpaceInfiltrationDesignFlowRate& other) = default;
    SpaceInfiltrationDesignFlowRate(SpaceInfiltrationDesignFlowRate&& other) = default;
    SpaceInfiltrationDesignFlowRate& operator=(const SpaceInfiltrationDesignFlowRate&) = default;
    SpaceInfiltrationDesignFlowRate& operator=(SpaceInfiltrationDesignFlowRate&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designFlowRateCalculationMethodValues();
    static std::vector<std::string> densityBasisValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names for the ZoneInfiltration:DesignFlowRate model-counterpart.
    // - Field Mapping: designFlowRateCalculationMethod, design/flow constants, and densityBasis map directly to the EnergyPlus fields.
    // - Field Mapping: Space/SpaceType relationships plus schedule references are intentionally excluded from this scalar-only API.
    // - TODO(parity): Add relationship helpers once scheduler/space targets migrate.
    std::string designFlowRateCalculationMethod() const;

    boost::optional<double> designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);

    boost::optional<double> flowperSpaceFloorArea() const;
    bool setFlowperSpaceFloorArea(double flowperSpaceFloorArea);

    boost::optional<double> flowperExteriorSurfaceArea() const;
    bool setFlowperExteriorSurfaceArea(double flowperExteriorSurfaceArea);

    boost::optional<double> flowperExteriorWallArea() const;
    bool setFlowperExteriorWallArea(double flowperExteriorWallArea);

    boost::optional<double> airChangesperHour() const;
    bool setAirChangesperHour(double airChangesperHour);

    double constantTermCoefficient() const;
    bool isConstantTermCoefficientDefaulted() const;
    bool setConstantTermCoefficient(double constantTermCoefficient);
    void resetConstantTermCoefficient();

    double temperatureTermCoefficient() const;
    bool isTemperatureTermCoefficientDefaulted() const;
    bool setTemperatureTermCoefficient(double temperatureTermCoefficient);
    void resetTemperatureTermCoefficient();

    double velocityTermCoefficient() const;
    bool isVelocityTermCoefficientDefaulted() const;
    bool setVelocityTermCoefficient(double velocityTermCoefficient);
    void resetVelocityTermCoefficient();

    double velocitySquaredTermCoefficient() const;
    bool isVelocitySquaredTermCoefficientDefaulted() const;
    bool setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient);
    void resetVelocitySquaredTermCoefficient();

    std::string densityBasis() const;
    bool setDensityBasis(const std::string& densityBasis);

   protected:
    using ImplType = detail::SpaceInfiltrationDesignFlowRate_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SpaceInfiltrationDesignFlowRate(std::shared_ptr<detail::SpaceInfiltrationDesignFlowRate_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
