/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERDIFFUSION_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERDIFFUSION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class MaterialPropertyHeatAndMoistureTransferDiffusion_Impl;
  }

  /** MaterialPropertyHeatAndMoistureTransferDiffusion is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:HeatAndMoistureTransfer:Diffusion'. */
  class EPMODEL_API MaterialPropertyHeatAndMoistureTransferDiffusion : public ModelObject
  {
   public:
    explicit MaterialPropertyHeatAndMoistureTransferDiffusion(const Model& model);

    virtual ~MaterialPropertyHeatAndMoistureTransferDiffusion() override = default;
    MaterialPropertyHeatAndMoistureTransferDiffusion(const MaterialPropertyHeatAndMoistureTransferDiffusion& other) = default;
    MaterialPropertyHeatAndMoistureTransferDiffusion(MaterialPropertyHeatAndMoistureTransferDiffusion&& other) = default;
    MaterialPropertyHeatAndMoistureTransferDiffusion& operator=(const MaterialPropertyHeatAndMoistureTransferDiffusion&) = default;
    MaterialPropertyHeatAndMoistureTransferDiffusion& operator=(MaterialPropertyHeatAndMoistureTransferDiffusion&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists; use IDD-derived scalar accessor naming.
    // - Field Mapping: numberofDataPairs maps to EnergyPlus field Number of Data Pairs.
    // - TODO(parity): Add non-scalar extensible diffusion pair APIs in a dedicated parity pass.
    int numberofDataPairs() const;
    bool setNumberofDataPairs(int numberofDataPairs);

   protected:
    using ImplType = detail::MaterialPropertyHeatAndMoistureTransferDiffusion_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit MaterialPropertyHeatAndMoistureTransferDiffusion(std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferDiffusion_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
