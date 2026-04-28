/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/MaterialPropertyHeatAndMoistureTransferRedistribution.hpp"
#include "scaffolds/MaterialPropertyHeatAndMoistureTransferRedistribution_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_HeatAndMoistureTransfer_Redistribution_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyHeatAndMoistureTransferRedistribution::MaterialPropertyHeatAndMoistureTransferRedistribution(const Model& model)
    : ModelObject(MaterialPropertyHeatAndMoistureTransferRedistribution::iddObjectType(), model) {}

  MaterialPropertyHeatAndMoistureTransferRedistribution::MaterialPropertyHeatAndMoistureTransferRedistribution(
    std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferRedistribution_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyHeatAndMoistureTransferRedistribution::iddObjectType() {
    return IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Redistribution;
  }

  ////////////////////////////////////////////////////////////////////////
  // Scalar accessors for Number of Redistribution points
  ////////////////////////////////////////////////////////////////////////
  int MaterialPropertyHeatAndMoistureTransferRedistribution::numberofRedistributionpoints() const {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferRedistribution_Impl>()->numberofRedistributionpoints();
  }

  bool MaterialPropertyHeatAndMoistureTransferRedistribution::setNumberofRedistributionpoints(int numberofRedistributionpoints) {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferRedistribution_Impl>()->setNumberofRedistributionpoints(
      numberofRedistributionpoints);
  }

  namespace detail {

    int MaterialPropertyHeatAndMoistureTransferRedistribution_Impl::numberofRedistributionpoints() const {
      const auto value = getInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_RedistributionFields::NumberofRedistributionpoints, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyHeatAndMoistureTransferRedistribution_Impl::setNumberofRedistributionpoints(int numberofRedistributionpoints) {
      return setInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_RedistributionFields::NumberofRedistributionpoints,
                    numberofRedistributionpoints);
    }

  }  // namespace detail

}  // namespace epmodel

}  // namespace openstudio
