/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTSIZING_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONDUCTSIZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionDuctSizing_Impl;
  }

  class EPMODEL_API AirflowNetworkDistributionDuctSizing : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionDuctSizing(const Model& model);

    virtual ~AirflowNetworkDistributionDuctSizing() override = default;
    AirflowNetworkDistributionDuctSizing(const AirflowNetworkDistributionDuctSizing& other) = default;
    AirflowNetworkDistributionDuctSizing(AirflowNetworkDistributionDuctSizing&& other) = default;
    AirflowNetworkDistributionDuctSizing& operator=(const AirflowNetworkDistributionDuctSizing&) = default;
    AirflowNetworkDistributionDuctSizing& operator=(AirflowNetworkDistributionDuctSizing&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> ductSizingMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: Name is a relationship-like object-list field in this IDD object and remains
    //   available via base ModelObject naming API.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus
    //   AirflowNetwork:Distribution:DuctSizing scalar fields.
    // - TODO(parity): Re-evaluate naming if a future model-counterpart parity layer is introduced.
    std::string ductSizingMethod() const;
    bool setDuctSizingMethod(const std::string& ductSizingMethod);
    void resetDuctSizingMethod();
    bool isDuctSizingMethodDefaulted() const;

    double ductSizingFactor() const;
    bool setDuctSizingFactor(double ductSizingFactor);
    void resetDuctSizingFactor();
    bool isDuctSizingFactorDefaulted() const;

    double maximumAirflowVelocity() const;
    bool setMaximumAirflowVelocity(double maximumAirflowVelocity);
    void resetMaximumAirflowVelocity();
    bool isMaximumAirflowVelocityDefaulted() const;

    boost::optional<double> totalPressureLossAcrossSupplyTrunk() const;
    bool setTotalPressureLossAcrossSupplyTrunk(double totalPressureLossAcrossSupplyTrunk);
    void resetTotalPressureLossAcrossSupplyTrunk();

    boost::optional<double> totalPressureLossAcrossSupplyBranch() const;
    bool setTotalPressureLossAcrossSupplyBranch(double totalPressureLossAcrossSupplyBranch);
    void resetTotalPressureLossAcrossSupplyBranch();

    boost::optional<double> totalPressureLossAcrossReturnTrunk() const;
    bool setTotalPressureLossAcrossReturnTrunk(double totalPressureLossAcrossReturnTrunk);
    void resetTotalPressureLossAcrossReturnTrunk();

    boost::optional<double> totalPressureLossAcrossReturnBranch() const;
    bool setTotalPressureLossAcrossReturnBranch(double totalPressureLossAcrossReturnBranch);
    void resetTotalPressureLossAcrossReturnBranch();

   protected:
    using ImplType = detail::AirflowNetworkDistributionDuctSizing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionDuctSizing(std::shared_ptr<detail::AirflowNetworkDistributionDuctSizing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
