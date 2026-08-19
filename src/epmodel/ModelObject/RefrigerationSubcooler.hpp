/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSUBCOOLER_HPP
#define EPMODEL_REFRIGERATIONSUBCOOLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RefrigerationSubcooler_Impl;
  }

  /** \brief RefrigerationSubcooler.
   *
   * \par EnergyPlus object
   * \epobject{group-refrigeration.html#refrigerationsubcooler,Refrigeration:Subcooler}.
   *
   * \par OpenStudio Model API
   * There is no corresponding <code>openstudio::model::RefrigerationSubcooler</code> base class. This EPModel base represents the shared EnergyPlus object fields; typed subclasses select the subcooler type.
   *
   * \par Known limitations
   * There is no corresponding <code>openstudio::model::RefrigerationSubcooler</code> base class. This EPModel base represents the shared EnergyPlus object fields; typed subclasses select the subcooler type.
   */
  class EPMODEL_API RefrigerationSubcooler : public ModelObject
  {
   public:
    explicit RefrigerationSubcooler(const Model& model);

    virtual ~RefrigerationSubcooler() override = default;
    RefrigerationSubcooler(const RefrigerationSubcooler& other) = default;
    RefrigerationSubcooler(RefrigerationSubcooler&& other) = default;
    RefrigerationSubcooler& operator=(const RefrigerationSubcooler&) = default;
    RefrigerationSubcooler& operator=(RefrigerationSubcooler&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> subcoolerTypeValues();

    std::string subcoolerType() const;
    bool setSubcoolerType(const std::string& subcoolerType);

    boost::optional<double> liquidSuctionDesignSubcoolingTemperatureDifference() const;
    bool setLiquidSuctionDesignSubcoolingTemperatureDifference(double value);
    void resetLiquidSuctionDesignSubcoolingTemperatureDifference();

    boost::optional<double> designLiquidInletTemperature() const;
    bool setDesignLiquidInletTemperature(double value);
    void resetDesignLiquidInletTemperature();

    boost::optional<double> designVaporInletTemperature() const;
    bool setDesignVaporInletTemperature(double value);
    void resetDesignVaporInletTemperature();

    boost::optional<double> outletControlTemperature() const;
    bool setOutletControlTemperature(double value);
    void resetOutletControlTemperature();

   protected:
    using ImplType = detail::RefrigerationSubcooler_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RefrigerationSubcooler(std::shared_ptr<detail::RefrigerationSubcooler_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
