/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCOIL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCOIL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentCoil_Impl;
  }

  /** \brief Represents the EnergyPlus AirflowNetwork:Distribution:Component:Coil object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkdistributioncomponentcoil,AirflowNetwork:Distribution:Component:Coil}
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for this EnergyPlus object. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * No known EPModel-specific limitations beyond the public fields and relationships exposed by this wrapper.
   */
  class EPMODEL_API AirflowNetworkDistributionComponentCoil : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentCoil(const Model& model);

    virtual ~AirflowNetworkDistributionComponentCoil() override = default;
    AirflowNetworkDistributionComponentCoil(const AirflowNetworkDistributionComponentCoil& other) = default;
    AirflowNetworkDistributionComponentCoil(AirflowNetworkDistributionComponentCoil&& other) = default;
    AirflowNetworkDistributionComponentCoil& operator=(const AirflowNetworkDistributionComponentCoil&) = default;
    AirflowNetworkDistributionComponentCoil& operator=(AirflowNetworkDistributionComponentCoil&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> coilObjectTypeValues();

    std::string coilObjectType() const;
    bool setCoilObjectType(const std::string& coilObjectType);

    double airPathLength() const;
    bool setAirPathLength(double airPathLength);

    double airPathHydraulicDiameter() const;
    bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentCoil_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentCoil(std::shared_ptr<detail::AirflowNetworkDistributionComponentCoil_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
