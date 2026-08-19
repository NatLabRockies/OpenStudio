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

  /** \brief RefrigerationCondenserCascade.
   *
   * \par EnergyPlus object
   * \epobject{group-refrigeration.html#refrigerationcondensercascade,Refrigeration:Condenser:Cascade}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationCondenserCascade</code>. The rated condenser, control, and refrigerant-inventory fields are exposed. Model's broader refrigeration relationship helpers are not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
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

    double ratedCondensingTemperature() const;
    bool setRatedCondensingTemperature(double ratedCondensingTemperature);

    double ratedApproachTemperatureDifference() const;
    bool isRatedApproachTemperatureDifferenceDefaulted() const;
    bool setRatedApproachTemperatureDifference(double ratedApproachTemperatureDifference);
    void resetRatedApproachTemperatureDifference();

    double ratedEffectiveTotalHeatRejectionRate() const;
    bool setRatedEffectiveTotalHeatRejectionRate(double ratedEffectiveTotalHeatRejectionRate);

    std::string condensingTemperatureControlType() const;
    bool isCondensingTemperatureControlTypeDefaulted() const;
    bool setCondensingTemperatureControlType(const std::string& condensingTemperatureControlType);
    void resetCondensingTemperatureControlType();

    boost::optional<double> condenserRefrigerantOperatingChargeInventory() const;
    bool setCondenserRefrigerantOperatingChargeInventory(double condenserRefrigerantOperatingChargeInventory);
    void resetCondenserRefrigerantOperatingChargeInventory();

    boost::optional<double> condensateReceiverRefrigerantInventory() const;
    bool setCondensateReceiverRefrigerantInventory(double condensateReceiverRefrigerantInventory);
    void resetCondensateReceiverRefrigerantInventory();

    boost::optional<double> condensatePipingRefrigerantInventory() const;
    bool setCondensatePipingRefrigerantInventory(double condensatePipingRefrigerantInventory);
    void resetCondensatePipingRefrigerantInventory();

   protected:
    using ImplType = detail::RefrigerationCondenserCascade_Impl;

    explicit RefrigerationCondenserCascade(std::shared_ptr<detail::RefrigerationCondenserCascade_Impl> impl);

    friend class detail::RefrigerationCondenserCascade_Impl;
    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

   private:
    REGISTER_LOGGER("openstudio.epmodel.RefrigerationCondenserCascade");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_REFRIGERATIONCONDENSERCASCADE_HPP
