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
      bool isDwallWallthicknessDefaulted() const;
      bool setDwallWallthickness(double dwallWallthickness);
      void resetDwallWallthickness();

      double dslabFloorslabthickness() const;
      bool isDslabFloorslabthicknessDefaulted() const;
      bool setDslabFloorslabthickness(double dslabFloorslabthickness);
      void resetDslabFloorslabthickness();

      double dgravxyWidthofgravelpitbesidebasementwall() const;
      bool isDgravxyWidthofgravelpitbesidebasementwallDefaulted() const;
      bool setDgravxyWidthofgravelpitbesidebasementwall(double dgravxyWidthofgravelpitbesidebasementwall);
      void resetDgravxyWidthofgravelpitbesidebasementwall();

      double dgravznGraveldepthextendingabovethefloorslab() const;
      bool isDgravznGraveldepthextendingabovethefloorslabDefaulted() const;
      bool setDgravznGraveldepthextendingabovethefloorslab(double dgravznGraveldepthextendingabovethefloorslab);
      void resetDgravznGraveldepthextendingabovethefloorslab();

      double dgravzpGraveldepthbelowthefloorslab() const;
      bool isDgravzpGraveldepthbelowthefloorslabDefaulted() const;
      bool setDgravzpGraveldepthbelowthefloorslab(double dgravzpGraveldepthbelowthefloorslab);
      void resetDgravzpGraveldepthbelowthefloorslab();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
