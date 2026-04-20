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
      bool setNXNumberofcellsintheXdirection(int nXNumberofcellsintheXdirection);

      int nYNumberofcellsintheYdirection() const;
      bool setNYNumberofcellsintheYdirection(int nYNumberofcellsintheYdirection);

      int nZNumberofcellsintheZdirection() const;
      bool setNZNumberofcellsintheZdirection(int nZNumberofcellsintheZdirection);

      int iBOXXdirectioncellindicatorofslabedge() const;
      bool setIBOXXdirectioncellindicatorofslabedge(int iBOXXdirectioncellindicatorofslabedge);

      int jBOXYdirectioncellindicatorofslabedge() const;
      bool setJBOXYdirectioncellindicatorofslabedge(int jBOXYdirectioncellindicatorofslabedge);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
