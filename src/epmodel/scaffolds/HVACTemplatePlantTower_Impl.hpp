/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTTOWER_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTTOWER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplatePlantTower_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplatePlantTower_Impl() override = default;

      std::string towerType() const;
      bool setTowerType(const std::string& towerType);

      boost::optional<double> highSpeedNominalCapacity() const;
      bool isHighSpeedNominalCapacityDefaulted() const;
      bool isHighSpeedNominalCapacityAutosized() const;
      bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);
      void resetHighSpeedNominalCapacity();
      void autosizeHighSpeedNominalCapacity();

      boost::optional<double> highSpeedFanPower() const;
      bool isHighSpeedFanPowerDefaulted() const;
      bool isHighSpeedFanPowerAutosized() const;
      bool setHighSpeedFanPower(double highSpeedFanPower);
      void resetHighSpeedFanPower();
      void autosizeHighSpeedFanPower();

      boost::optional<double> lowSpeedNominalCapacity() const;
      bool isLowSpeedNominalCapacityDefaulted() const;
      bool isLowSpeedNominalCapacityAutosized() const;
      bool setLowSpeedNominalCapacity(double lowSpeedNominalCapacity);
      void resetLowSpeedNominalCapacity();
      void autosizeLowSpeedNominalCapacity();

      boost::optional<double> lowSpeedFanPower() const;
      bool isLowSpeedFanPowerDefaulted() const;
      bool isLowSpeedFanPowerAutosized() const;
      bool setLowSpeedFanPower(double lowSpeedFanPower);
      void resetLowSpeedFanPower();
      void autosizeLowSpeedFanPower();

      boost::optional<double> freeConvectionCapacity() const;
      bool isFreeConvectionCapacityDefaulted() const;
      bool isFreeConvectionCapacityAutosized() const;
      bool setFreeConvectionCapacity(double freeConvectionCapacity);
      void resetFreeConvectionCapacity();
      void autosizeFreeConvectionCapacity();

      boost::optional<std::string> priority() const;
      bool setPriority(const std::string& priority);
      void resetPriority();

      double sizingFactor() const;
      bool isSizingFactorDefaulted() const;
      bool setSizingFactor(double sizingFactor);
      void resetSizingFactor();

      boost::optional<std::string> templatePlantLoopType() const;
      bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);
      void resetTemplatePlantLoopType();

      std::vector<std::string> towerTypeValues() const;
      std::vector<std::string> templatePlantLoopTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
