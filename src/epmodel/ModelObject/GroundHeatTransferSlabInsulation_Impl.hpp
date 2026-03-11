/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabInsulation_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabInsulation_Impl() override = default;

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

  std::vector<std::string> iVINSFlagIsthereverticalinsulationValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
