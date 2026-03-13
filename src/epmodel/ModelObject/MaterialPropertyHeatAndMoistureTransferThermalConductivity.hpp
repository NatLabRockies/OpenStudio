/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERTHERMALCONDUCTIVITY_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERTHERMALCONDUCTIVITY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl;
  }

  /** MaterialPropertyHeatAndMoistureTransferThermalConductivity is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:HeatAndMoistureTransfer:ThermalConductivity'. */
  class EPMODEL_API MaterialPropertyHeatAndMoistureTransferThermalConductivity : public ModelObject
  {
   public:
    explicit MaterialPropertyHeatAndMoistureTransferThermalConductivity(const Model& model);

    virtual ~MaterialPropertyHeatAndMoistureTransferThermalConductivity() override = default;
    MaterialPropertyHeatAndMoistureTransferThermalConductivity(const MaterialPropertyHeatAndMoistureTransferThermalConductivity& other) = default;
    MaterialPropertyHeatAndMoistureTransferThermalConductivity(MaterialPropertyHeatAndMoistureTransferThermalConductivity&& other) = default;
    MaterialPropertyHeatAndMoistureTransferThermalConductivity&
      operator=(const MaterialPropertyHeatAndMoistureTransferThermalConductivity&) = default;
    MaterialPropertyHeatAndMoistureTransferThermalConductivity& operator=(MaterialPropertyHeatAndMoistureTransferThermalConductivity&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists; use IDD-derived scalar accessor naming.
    // - Field Mapping: numberofThermalCoordinates maps to EnergyPlus field Number of Thermal Coordinates.
    // - TODO(parity): Add non-scalar extensible moisture-content/thermal-conductivity pair APIs in a dedicated parity pass.
    /** @name Number of Thermal Coordinates */
    //@{
    int numberofThermalCoordinates() const;
    bool setNumberofThermalCoordinates(int numberofThermalCoordinates);
    //@}

   protected:
    using ImplType = detail::MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MaterialPropertyHeatAndMoistureTransferThermalConductivity(
      std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferThermalConductivity_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
