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

  /** \brief RefrigerationSubcoolerLiquidSuction.
   *
   * \par EnergyPlus object
   * \epobject{group-refrigeration.html#refrigerationsubcooler,Refrigeration:Subcooler}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RefrigerationSubcoolerLiquidSuction</code>. This typed wrapper uses <code>Refrigeration:Subcooler</code> with <code>Subcooler Type</code> fixed to <code>LiquidSuction</code>. The Model relationship to a refrigeration system is not available.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
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
