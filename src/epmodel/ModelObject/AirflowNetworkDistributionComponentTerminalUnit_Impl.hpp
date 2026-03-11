/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTTERMINALUNIT_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTTERMINALUNIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkDistributionComponentTerminalUnit_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkDistributionComponentTerminalUnit_Impl() override = default;

  std::string terminalUnitObjectType() const;
  bool setTerminalUnitObjectType(const std::string& terminalUnitObjectType);

  double airPathLength() const;
  bool setAirPathLength(double airPathLength);

  double airPathHydraulicDiameter() const;
  bool setAirPathHydraulicDiameter(double airPathHydraulicDiameter);

  std::vector<std::string> terminalUnitObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
