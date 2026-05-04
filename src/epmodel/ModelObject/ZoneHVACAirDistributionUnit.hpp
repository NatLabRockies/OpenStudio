/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACAIRDISTRIBUTIONUNIT_HPP
#define EPMODEL_ZONEHVACAIRDISTRIBUTIONUNIT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class ZoneHVACAirDistributionUnit_Impl;
}

class EPMODEL_API ZoneHVACAirDistributionUnit : public ModelObject
{
 public:
  explicit ZoneHVACAirDistributionUnit(const Model& model);

  virtual ~ZoneHVACAirDistributionUnit() override = default;
  ZoneHVACAirDistributionUnit(const ZoneHVACAirDistributionUnit& other) = default;
  ZoneHVACAirDistributionUnit(ZoneHVACAirDistributionUnit&& other) = default;
  ZoneHVACAirDistributionUnit& operator=(const ZoneHVACAirDistributionUnit&) = default;
  ZoneHVACAirDistributionUnit& operator=(ZoneHVACAirDistributionUnit&&) = default;

  static IddObjectType iddObjectType();

  boost::optional<ModelObject> airTerminal() const;

  boost::optional<Node> outletNode() const;

 protected:
  using ImplType = detail::ZoneHVACAirDistributionUnit_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class Model;

  explicit ZoneHVACAirDistributionUnit(std::shared_ptr<detail::ZoneHVACAirDistributionUnit_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
