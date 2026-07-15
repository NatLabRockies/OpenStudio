/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGGAS_IMPL_HPP
#define EPMODEL_COILHEATINGGAS_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  class Schedule;
  class Curve;
  namespace detail {

    class EPMODEL_API CoilHeatingGas_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilHeatingGas_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;

      bool addToNode(Node& node) override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<Curve> partLoadFractionCorrelationCurve() const;
      bool setPartLoadFractionCorrelationCurve(const Curve& curve);
      void resetPartLoadFractionCorrelationCurve();

      std::string fuelType() const;
      bool setFuelType(const std::string& fuelType);
      void resetFuelType();

      double gasBurnerEfficiency() const;
      bool setGasBurnerEfficiency(double value);

      double parasiticElectricLoad() const;
      bool setParasiticElectricLoad(double value);

      double onCycleParasiticElectricLoad() const;
      bool setOnCycleParasiticElectricLoad(double value);

      double parasiticGasLoad() const;
      bool setParasiticGasLoad(double value);

      double offCycleParasiticGasLoad() const;
      bool setOffCycleParasiticGasLoad(double value);

      boost::optional<double> nominalCapacity() const;
      bool isNominalCapacityAutosized() const;
      bool setNominalCapacity(double nominalCapacity);
      void resetNominalCapacity();
      void autosizeNominalCapacity();

      boost::optional<double> autosizedNominalCapacity() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
