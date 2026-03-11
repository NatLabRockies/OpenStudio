/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMATLPROPS_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMATLPROPS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferSlabMatlProps_Impl;
}

class EPMODEL_API GroundHeatTransferSlabMatlProps : public ModelObject
{
 public:
  explicit GroundHeatTransferSlabMatlProps(const Model& model);

  virtual ~GroundHeatTransferSlabMatlProps() override = default;
  GroundHeatTransferSlabMatlProps(const GroundHeatTransferSlabMatlProps& other) = default;
  GroundHeatTransferSlabMatlProps(GroundHeatTransferSlabMatlProps&& other) = default;
  GroundHeatTransferSlabMatlProps& operator=(const GroundHeatTransferSlabMatlProps&) = default;
  GroundHeatTransferSlabMatlProps& operator=(GroundHeatTransferSlabMatlProps&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:MatlProps N1-N6 fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  double rHOSlabMaterialdensity() const;
  double rHOSoilDensity() const;
  double cPSlabCP() const;
  double cPSoilCP() const;
  double tCONSlabk() const;
  double tCONSoilk() const;

  bool isRHOSlabMaterialdensityDefaulted() const;
  bool isRHOSoilDensityDefaulted() const;
  bool isCPSlabCPDefaulted() const;
  bool isCPSoilCPDefaulted() const;
  bool isTCONSlabkDefaulted() const;
  bool isTCONSoilkDefaulted() const;

  bool setRHOSlabMaterialdensity(double rHOSlabMaterialdensity);
  bool setRHOSoilDensity(double rHOSoilDensity);
  bool setCPSlabCP(double cPSlabCP);
  bool setCPSoilCP(double cPSoilCP);
  bool setTCONSlabk(double tCONSlabk);
  bool setTCONSoilk(double tCONSoilk);

  void resetRHOSlabMaterialdensity();
  void resetRHOSoilDensity();
  void resetCPSlabCP();
  void resetCPSoilCP();
  void resetTCONSlabk();
  void resetTCONSoilk();

 protected:
  using ImplType = detail::GroundHeatTransferSlabMatlProps_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferSlabMatlProps(std::shared_ptr<detail::GroundHeatTransferSlabMatlProps_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
