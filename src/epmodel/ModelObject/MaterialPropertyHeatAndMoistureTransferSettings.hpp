/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSETTINGS_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSETTINGS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyHeatAndMoistureTransferSettings_Impl;
}

/** MaterialPropertyHeatAndMoistureTransferSettings is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:HeatAndMoistureTransfer:Settings'. */
class EPMODEL_API MaterialPropertyHeatAndMoistureTransferSettings : public ModelObject
{
 public:
  explicit MaterialPropertyHeatAndMoistureTransferSettings(const Model& model);

  virtual ~MaterialPropertyHeatAndMoistureTransferSettings() override = default;
  MaterialPropertyHeatAndMoistureTransferSettings(const MaterialPropertyHeatAndMoistureTransferSettings& other) = default;
  MaterialPropertyHeatAndMoistureTransferSettings(MaterialPropertyHeatAndMoistureTransferSettings&& other) = default;
  MaterialPropertyHeatAndMoistureTransferSettings& operator=(const MaterialPropertyHeatAndMoistureTransferSettings&) = default;
  MaterialPropertyHeatAndMoistureTransferSettings& operator=(MaterialPropertyHeatAndMoistureTransferSettings&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: No openstudio::model counterpart exists; use IDD-derived scalar accessor naming.
  // - Field Mapping: porosity and initialWaterContentRatio map directly to EnergyPlus scalar fields
  //   Porosity and Initial Water Content Ratio.
  // - Field Mapping: Material Name is an object-list relationship field and is intentionally excluded.
  // - TODO(parity): Add relationship API for Material Name if/when non-scalar linkage is scaffolded.
  double porosity() const;
  bool setPorosity(double porosity);

  double initialWaterContentRatio() const;
  bool isInitialWaterContentRatioDefaulted() const;
  bool setInitialWaterContentRatio(double initialWaterContentRatio);
  void resetInitialWaterContentRatio();

 protected:
  using ImplType = detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyHeatAndMoistureTransferSettings(std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
