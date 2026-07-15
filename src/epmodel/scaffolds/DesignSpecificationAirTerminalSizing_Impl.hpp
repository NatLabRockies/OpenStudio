/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONAIRTERMINALSIZING_IMPL_HPP
#define EPMODEL_DESIGNSPECIFICATIONAIRTERMINALSIZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API DesignSpecificationAirTerminalSizing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DesignSpecificationAirTerminalSizing_Impl() override = default;

      double fractionofDesignCoolingLoad() const;
      bool isFractionofDesignCoolingLoadDefaulted() const;
      bool setFractionofDesignCoolingLoad(double fractionofDesignCoolingLoad);
      void resetFractionofDesignCoolingLoad();

      double coolingDesignSupplyAirTemperatureDifferenceRatio() const;
      bool isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const;
      bool setCoolingDesignSupplyAirTemperatureDifferenceRatio(double coolingDesignSupplyAirTemperatureDifferenceRatio);
      void resetCoolingDesignSupplyAirTemperatureDifferenceRatio();

      double fractionofDesignHeatingLoad() const;
      bool isFractionofDesignHeatingLoadDefaulted() const;
      bool setFractionofDesignHeatingLoad(double fractionofDesignHeatingLoad);
      void resetFractionofDesignHeatingLoad();

      double heatingDesignSupplyAirTemperatureDifferenceRatio() const;
      bool isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const;
      bool setHeatingDesignSupplyAirTemperatureDifferenceRatio(double heatingDesignSupplyAirTemperatureDifferenceRatio);
      void resetHeatingDesignSupplyAirTemperatureDifferenceRatio();

      double fractionofMinimumOutdoorAirFlow() const;
      bool isFractionofMinimumOutdoorAirFlowDefaulted() const;
      bool setFractionofMinimumOutdoorAirFlow(double fractionofMinimumOutdoorAirFlow);
      void resetFractionofMinimumOutdoorAirFlow();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
