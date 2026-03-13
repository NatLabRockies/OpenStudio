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

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus
    //   AirflowNetwork:Distribution:DuctViewFactors scalar fields.
    // - ForwardTranslator evidence: translateAirflowNetworkDuctViewFactors writes these scalar fields directly.
    // - Field Mapping: Linkage Name and extensible Surface Name/View Factor pairs are relationship/extensible fields
    //   and intentionally excluded from simple scalar accessor scaffolding.
    // - TODO(parity): Re-evaluate naming/coverage if a future model-counterpart parity layer is introduced.
    // Duct surface exposure fraction accessors
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
