/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEINFILTRATIONDESIGNFLOWRATE_IMPL_HPP
#define EPMODEL_SPACEINFILTRATIONDESIGNFLOWRATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <boost/optional.hpp>

#include <string>

namespace openstudio {
namespace epmodel {

  class Model_Impl;

  namespace detail {

    class EPMODEL_API SpaceInfiltrationDesignFlowRate_Impl : public ModelObject_Impl
    {
     public:
      SpaceInfiltrationDesignFlowRate_Impl(const IdfObject& object, Model_Impl* model, bool keepHandle);
      SpaceInfiltrationDesignFlowRate_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      SpaceInfiltrationDesignFlowRate_Impl(const SpaceInfiltrationDesignFlowRate_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~SpaceInfiltrationDesignFlowRate_Impl() override = default;

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

      std::string densityBasis() const;
      bool setDensityBasis(const std::string& densityBasis);

     private:
      REGISTER_LOGGER("openstudio.epmodel.SpaceInfiltrationDesignFlowRate");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
