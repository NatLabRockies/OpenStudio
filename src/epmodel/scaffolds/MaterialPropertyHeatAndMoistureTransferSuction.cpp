/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/MaterialPropertyHeatAndMoistureTransferSuction.hpp"
#include "scaffolds/MaterialPropertyHeatAndMoistureTransferSuction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_HeatAndMoistureTransfer_Suction_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MaterialPropertyHeatAndMoistureTransferSuction::MaterialPropertyHeatAndMoistureTransferSuction(const Model& model)
    : ModelObject(MaterialPropertyHeatAndMoistureTransferSuction::iddObjectType(), model) {}

  MaterialPropertyHeatAndMoistureTransferSuction::MaterialPropertyHeatAndMoistureTransferSuction(
    std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferSuction_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType MaterialPropertyHeatAndMoistureTransferSuction::iddObjectType() {
    return IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Suction;
  }

  int MaterialPropertyHeatAndMoistureTransferSuction::numberofSuctionpoints() const {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSuction_Impl>()->numberofSuctionpoints();
  }

  bool MaterialPropertyHeatAndMoistureTransferSuction::setNumberofSuctionpoints(int numberofSuctionpoints) {
    return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSuction_Impl>()->setNumberofSuctionpoints(numberofSuctionpoints);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int MaterialPropertyHeatAndMoistureTransferSuction_Impl::numberofSuctionpoints() const {
      const auto value = getInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_SuctionFields::NumberofSuctionpoints, true);
      OS_ASSERT(value);
      return *value;
    }

    bool MaterialPropertyHeatAndMoistureTransferSuction_Impl::setNumberofSuctionpoints(int numberofSuctionpoints) {
      return setInt(openstudio::MaterialProperty_HeatAndMoistureTransfer_SuctionFields::NumberofSuctionpoints, numberofSuctionpoints);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
