/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTBLDGDATA_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTBLDGDATA_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferBasementBldgData_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferBasementBldgData_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
