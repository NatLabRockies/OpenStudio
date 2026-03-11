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
    boost::optional<double> flowperSpaceFloorArea() const;
    boost::optional<double> flowperExteriorSurfaceArea() const;
    boost::optional<double> flowperExteriorWallArea() const;
    boost::optional<double> airChangesperHour() const;

    double constantTermCoefficient() const;
    bool isConstantTermCoefficientDefaulted() const;
    double temperatureTermCoefficient() const;
    bool isTemperatureTermCoefficientDefaulted() const;
    double velocityTermCoefficient() const;
    bool isVelocityTermCoefficientDefaulted() const;
    double velocitySquaredTermCoefficient() const;
    bool isVelocitySquaredTermCoefficientDefaulted() const;

    std::string densityBasis() const;

    bool setDesignFlowRate(double designFlowRate);
    bool setFlowperSpaceFloorArea(double flowperSpaceFloorArea);
    bool setFlowperExteriorSurfaceArea(double flowperExteriorSurfaceArea);
    bool setFlowperExteriorWallArea(double flowperExteriorWallArea);
    bool setAirChangesperHour(double airChangesperHour);

    bool setConstantTermCoefficient(double constantTermCoefficient);
    void resetConstantTermCoefficient();

    bool setTemperatureTermCoefficient(double temperatureTermCoefficient);
    void resetTemperatureTermCoefficient();

    bool setVelocityTermCoefficient(double velocityTermCoefficient);
    void resetVelocityTermCoefficient();

    bool setVelocitySquaredTermCoefficient(double velocitySquaredTermCoefficient);
    void resetVelocitySquaredTermCoefficient();

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
