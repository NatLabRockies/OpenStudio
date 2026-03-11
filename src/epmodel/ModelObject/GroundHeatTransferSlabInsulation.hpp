/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferSlabInsulation_Impl;
}

class EPMODEL_API GroundHeatTransferSlabInsulation : public ModelObject
{
 public:
  explicit GroundHeatTransferSlabInsulation(const Model& model);

  virtual ~GroundHeatTransferSlabInsulation() override = default;
  GroundHeatTransferSlabInsulation(const GroundHeatTransferSlabInsulation& other) = default;
  GroundHeatTransferSlabInsulation(GroundHeatTransferSlabInsulation&& other) = default;
  GroundHeatTransferSlabInsulation& operator=(const GroundHeatTransferSlabInsulation&) = default;
  GroundHeatTransferSlabInsulation& operator=(GroundHeatTransferSlabInsulation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> iVINSFlagIsthereverticalinsulationValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:Insulation fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  double rINSRvalueofunderslabinsulation() const;
  double dINSWidthofstripofunderslabinsulation() const;
  double rVINSRvalueofverticalinsulation() const;
  double zVINSDepthofverticalinsulation() const;
  std::string iVINSFlagIsthereverticalinsulation() const;

  bool isRINSRvalueofunderslabinsulationDefaulted() const;
  bool isDINSWidthofstripofunderslabinsulationDefaulted() const;
  bool isRVINSRvalueofverticalinsulationDefaulted() const;
  bool isZVINSDepthofverticalinsulationDefaulted() const;
  bool isIVINSFlagIsthereverticalinsulationDefaulted() const;

  bool setRINSRvalueofunderslabinsulation(double rINSRvalueofunderslabinsulation);
  bool setDINSWidthofstripofunderslabinsulation(double dINSWidthofstripofunderslabinsulation);
  bool setRVINSRvalueofverticalinsulation(double rVINSRvalueofverticalinsulation);
  bool setZVINSDepthofverticalinsulation(double zVINSDepthofverticalinsulation);
  bool setIVINSFlagIsthereverticalinsulation(const std::string& iVINSFlagIsthereverticalinsulation);

  void resetRINSRvalueofunderslabinsulation();
  void resetDINSWidthofstripofunderslabinsulation();
  void resetRVINSRvalueofverticalinsulation();
  void resetZVINSDepthofverticalinsulation();
  void resetIVINSFlagIsthereverticalinsulation();

 protected:
  using ImplType = detail::GroundHeatTransferSlabInsulation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferSlabInsulation(std::shared_ptr<detail::GroundHeatTransferSlabInsulation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
