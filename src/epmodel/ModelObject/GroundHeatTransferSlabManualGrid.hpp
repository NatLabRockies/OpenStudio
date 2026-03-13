/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMANUALGRID_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMANUALGRID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabManualGrid_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabManualGrid : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabManualGrid(const Model& model);

    virtual ~GroundHeatTransferSlabManualGrid() override = default;
    GroundHeatTransferSlabManualGrid(const GroundHeatTransferSlabManualGrid& other) = default;
    GroundHeatTransferSlabManualGrid(GroundHeatTransferSlabManualGrid&& other) = default;
    GroundHeatTransferSlabManualGrid& operator=(const GroundHeatTransferSlabManualGrid&) = default;
    GroundHeatTransferSlabManualGrid& operator=(GroundHeatTransferSlabManualGrid&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:ManualGrid numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
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

   protected:
    using ImplType = detail::GroundHeatTransferSlabManualGrid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabManualGrid(std::shared_ptr<detail::GroundHeatTransferSlabManualGrid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
