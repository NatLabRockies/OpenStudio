/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACECRACK_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACECRACK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkMultiZoneSurfaceCrack_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:MultiZone:Surface:Crack object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkmultizonesurfacecrack,AirflowNetwork:MultiZone:Surface:Crack}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkMultiZoneSurfaceCrack : public ModelObject
  {
   public:
    explicit AirflowNetworkMultiZoneSurfaceCrack(const Model& model);

    virtual ~AirflowNetworkMultiZoneSurfaceCrack() override = default;
    AirflowNetworkMultiZoneSurfaceCrack(const AirflowNetworkMultiZoneSurfaceCrack& other) = default;
    AirflowNetworkMultiZoneSurfaceCrack(AirflowNetworkMultiZoneSurfaceCrack&& other) = default;
    AirflowNetworkMultiZoneSurfaceCrack& operator=(const AirflowNetworkMultiZoneSurfaceCrack&) = default;
    AirflowNetworkMultiZoneSurfaceCrack& operator=(AirflowNetworkMultiZoneSurfaceCrack&&) = default;

    static IddObjectType iddObjectType();

    /** Accessors for Air Mass Flow Coefficient at Reference Conditions. */
    double airMassFlowCoefficientatReferenceConditions() const;
    bool setAirMassFlowCoefficientatReferenceConditions(double airMassFlowCoefficientatReferenceConditions);

    /** Accessors for Air Mass Flow Exponent. */
    double airMassFlowExponent() const;
    bool isAirMassFlowExponentDefaulted() const;
    bool setAirMassFlowExponent(double airMassFlowExponent);
    void resetAirMassFlowExponent();

   protected:
    using ImplType = detail::AirflowNetworkMultiZoneSurfaceCrack_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkMultiZoneSurfaceCrack(std::shared_ptr<detail::AirflowNetworkMultiZoneSurfaceCrack_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
