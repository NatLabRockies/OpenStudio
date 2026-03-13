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

     private:
      REGISTER_LOGGER("openstudio.epmodel.SpaceInfiltrationDesignFlowRate");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
