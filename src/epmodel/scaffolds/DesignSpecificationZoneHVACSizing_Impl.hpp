/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONZONEHVACSIZING_IMPL_HPP
#define EPMODEL_DESIGNSPECIFICATIONZONEHVACSIZING_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API DesignSpecificationZoneHVACSizing_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DesignSpecificationZoneHVACSizing_Impl() override = default;

      std::string coolingSupplyAirFlowRateMethod() const;
      bool isCoolingSupplyAirFlowRateMethodDefaulted() const;
      bool setCoolingSupplyAirFlowRateMethod(const std::string& coolingSupplyAirFlowRateMethod);
      void resetCoolingSupplyAirFlowRateMethod();

      boost::optional<double> coolingSupplyAirFlowRate() const;
      bool isCoolingSupplyAirFlowRateAutosized() const;
      bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
      void resetCoolingSupplyAirFlowRate();
      void autosizeCoolingSupplyAirFlowRate();

      boost::optional<double> coolingSupplyAirFlowRatePerFloorArea() const;
      bool setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea);
      void resetCoolingSupplyAirFlowRatePerFloorArea();

      boost::optional<double> coolingFractionofAutosizedCoolingSupplyAirFlowRate() const;
      bool setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate);
      void resetCoolingFractionofAutosizedCoolingSupplyAirFlowRate();

      boost::optional<double> coolingSupplyAirFlowRatePerUnitCoolingCapacity() const;
      bool setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity);
      void resetCoolingSupplyAirFlowRatePerUnitCoolingCapacity();

      std::string noLoadSupplyAirFlowRateMethod() const;
      bool isNoLoadSupplyAirFlowRateMethodDefaulted() const;
      bool setNoLoadSupplyAirFlowRateMethod(const std::string& noLoadSupplyAirFlowRateMethod);
      void resetNoLoadSupplyAirFlowRateMethod();

      boost::optional<double> noLoadSupplyAirFlowRate() const;
      bool isNoLoadSupplyAirFlowRateAutosized() const;
      bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
      void resetNoLoadSupplyAirFlowRate();
      void autosizeNoLoadSupplyAirFlowRate();

      boost::optional<double> noLoadSupplyAirFlowRatePerFloorArea() const;
      bool setNoLoadSupplyAirFlowRatePerFloorArea(double noLoadSupplyAirFlowRatePerFloorArea);
      void resetNoLoadSupplyAirFlowRatePerFloorArea();

      boost::optional<double> noLoadFractionofCoolingSupplyAirFlowRate() const;
      bool setNoLoadFractionofCoolingSupplyAirFlowRate(double noLoadFractionofCoolingSupplyAirFlowRate);
      void resetNoLoadFractionofCoolingSupplyAirFlowRate();

      boost::optional<double> noLoadFractionofHeatingSupplyAirFlowRate() const;
      bool setNoLoadFractionofHeatingSupplyAirFlowRate(double noLoadFractionofHeatingSupplyAirFlowRate);
      void resetNoLoadFractionofHeatingSupplyAirFlowRate();

      std::string heatingSupplyAirFlowRateMethod() const;
      bool isHeatingSupplyAirFlowRateMethodDefaulted() const;
      bool setHeatingSupplyAirFlowRateMethod(const std::string& heatingSupplyAirFlowRateMethod);
      void resetHeatingSupplyAirFlowRateMethod();

      boost::optional<double> heatingSupplyAirFlowRate() const;
      bool isHeatingSupplyAirFlowRateAutosized() const;
      bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
      void resetHeatingSupplyAirFlowRate();
      void autosizeHeatingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRatePerFloorArea() const;
      bool setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea);
      void resetHeatingSupplyAirFlowRatePerFloorArea();

      boost::optional<double> heatingFractionofHeatingSupplyAirFlowRate() const;
      bool setHeatingFractionofHeatingSupplyAirFlowRate(double heatingFractionofHeatingSupplyAirFlowRate);
      void resetHeatingFractionofHeatingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRatePerUnitHeatingCapacity() const;
      bool setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity);
      void resetHeatingSupplyAirFlowRatePerUnitHeatingCapacity();

      std::string coolingDesignCapacityMethod() const;
      bool isCoolingDesignCapacityMethodDefaulted() const;
      bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);
      void resetCoolingDesignCapacityMethod();

      boost::optional<double> coolingDesignCapacity() const;
      bool isCoolingDesignCapacityAutosized() const;
      bool setCoolingDesignCapacity(double coolingDesignCapacity);
      void resetCoolingDesignCapacity();
      void autosizeCoolingDesignCapacity();

      boost::optional<double> coolingDesignCapacityPerFloorArea() const;
      bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);
      void resetCoolingDesignCapacityPerFloorArea();

      boost::optional<double> fractionofAutosizedCoolingDesignCapacity() const;
      bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);
      void resetFractionofAutosizedCoolingDesignCapacity();

      std::string heatingDesignCapacityMethod() const;
      bool isHeatingDesignCapacityMethodDefaulted() const;
      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);
      void resetHeatingDesignCapacityMethod();

      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void resetHeatingDesignCapacity();
      void autosizeHeatingDesignCapacity();

      boost::optional<double> heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);
      void resetHeatingDesignCapacityPerFloorArea();

      boost::optional<double> fractionofAutosizedHeatingDesignCapacity() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);
      void resetFractionofAutosizedHeatingDesignCapacity();

      std::vector<std::string> coolingSupplyAirFlowRateMethodValues() const;
      std::vector<std::string> noLoadSupplyAirFlowRateMethodValues() const;
      std::vector<std::string> heatingSupplyAirFlowRateMethodValues() const;
      std::vector<std::string> coolingDesignCapacityMethodValues() const;
      std::vector<std::string> heatingDesignCapacityMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
