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
      bool setNXNumberofcellsintheXdirection20(int nXNumberofcellsintheXdirection20);

      int nYNumberofcellsintheYdirection20() const;
      bool setNYNumberofcellsintheYdirection20(int nYNumberofcellsintheYdirection20);

      int nZAGNumberofcellsintheZdirectionabovegrade4Always() const;
      bool setNZAGNumberofcellsintheZdirectionabovegrade4Always(int nZAGNumberofcellsintheZdirectionabovegrade4Always);

      int nZBGNumberofcellsinZdirectionbelowgrade1035() const;
      bool setNZBGNumberofcellsinZdirectionbelowgrade1035(int nZBGNumberofcellsinZdirectionbelowgrade1035);

      int iBASEXdirectioncellindicatorofslabedge520() const;
      bool setIBASEXdirectioncellindicatorofslabedge520(int iBASEXdirectioncellindicatorofslabedge520);

      int jBASEYdirectioncellindicatorofslabedge520() const;
      bool setJBASEYdirectioncellindicatorofslabedge520(int jBASEYdirectioncellindicatorofslabedge520);

      int kBASEZdirectioncellindicatorofthetopofthefloorslab520() const;
      bool setKBASEZdirectioncellindicatorofthetopofthefloorslab520(int kBASEZdirectioncellindicatorofthetopofthefloorslab520);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
