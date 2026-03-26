/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BOILERSTEAM_IMPL_HPP
#define EPMODEL_BOILERSTEAM_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Node;

  namespace detail {

    class EPMODEL_API BoilerSteam_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~BoilerSteam_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      std::string fuelType() const;
      bool setFuelType(const std::string& fuelType);
      std::vector<std::string> fuelTypeValues() const;

      boost::optional<double> maximumOperatingPressure() const;
      bool setMaximumOperatingPressure(double maximumOperatingPressure);
      void resetMaximumOperatingPressure();

      boost::optional<double> theoreticalEfficiency() const;
      bool setTheoreticalEfficiency(double theoreticalEfficiency);
      void resetTheoreticalEfficiency();

      boost::optional<double> designOutletSteamTemperature() const;
      bool setDesignOutletSteamTemperature(double designOutletSteamTemperature);
      void resetDesignOutletSteamTemperature();

      boost::optional<double> nominalCapacity() const;
      bool isNominalCapacityAutosized() const;
      bool setNominalCapacity(double nominalCapacity);
      void resetNominalCapacity();
      void autosizeNominalCapacity();

      boost::optional<double> minimumPartLoadRatio() const;
      bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
      void resetMinimumPartLoadRatio();

      boost::optional<double> maximumPartLoadRatio() const;
      bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
      void resetMaximumPartLoadRatio();

      boost::optional<double> optimumPartLoadRatio() const;
      bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
      void resetOptimumPartLoadRatio();

      boost::optional<double> coefficient1ofFuelUseFunctionofPartLoadRatioCurve() const;
      bool setCoefficient1ofFuelUseFunctionofPartLoadRatioCurve(double coefficient1ofFuelUseFunctionofPartLoadRatioCurve);
      void resetCoefficient1ofFuelUseFunctionofPartLoadRatioCurve();

      boost::optional<double> coefficient2ofFuelUseFunctionofPartLoadRatioCurve() const;
      bool setCoefficient2ofFuelUseFunctionofPartLoadRatioCurve(double coefficient2ofFuelUseFunctionofPartLoadRatioCurve);
      void resetCoefficient2ofFuelUseFunctionofPartLoadRatioCurve();

      boost::optional<double> coefficient3ofFuelUseFunctionofPartLoadRatioCurve() const;
      bool setCoefficient3ofFuelUseFunctionofPartLoadRatioCurve(double coefficient3ofFuelUseFunctionofPartLoadRatioCurve);
      void resetCoefficient3ofFuelUseFunctionofPartLoadRatioCurve();

      double sizingFactor() const;
      bool isSizingFactorDefaulted() const;
      bool setSizingFactor(double sizingFactor);
      void resetSizingFactor();

      boost::optional<double> autosizedNominalCapacity() const;

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
