/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSUBCOOLER_IMPL_HPP
#define EPMODEL_REFRIGERATIONSUBCOOLER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationSubcooler_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationSubcooler_Impl() override = default;

      std::string subcoolerType() const;
      bool setSubcoolerType(const std::string& subcoolerType);

      boost::optional<double> liquidSuctionDesignSubcoolingTemperatureDifference() const;
      boost::optional<double> designLiquidInletTemperature() const;
      boost::optional<double> designVaporInletTemperature() const;
      boost::optional<double> outletControlTemperature() const;

      bool setLiquidSuctionDesignSubcoolingTemperatureDifference(boost::optional<double> value);
      void resetLiquidSuctionDesignSubcoolingTemperatureDifference();

      bool setDesignLiquidInletTemperature(boost::optional<double> value);
      void resetDesignLiquidInletTemperature();

      bool setDesignVaporInletTemperature(boost::optional<double> value);
      void resetDesignVaporInletTemperature();

      bool setOutletControlTemperature(boost::optional<double> value);
      void resetOutletControlTemperature();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
