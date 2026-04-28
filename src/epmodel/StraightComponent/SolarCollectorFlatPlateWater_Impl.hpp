/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORFLATPLATEWATER_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORFLATPLATEWATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class SolarCollectorFlatPlateWater;
  class SolarCollectorPerformanceFlatPlate;

  namespace detail {

    class EPMODEL_API SolarCollectorFlatPlateWater_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~SolarCollectorFlatPlateWater_Impl() override = default;

      std::vector<ModelObject> children() const override;
      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;
      std::vector<IdfObject> remove() override;

      SolarCollectorPerformanceFlatPlate solarCollectorPerformance() const;
      bool setSolarCollectorPerformance(const SolarCollectorPerformanceFlatPlate& solarCollectorPerformanceFlatPlate);
      void resetSolarCollectorPerformance();

      /** @name Maximum flow rate */
      //@{
      boost::optional<double> maximumFlowRate() const;
      bool setMaximumFlowRate(double maximumFlowRate);
      void resetMaximumFlowRate();
      //@}

     private:
      REGISTER_LOGGER("openstudio.epmodel.SolarCollectorFlatPlateWater");

      bool setSolarCollectorPerformanceNoClone(const SolarCollectorPerformanceFlatPlate& solarCollectorPerformanceFlatPlate);

      friend class openstudio::epmodel::SolarCollectorFlatPlateWater;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
