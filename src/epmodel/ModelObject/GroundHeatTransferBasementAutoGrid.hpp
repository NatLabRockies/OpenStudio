/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTAUTOGRID_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTAUTOGRID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferBasementAutoGrid_Impl;
}

class EPMODEL_API GroundHeatTransferBasementAutoGrid : public ModelObject
{
 public:
  explicit GroundHeatTransferBasementAutoGrid(const Model& model);

  virtual ~GroundHeatTransferBasementAutoGrid() override = default;
  GroundHeatTransferBasementAutoGrid(const GroundHeatTransferBasementAutoGrid& other) = default;
  GroundHeatTransferBasementAutoGrid(GroundHeatTransferBasementAutoGrid&& other) = default;
  GroundHeatTransferBasementAutoGrid& operator=(const GroundHeatTransferBasementAutoGrid&) = default;
  GroundHeatTransferBasementAutoGrid& operator=(GroundHeatTransferBasementAutoGrid&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:AutoGrid numeric fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  double clearanceDistancefromoutsideofwalltoedge() const;
  double slabxXdimensionofthebuildingslab() const;
  double slabyYdimensionofthebuildingslab() const;
  double concAGHeightHeightofthefoundationwallabovegrade() const;
  double slabDepthThicknessofthefloorslab() const;
  double baseDepthDepthofthebasementwallbelowgrade() const;

  bool isClearanceDistancefromoutsideofwalltoedgeDefaulted() const;
  bool isConcAGHeightHeightofthefoundationwallabovegradeDefaulted() const;
  bool isSlabDepthThicknessofthefloorslabDefaulted() const;
  bool isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const;

  bool setClearanceDistancefromoutsideofwalltoedge(double clearanceDistancefromoutsideofwalltoedge);
  bool setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab);
  bool setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab);
  bool setConcAGHeightHeightofthefoundationwallabovegrade(double concAGHeightHeightofthefoundationwallabovegrade);
  bool setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab);
  bool setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade);

  void resetClearanceDistancefromoutsideofwalltoedge();
  void resetConcAGHeightHeightofthefoundationwallabovegrade();
  void resetSlabDepthThicknessofthefloorslab();
  void resetBaseDepthDepthofthebasementwallbelowgrade();

 protected:
  using ImplType = detail::GroundHeatTransferBasementAutoGrid_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferBasementAutoGrid(std::shared_ptr<detail::GroundHeatTransferBasementAutoGrid_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
