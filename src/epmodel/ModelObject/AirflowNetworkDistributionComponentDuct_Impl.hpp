/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTDUCT_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTDUCT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkDistributionComponentDuct_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkDistributionComponentDuct_Impl() override = default;

      double ductLength() const;
      bool setDuctLength(double ductLength);

      double hydraulicDiameter() const;
      bool setHydraulicDiameter(double hydraulicDiameter);

      double crossSectionArea() const;
      bool setCrossSectionArea(double crossSectionArea);

      double surfaceRoughness() const;
      bool isSurfaceRoughnessDefaulted() const;
      bool setSurfaceRoughness(double surfaceRoughness);
      void resetSurfaceRoughness();

      double coefficientforLocalDynamicLossDuetoFitting() const;
      bool isCoefficientforLocalDynamicLossDuetoFittingDefaulted() const;
      bool setCoefficientforLocalDynamicLossDuetoFitting(double coefficientforLocalDynamicLossDuetoFitting);
      void resetCoefficientforLocalDynamicLossDuetoFitting();

      double heatTransmittanceCoefficientUFactorforDuctWallConstruction() const;
      bool isHeatTransmittanceCoefficientUFactorforDuctWallConstructionDefaulted() const;
      bool setHeatTransmittanceCoefficientUFactorforDuctWallConstruction(double heatTransmittanceCoefficientUFactorforDuctWallConstruction);
      void resetHeatTransmittanceCoefficientUFactorforDuctWallConstruction();

      double overallMoistureTransmittanceCoefficientfromAirtoAir() const;
      bool isOverallMoistureTransmittanceCoefficientfromAirtoAirDefaulted() const;
      bool setOverallMoistureTransmittanceCoefficientfromAirtoAir(double overallMoistureTransmittanceCoefficientfromAirtoAir);
      void resetOverallMoistureTransmittanceCoefficientfromAirtoAir();

      boost::optional<double> outsideConvectionCoefficient() const;
      bool setOutsideConvectionCoefficient(double outsideConvectionCoefficient);
      void resetOutsideConvectionCoefficient();

      boost::optional<double> insideConvectionCoefficient() const;
      bool setInsideConvectionCoefficient(double insideConvectionCoefficient);
      void resetInsideConvectionCoefficient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
