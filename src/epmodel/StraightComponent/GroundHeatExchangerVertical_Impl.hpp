/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
class WorkspaceObject;
namespace epmodel {
  namespace detail {

    class EPMODEL_API GroundHeatExchangerVertical_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~GroundHeatExchangerVertical_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> designFlowRate() const;
      bool setDesignFlowRate(double designFlowRate);

      boost::optional<double> groundThermalConductivity() const;
      bool setGroundThermalConductivity(double groundThermalConductivity);
      void resetGroundThermalConductivity();

      boost::optional<double> groundThermalHeatCapacity() const;
      bool setGroundThermalHeatCapacity(double groundThermalHeatCapacity);
      void resetGroundThermalHeatCapacity();

      double boreHoleTopDepth() const;
      bool setBoreHoleTopDepth(double boreHoleTopDepth);

      boost::optional<double> boreHoleLength() const;
      bool setBoreHoleLength(double boreHoleLength);
      void resetBoreHoleLength();

      boost::optional<double> boreHoleRadius() const;
      bool setBoreHoleRadius(double boreHoleRadius);
      void resetBoreHoleRadius();

      boost::optional<double> groutThermalConductivity() const;
      bool setGroutThermalConductivity(double groutThermalConductivity);
      void resetGroutThermalConductivity();

      boost::optional<double> pipeThermalConductivity() const;
      bool setPipeThermalConductivity(double pipeThermalConductivity);
      void resetPipeThermalConductivity();

      boost::optional<double> pipeOutDiameter() const;
      bool setPipeOutDiameter(double pipeOutDiameter);
      void resetPipeOutDiameter();

      boost::optional<double> uTubeDistance() const;
      bool setUTubeDistance(double uTubeDistance);
      void resetUTubeDistance();

      boost::optional<double> pipeThickness() const;
      bool setPipeThickness(double pipeThickness);
      void resetPipeThickness();

      boost::optional<int> numberofBoreHoles() const;
      bool setNumberofBoreHoles(int numberofBoreHoles);
      void resetNumberofBoreHoles();

      double gFunctionReferenceRatio() const;
      bool isGFunctionReferenceRatioDefaulted() const;
      bool setGFunctionReferenceRatio(double gFunctionReferenceRatio);
      void resetGFunctionReferenceRatio();

     private:
      boost::optional<openstudio::WorkspaceObject> groundHeatExchangerSystem() const;
      boost::optional<openstudio::WorkspaceObject> getOrCreateGroundHeatExchangerSystem();
      boost::optional<openstudio::WorkspaceObject> groundHeatExchangerVerticalProperties() const;
      boost::optional<openstudio::WorkspaceObject> getOrCreateGroundHeatExchangerVerticalProperties();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
