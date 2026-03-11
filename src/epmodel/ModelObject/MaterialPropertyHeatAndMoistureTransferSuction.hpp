/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSUCTION_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSUCTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyHeatAndMoistureTransferSuction_Impl;
}

/** MaterialPropertyHeatAndMoistureTransferSuction is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:HeatAndMoistureTransfer:Suction'. */
class EPMODEL_API MaterialPropertyHeatAndMoistureTransferSuction : public ModelObject
{
 public:
  explicit MaterialPropertyHeatAndMoistureTransferSuction(const Model& model);

  virtual ~MaterialPropertyHeatAndMoistureTransferSuction() override = default;
  MaterialPropertyHeatAndMoistureTransferSuction(const MaterialPropertyHeatAndMoistureTransferSuction& other) = default;
  MaterialPropertyHeatAndMoistureTransferSuction(MaterialPropertyHeatAndMoistureTransferSuction&& other) = default;
  MaterialPropertyHeatAndMoistureTransferSuction& operator=(const MaterialPropertyHeatAndMoistureTransferSuction&) = default;
  MaterialPropertyHeatAndMoistureTransferSuction& operator=(MaterialPropertyHeatAndMoistureTransferSuction&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart exists; use IDD-derived scalar accessor naming.
  // - Field Mapping: numberofSuctionpoints maps to EnergyPlus field Number of Suction points.
  // - Field Mapping: Material Name is an object-list relationship field and is intentionally excluded.
  // - TODO(parity): Add non-scalar extensible suction pair APIs in a dedicated parity pass.
  int numberofSuctionpoints() const;
  bool setNumberofSuctionpoints(int numberofSuctionpoints);

 protected:
  using ImplType = detail::MaterialPropertyHeatAndMoistureTransferSuction_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyHeatAndMoistureTransferSuction(std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferSuction_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
