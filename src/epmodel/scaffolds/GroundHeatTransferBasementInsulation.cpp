/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementInsulation.hpp"
#include "GroundHeatTransferBasementInsulation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_Insulation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementInsulation::GroundHeatTransferBasementInsulation(const Model& model)
    : ModelObject(GroundHeatTransferBasementInsulation::iddObjectType(), model) {}

  GroundHeatTransferBasementInsulation::GroundHeatTransferBasementInsulation(std::shared_ptr<detail::GroundHeatTransferBasementInsulation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementInsulation::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_Insulation;
  }

  boost::optional<double> GroundHeatTransferBasementInsulation::rEXTRValueofanyexteriorinsulation() const {
    return getImpl<detail::GroundHeatTransferBasementInsulation_Impl>()->rEXTRValueofanyexteriorinsulation();
  }

  bool GroundHeatTransferBasementInsulation::setREXTRValueofanyexteriorinsulation(double rEXTRValueofanyexteriorinsulation) {
    return getImpl<detail::GroundHeatTransferBasementInsulation_Impl>()->setREXTRValueofanyexteriorinsulation(rEXTRValueofanyexteriorinsulation);
  }

  void GroundHeatTransferBasementInsulation::resetREXTRValueofanyexteriorinsulation() {
    getImpl<detail::GroundHeatTransferBasementInsulation_Impl>()->resetREXTRValueofanyexteriorinsulation();
  }

  bool GroundHeatTransferBasementInsulation::iNSFULLFlagIsthewallfullyinsulated() const {
    return getImpl<detail::GroundHeatTransferBasementInsulation_Impl>()->iNSFULLFlagIsthewallfullyinsulated();
  }

  bool GroundHeatTransferBasementInsulation::setINSFULLFlagIsthewallfullyinsulated(bool iNSFULLFlagIsthewallfullyinsulated) {
    return getImpl<detail::GroundHeatTransferBasementInsulation_Impl>()->setINSFULLFlagIsthewallfullyinsulated(iNSFULLFlagIsthewallfullyinsulated);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> GroundHeatTransferBasementInsulation_Impl::rEXTRValueofanyexteriorinsulation() const {
      return getDouble(openstudio::GroundHeatTransfer_Basement_InsulationFields::REXT_RValueofanyexteriorinsulation, true);
    }

    bool GroundHeatTransferBasementInsulation_Impl::setREXTRValueofanyexteriorinsulation(double rEXTRValueofanyexteriorinsulation) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_InsulationFields::REXT_RValueofanyexteriorinsulation,
                       rEXTRValueofanyexteriorinsulation);
    }

    void GroundHeatTransferBasementInsulation_Impl::resetREXTRValueofanyexteriorinsulation() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_InsulationFields::REXT_RValueofanyexteriorinsulation, ""));
    }

    bool GroundHeatTransferBasementInsulation_Impl::iNSFULLFlagIsthewallfullyinsulated() const {
      const auto value = getString(openstudio::GroundHeatTransfer_Basement_InsulationFields::INSFULL_Flag_Isthewallfullyinsulated, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "TRUE");
    }

    bool GroundHeatTransferBasementInsulation_Impl::setINSFULLFlagIsthewallfullyinsulated(bool iNSFULLFlagIsthewallfullyinsulated) {
      const bool result = setString(openstudio::GroundHeatTransfer_Basement_InsulationFields::INSFULL_Flag_Isthewallfullyinsulated,
                                    iNSFULLFlagIsthewallfullyinsulated ? "TRUE" : "FALSE");
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
