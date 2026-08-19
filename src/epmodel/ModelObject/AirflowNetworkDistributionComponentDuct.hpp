/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTDUCT_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTDUCT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentDuct_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:Duct object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributioncomponentduct,AirflowNetwork:Distribution:Component:Duct}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionComponentDuct : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentDuct(const Model& model);

    virtual ~AirflowNetworkDistributionComponentDuct() override = default;
    AirflowNetworkDistributionComponentDuct(const AirflowNetworkDistributionComponentDuct& other) = default;
    AirflowNetworkDistributionComponentDuct(AirflowNetworkDistributionComponentDuct&& other) = default;
    AirflowNetworkDistributionComponentDuct& operator=(const AirflowNetworkDistributionComponentDuct&) = default;
    AirflowNetworkDistributionComponentDuct& operator=(AirflowNetworkDistributionComponentDuct&&) = default;

    static IddObjectType iddObjectType();

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

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentDuct_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentDuct(std::shared_ptr<detail::AirflowNetworkDistributionComponentDuct_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
