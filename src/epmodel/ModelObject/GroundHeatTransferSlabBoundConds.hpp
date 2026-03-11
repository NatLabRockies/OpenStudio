/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABBOUNDCONDS_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABBOUNDCONDS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferSlabBoundConds_Impl;
}

class EPMODEL_API GroundHeatTransferSlabBoundConds : public ModelObject
{
 public:
  explicit GroundHeatTransferSlabBoundConds(const Model& model);

  virtual ~GroundHeatTransferSlabBoundConds() override = default;
  GroundHeatTransferSlabBoundConds(const GroundHeatTransferSlabBoundConds& other) = default;
  GroundHeatTransferSlabBoundConds(GroundHeatTransferSlabBoundConds&& other) = default;
  GroundHeatTransferSlabBoundConds& operator=(const GroundHeatTransferSlabBoundConds&) = default;
  GroundHeatTransferSlabBoundConds& operator=(GroundHeatTransferSlabBoundConds&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:BoundConds fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  bool eVTRIssurfaceevapotranspirationmodeled() const;
  bool fIXBCIsthelowerboundaryatafixedtemperature() const;
  boost::optional<double> tDEEPin() const;
  bool uSRHflagIsthegroundsurfacehspecifiedbytheuser() const;
  boost::optional<double> uSERHUserspecifiedgroundsurfaceheattransfercoefficient() const;

  bool setEVTRIssurfaceevapotranspirationmodeled(bool eVTRIssurfaceevapotranspirationmodeled);
  bool setFIXBCIsthelowerboundaryatafixedtemperature(bool fIXBCIsthelowerboundaryatafixedtemperature);
  bool setTDEEPin(double tDEEPin);
  bool setUSRHflagIsthegroundsurfacehspecifiedbytheuser(bool uSRHflagIsthegroundsurfacehspecifiedbytheuser);
  bool setUSERHUserspecifiedgroundsurfaceheattransfercoefficient(double uSERHUserspecifiedgroundsurfaceheattransfercoefficient);

  void resetTDEEPin();
  void resetUSERHUserspecifiedgroundsurfaceheattransfercoefficient();

 protected:
  using ImplType = detail::GroundHeatTransferSlabBoundConds_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferSlabBoundConds(std::shared_ptr<detail::GroundHeatTransferSlabBoundConds_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
