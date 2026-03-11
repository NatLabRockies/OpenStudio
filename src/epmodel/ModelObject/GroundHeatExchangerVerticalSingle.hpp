/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICALSINGLE_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICALSINGLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatExchangerVerticalSingle_Impl;
}

class EPMODEL_API GroundHeatExchangerVerticalSingle : public ModelObject
{
 public:
  explicit GroundHeatExchangerVerticalSingle(const Model& model);

  virtual ~GroundHeatExchangerVerticalSingle() override = default;
  GroundHeatExchangerVerticalSingle(const GroundHeatExchangerVerticalSingle& other) = default;
  GroundHeatExchangerVerticalSingle(GroundHeatExchangerVerticalSingle&& other) = default;
  GroundHeatExchangerVerticalSingle& operator=(const GroundHeatExchangerVerticalSingle&) = default;
  GroundHeatExchangerVerticalSingle& operator=(GroundHeatExchangerVerticalSingle&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatExchanger:Vertical:Single fields X-Location and Y-Location.
  // - Field Mapping: GHE:Vertical:Properties Object Name is an object-list relationship field and is excluded.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
  double xLocation() const;
  double yLocation() const;

  bool setXLocation(double xLocation);
  bool setYLocation(double yLocation);

 protected:
  using ImplType = detail::GroundHeatExchangerVerticalSingle_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatExchangerVerticalSingle(std::shared_ptr<detail::GroundHeatExchangerVerticalSingle_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
