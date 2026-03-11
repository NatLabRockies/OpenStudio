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
    boost::optional<double> designLiquidInletTemperature() const;
    boost::optional<double> designVaporInletTemperature() const;
    boost::optional<double> outletControlTemperature() const;

    bool setLiquidSuctionDesignSubcoolingTemperatureDifference(double value);
    void resetLiquidSuctionDesignSubcoolingTemperatureDifference();

    bool setDesignLiquidInletTemperature(double value);
    void resetDesignLiquidInletTemperature();

    bool setDesignVaporInletTemperature(double value);
    void resetDesignVaporInletTemperature();

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
