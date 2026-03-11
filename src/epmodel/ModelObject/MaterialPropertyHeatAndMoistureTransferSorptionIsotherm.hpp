/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSORPTIONISOTHERM_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSORPTIONISOTHERM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl;
}

/** MaterialPropertyHeatAndMoistureTransferSorptionIsotherm is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:HeatAndMoistureTransfer:SorptionIsotherm'. */
class EPMODEL_API MaterialPropertyHeatAndMoistureTransferSorptionIsotherm : public ModelObject
{
 public:
  explicit MaterialPropertyHeatAndMoistureTransferSorptionIsotherm(const Model& model);

  virtual ~MaterialPropertyHeatAndMoistureTransferSorptionIsotherm() override = default;
  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm(const MaterialPropertyHeatAndMoistureTransferSorptionIsotherm& other) = default;
  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm(MaterialPropertyHeatAndMoistureTransferSorptionIsotherm&& other) = default;
  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm& operator=(const MaterialPropertyHeatAndMoistureTransferSorptionIsotherm&) = default;
  MaterialPropertyHeatAndMoistureTransferSorptionIsotherm& operator=(MaterialPropertyHeatAndMoistureTransferSorptionIsotherm&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart exists; use IDD-derived scalar accessor naming.
  // - Field Mapping: numberofIsothermCoordinates maps to EnergyPlus field Number of Isotherm Coordinates.
  // - Field Mapping: Material Name is an object-list relationship field and is intentionally excluded.
  // - Field Mapping: Relative Humidity Fraction / Moisture Content extensible pairs are intentionally excluded (non-scalar).
  // - TODO(parity): Add extensible sorption isotherm pair APIs in a dedicated non-scalar parity pass.
  int numberofIsothermCoordinates() const;
  bool setNumberofIsothermCoordinates(int numberofIsothermCoordinates);

 protected:
  using ImplType = detail::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyHeatAndMoistureTransferSorptionIsotherm(
    std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferSorptionIsotherm_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
