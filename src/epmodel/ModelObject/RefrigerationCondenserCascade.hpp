/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONCONDENSERCASCADE_HPP
#define EPMODEL_REFRIGERATIONCONDENSERCASCADE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationCondenserCascade_Impl;
  }

  class EPMODEL_API RefrigerationCondenserCascade : public ModelObject
  {
   public:
    explicit RefrigerationCondenserCascade(const Model& model);

    virtual ~RefrigerationCondenserCascade() override = default;
    RefrigerationCondenserCascade(const RefrigerationCondenserCascade& other) = default;
    RefrigerationCondenserCascade(RefrigerationCondenserCascade&& other) = default;
    RefrigerationCondenserCascade& operator=(const RefrigerationCondenserCascade&) = default;
    RefrigerationCondenserCascade& operator=(RefrigerationCondenserCascade&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condensingTemperatureControlTypeValues();

    // Schema Alignment Notes:
    // - API: preserve the openstudio::model RefrigerationCondenserCascade scalar accessor naming/signatures while translating to the
    //   EnergyPlus Refrigeration:Condenser:Cascade object.
    // - Field Mapping: ForwardTranslateRefrigerationCondenserCascade.cpp inserts these scalars into Refrigeration_Condenser_CascadeFields (rated temps,
    //   control type, and optional refrigerant inventories).
    // - TODO(parity): Expand beyond simple scalars once relationship-like fields are handled by richer epmodel types.
    double ratedCondensingTemperature() const;
    double ratedApproachTemperatureDifference() const;
    bool isRatedApproachTemperatureDifferenceDefaulted() const;
    double ratedEffectiveTotalHeatRejectionRate() const;
    std::string condensingTemperatureControlType() const;
    bool isCondensingTemperatureControlTypeDefaulted() const;
    boost::optional<double> condenserRefrigerantOperatingChargeInventory() const;
    boost::optional<double> condensateReceiverRefrigerantInventory() const;
    boost::optional<double> condensatePipingRefrigerantInventory() const;

    bool setRatedCondensingTemperature(double ratedCondensingTemperature);
    bool setRatedApproachTemperatureDifference(double ratedApproachTemperatureDifference);
    void resetRatedApproachTemperatureDifference();
    bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);
    bool setCondensingTemperatureControlType(const std::string& condensingTemperatureControlType);
    void resetCondensingTemperatureControlType();
    bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
    void resetCondenserRefrigerantOperatingChargeInventory();
    bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
    void resetCondensateReceiverRefrigerantInventory();
    bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
    void resetCondensatePipingRefrigerantInventory();

   protected:
    using ImplType = detail::RefrigerationCondenserCascade_Impl;

    explicit RefrigerationCondenserCascade(std::shared_ptr<detail::RefrigerationCondenserCascade_Impl> impl);

    friend class detail::RefrigerationCondenserCascade_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationCondenserCascade");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERCASCADE_HPP
