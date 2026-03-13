/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORFLATPLATEPHOTOVOLTAICTHERMAL_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORFLATPLATEPHOTOVOLTAICTHERMAL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SolarCollectorFlatPlatePhotovoltaicThermal_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~SolarCollectorFlatPlatePhotovoltaicThermal_Impl() override = default;

      // Schema Alignment Notes:
      // - API: The model counterpart abstracts inlet/outlet node naming, while E+ has air and water node field pairs.
      // - Field Mapping: inletPort/outletPort select the air or water node pair based on ThermalWorkingFluidType value.
      // - TODO(parity): revisit loop-specific behaviors when non-scalar APIs are added.
      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> designFlowRate() const;
      bool setDesignFlowRate(double designFlowRate);
      void resetDesignFlowRate();

      bool isDesignFlowRateAutosized() const;
      boost::optional<double> autosizedDesignFlowRate() const;
      void autosizeDesignFlowRate();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
