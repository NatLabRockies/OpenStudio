/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTMANUALGRID_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTMANUALGRID_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferBasementManualGrid_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferBasementManualGrid_Impl() override = default;

  int nXNumberofcellsintheXdirection20() const;
  int nYNumberofcellsintheYdirection20() const;
  int nZAGNumberofcellsintheZdirectionabovegrade4Always() const;
  int nZBGNumberofcellsinZdirectionbelowgrade1035() const;
  int iBASEXdirectioncellindicatorofslabedge520() const;
  int jBASEYdirectioncellindicatorofslabedge520() const;
  int kBASEZdirectioncellindicatorofthetopofthefloorslab520() const;

  bool setNXNumberofcellsintheXdirection20(int nXNumberofcellsintheXdirection20);
  bool setNYNumberofcellsintheYdirection20(int nYNumberofcellsintheYdirection20);
  bool setNZAGNumberofcellsintheZdirectionabovegrade4Always(int nZAGNumberofcellsintheZdirectionabovegrade4Always);
  bool setNZBGNumberofcellsinZdirectionbelowgrade1035(int nZBGNumberofcellsinZdirectionbelowgrade1035);
  bool setIBASEXdirectioncellindicatorofslabedge520(int iBASEXdirectioncellindicatorofslabedge520);
  bool setJBASEYdirectioncellindicatorofslabedge520(int jBASEYdirectioncellindicatorofslabedge520);
  bool setKBASEZdirectioncellindicatorofthetopofthefloorslab520(int kBASEZdirectioncellindicatorofthetopofthefloorslab520);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
