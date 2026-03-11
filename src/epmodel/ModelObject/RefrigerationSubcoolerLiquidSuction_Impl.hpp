/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSUBCOOLERLIQUIDSUCTION_IMPL_HPP
#define EPMODEL_REFRIGERATIONSUBCOOLERLIQUIDSUCTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationSubcoolerLiquidSuction_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~RefrigerationSubcoolerLiquidSuction_Impl() override = default;

      boost::optional<double> liquidSuctionDesignSubcoolingTemperatureDifference() const;
      boost::optional<double> designLiquidInletTemperature() const;
      boost::optional<double> designVaporInletTemperature() const;

      bool setLiquidSuctionDesignSubcoolingTemperatureDifference(boost::optional<double> liquidSuctionDesignSubcoolingTemperatureDifference);
      void resetLiquidSuctionDesignSubcoolingTemperatureDifference();

      bool setDesignLiquidInletTemperature(boost::optional<double> designLiquidInletTemperature);
      void resetDesignLiquidInletTemperature();

      bool setDesignVaporInletTemperature(boost::optional<double> designVaporInletTemperature);
      void resetDesignVaporInletTemperature();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
