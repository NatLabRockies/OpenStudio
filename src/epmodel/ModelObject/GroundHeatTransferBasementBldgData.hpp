/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTBLDGDATA_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTBLDGDATA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferBasementBldgData_Impl;
}

class EPMODEL_API GroundHeatTransferBasementBldgData : public ModelObject
{
 public:
  explicit GroundHeatTransferBasementBldgData(const Model& model);

  virtual ~GroundHeatTransferBasementBldgData() override = default;
  GroundHeatTransferBasementBldgData(const GroundHeatTransferBasementBldgData& other) = default;
  GroundHeatTransferBasementBldgData(GroundHeatTransferBasementBldgData&& other) = default;
  GroundHeatTransferBasementBldgData& operator=(const GroundHeatTransferBasementBldgData&) = default;
  GroundHeatTransferBasementBldgData& operator=(GroundHeatTransferBasementBldgData&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:BldgData numeric fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  double dwallWallthickness() const;
  double dslabFloorslabthickness() const;
  double dgravxyWidthofgravelpitbesidebasementwall() const;
  double dgravznGraveldepthextendingabovethefloorslab() const;
  double dgravzpGraveldepthbelowthefloorslab() const;

  bool isDwallWallthicknessDefaulted() const;
  bool isDslabFloorslabthicknessDefaulted() const;
  bool isDgravxyWidthofgravelpitbesidebasementwallDefaulted() const;
  bool isDgravznGraveldepthextendingabovethefloorslabDefaulted() const;
  bool isDgravzpGraveldepthbelowthefloorslabDefaulted() const;

  bool setDwallWallthickness(double dwallWallthickness);
  bool setDslabFloorslabthickness(double dslabFloorslabthickness);
  bool setDgravxyWidthofgravelpitbesidebasementwall(double dgravxyWidthofgravelpitbesidebasementwall);
  bool setDgravznGraveldepthextendingabovethefloorslab(double dgravznGraveldepthextendingabovethefloorslab);
  bool setDgravzpGraveldepthbelowthefloorslab(double dgravzpGraveldepthbelowthefloorslab);

  void resetDwallWallthickness();
  void resetDslabFloorslabthickness();
  void resetDgravxyWidthofgravelpitbesidebasementwall();
  void resetDgravznGraveldepthextendingabovethefloorslab();
  void resetDgravzpGraveldepthbelowthefloorslab();

 protected:
  using ImplType = detail::GroundHeatTransferBasementBldgData_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferBasementBldgData(std::shared_ptr<detail::GroundHeatTransferBasementBldgData_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
