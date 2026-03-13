/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSUBCOOLERLIQUIDSUCTION_HPP
#define EPMODEL_REFRIGERATIONSUBCOOLERLIQUIDSUCTION_HPP

#include "EPModelAPI.hpp"
#include "RefrigerationSubcooler.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationSubcoolerLiquidSuction_Impl;
  }

  class EPMODEL_API RefrigerationSubcoolerLiquidSuction : public RefrigerationSubcooler
  {
   public:
    explicit RefrigerationSubcoolerLiquidSuction(const Model& model);

    virtual ~RefrigerationSubcoolerLiquidSuction() override = default;
    RefrigerationSubcoolerLiquidSuction(const RefrigerationSubcoolerLiquidSuction& other) = default;
    RefrigerationSubcoolerLiquidSuction(RefrigerationSubcoolerLiquidSuction&& other) = default;
    RefrigerationSubcoolerLiquidSuction& operator=(const RefrigerationSubcoolerLiquidSuction&) = default;
    RefrigerationSubcoolerLiquidSuction& operator=(RefrigerationSubcoolerLiquidSuction&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model scalar accessor names/signatures for the liquid suction subcooler.
    // - Field Mapping: Liquid suction design subcooling, liquid inlet, and vapor inlet temperature fields map directly to
    //   Refrigeration:Subcooler fields while Subcooler Type stays fixed to LiquidSuction for this typed wrapper.
    boost::optional<double> liquidSuctionDesignSubcoolingTemperatureDifference() const;
    bool setLiquidSuctionDesignSubcoolingTemperatureDifference(double liquidSuctionDesignSubcoolingTemperatureDifference);
    void resetLiquidSuctionDesignSubcoolingTemperatureDifference();

    boost::optional<double> designLiquidInletTemperature() const;
    bool setDesignLiquidInletTemperature(double designLiquidInletTemperature);
    void resetDesignLiquidInletTemperature();

    boost::optional<double> designVaporInletTemperature() const;
    bool setDesignVaporInletTemperature(double designVaporInletTemperature);
    void resetDesignVaporInletTemperature();

   protected:
    using ImplType = detail::RefrigerationSubcoolerLiquidSuction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class detail::RefrigerationSubcoolerLiquidSuction_Impl;

    explicit RefrigerationSubcoolerLiquidSuction(std::shared_ptr<detail::RefrigerationSubcoolerLiquidSuction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
