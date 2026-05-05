/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTTERMINALUNIT_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTTERMINALUNIT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkDistributionComponentTerminalUnit_Impl;
  }

  class EPMODEL_API AirflowNetworkDistributionComponentTerminalUnit : public ModelObject
  {
   public:
    explicit AirflowNetworkDistributionComponentTerminalUnit(const Model& model);

    virtual ~AirflowNetworkDistributionComponentTerminalUnit() override = default;
    AirflowNetworkDistributionComponentTerminalUnit(const AirflowNetworkDistributionComponentTerminalUnit& other) = default;
    AirflowNetworkDistributionComponentTerminalUnit(AirflowNetworkDistributionComponentTerminalUnit&& other) = default;
    AirflowNetworkDistributionComponentTerminalUnit& operator=(const AirflowNetworkDistributionComponentTerminalUnit&) = default;
    AirflowNetworkDistributionComponentTerminalUnit& operator=(AirflowNetworkDistributionComponentTerminalUnit&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> terminalUnitObjectTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: terminalUnitObjectType, airPathLength, and airPathHydraulicDiameter map
    //   directly to EnergyPlus AirflowNetwork:Distribution:Component:TerminalUnit scalar fields.
    // - Field Mapping: Terminal Unit Name is an object-list target-link field and is intentionally
    //   excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    std::string terminalUnitObjectType() const;
    bool setTerminalUnitObjectType(const std::string& terminalUnitObjectType);

    double airPathLength() const;
    bool setAirPathLength(double airPathLength);

    double airPathHydraulicDiameter() const;
    bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);

   protected:
    using ImplType = detail::AirflowNetworkDistributionComponentTerminalUnit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkDistributionComponentTerminalUnit(std::shared_ptr<detail::AirflowNetworkDistributionComponentTerminalUnit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
