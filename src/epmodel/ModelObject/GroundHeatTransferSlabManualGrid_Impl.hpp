/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMANUALGRID_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMANUALGRID_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabManualGrid_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabManualGrid_Impl() override = default;

  int nXNumberofcellsintheXdirection() const;
  int nYNumberofcellsintheYdirection() const;
  int nZNumberofcellsintheZdirection() const;
  int iBOXXdirectioncellindicatorofslabedge() const;
  int jBOXYdirectioncellindicatorofslabedge() const;

  bool setNXNumberofcellsintheXdirection(int nXNumberofcellsintheXdirection);
  bool setNYNumberofcellsintheYdirection(int nYNumberofcellsintheYdirection);
  bool setNZNumberofcellsintheZdirection(int nZNumberofcellsintheZdirection);
  bool setIBOXXdirectioncellindicatorofslabedge(int iBOXXdirectioncellindicatorofslabedge);
  bool setJBOXYdirectioncellindicatorofslabedge(int jBOXYdirectioncellindicatorofslabedge);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
