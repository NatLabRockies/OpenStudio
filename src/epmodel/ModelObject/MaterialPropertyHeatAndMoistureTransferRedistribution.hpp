/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERREDISTRIBUTION_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERREDISTRIBUTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyHeatAndMoistureTransferRedistribution_Impl;
}

/** MaterialPropertyHeatAndMoistureTransferRedistribution is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:HeatAndMoistureTransfer:Redistribution'. */
class EPMODEL_API MaterialPropertyHeatAndMoistureTransferRedistribution : public ModelObject
{
 public:
  explicit MaterialPropertyHeatAndMoistureTransferRedistribution(const Model& model);

  virtual ~MaterialPropertyHeatAndMoistureTransferRedistribution() override = default;
  MaterialPropertyHeatAndMoistureTransferRedistribution(const MaterialPropertyHeatAndMoistureTransferRedistribution& other) = default;
  MaterialPropertyHeatAndMoistureTransferRedistribution(MaterialPropertyHeatAndMoistureTransferRedistribution&& other) = default;
  MaterialPropertyHeatAndMoistureTransferRedistribution& operator=(const MaterialPropertyHeatAndMoistureTransferRedistribution&) = default;
  MaterialPropertyHeatAndMoistureTransferRedistribution& operator=(MaterialPropertyHeatAndMoistureTransferRedistribution&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart exists; use IDD-derived scalar accessor naming.
  // - Field Mapping: numberofRedistributionpoints maps to EnergyPlus field Number of Redistribution points.
  // - TODO(parity): Add non-scalar extensible redistribution pair APIs in a dedicated parity pass.
  int numberofRedistributionpoints() const;
  bool setNumberofRedistributionpoints(int numberofRedistributionpoints);

 protected:
  using ImplType = detail::MaterialPropertyHeatAndMoistureTransferRedistribution_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyHeatAndMoistureTransferRedistribution(
    std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferRedistribution_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
