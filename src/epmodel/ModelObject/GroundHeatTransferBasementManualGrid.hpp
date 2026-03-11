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
