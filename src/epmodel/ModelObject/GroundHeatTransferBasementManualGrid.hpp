/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTMANUALGRID_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTMANUALGRID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementManualGrid_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementManualGrid : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementManualGrid(const Model& model);

    virtual ~GroundHeatTransferBasementManualGrid() override = default;
    GroundHeatTransferBasementManualGrid(const GroundHeatTransferBasementManualGrid& other) = default;
    GroundHeatTransferBasementManualGrid(GroundHeatTransferBasementManualGrid&& other) = default;
    GroundHeatTransferBasementManualGrid& operator=(const GroundHeatTransferBasementManualGrid&) = default;
    GroundHeatTransferBasementManualGrid& operator=(GroundHeatTransferBasementManualGrid&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:ManualGrid numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
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

   protected:
    using ImplType = detail::GroundHeatTransferBasementManualGrid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementManualGrid(std::shared_ptr<detail::GroundHeatTransferBasementManualGrid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
