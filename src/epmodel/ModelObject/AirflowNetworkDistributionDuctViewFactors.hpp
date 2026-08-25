/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTVIEWFACTORS_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTVIEWFACTORS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionDuctViewFactors_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:DuctViewFactors object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributionductviewfactor,AirflowNetwork:Distribution:DuctViewFactors}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionDuctViewFactors : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionDuctViewFactors(const Model& model);

    virtual ~AirflowNetworkDistributionDuctViewFactors() override = default;
    AirflowNetworkDistributionDuctViewFactors(const AirflowNetworkDistributionDuctViewFactors& other) = default;
    AirflowNetworkDistributionDuctViewFactors(AirflowNetworkDistributionDuctViewFactors&& other) = default;
    AirflowNetworkDistributionDuctViewFactors& operator=(const AirflowNetworkDistributionDuctViewFactors&) = default;
    AirflowNetworkDistributionDuctViewFactors& operator=(AirflowNetworkDistributionDuctViewFactors&&) = default;

    static IddObjectType iddObjectType();

    double ductSurfaceExposureFraction() const;
    bool isDuctSurfaceExposureFractionDefaulted() const;
    bool setDuctSurfaceExposureFraction(double ductSurfaceExposureFraction);
    void resetDuctSurfaceExposureFraction();

    // Duct surface emittance accessors
    double ductSurfaceEmittance() const;
    bool isDuctSurfaceEmittanceDefaulted() const;
    bool setDuctSurfaceEmittance(double ductSurfaceEmittance);
    void resetDuctSurfaceEmittance();

   protected:
    using ImplType = detail::AirflowNetworkDistributionDuctViewFactors_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionDuctViewFactors(std::shared_ptr<detail::AirflowNetworkDistributionDuctViewFactors_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
