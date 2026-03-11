/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSESTORAGE_IMPL_HPP
#define EPMODEL_WATERUSESTORAGE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WaterUseStorage_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WaterUseStorage_Impl() override = default;

      boost::optional<std::string> waterQualitySubcategory() const;
      bool setWaterQualitySubcategory(const std::string& waterQualitySubcategory);

      boost::optional<double> maximumCapacity() const;
      bool setMaximumCapacity(double maximumCapacity);

      boost::optional<double> initialVolume() const;
      bool setInitialVolume(double initialVolume);

      boost::optional<double> designInFlowRate() const;
      bool setDesignInFlowRate(double designInFlowRate);

      boost::optional<double> designOutFlowRate() const;
      bool setDesignOutFlowRate(double designOutFlowRate);

      boost::optional<std::string> typeOfSupplyControlledByFloatValve() const;
      bool setTypeOfSupplyControlledByFloatValve(const std::string& typeOfSupplyControlledByFloatValve);
      std::vector<std::string> typeOfSupplyControlledByFloatValveValues() const;

      boost::optional<double> floatValveOnCapacity() const;
      bool setFloatValveOnCapacity(double floatValveOnCapacity);

      boost::optional<double> floatValveOffCapacity() const;
      bool setFloatValveOffCapacity(double floatValveOffCapacity);

      boost::optional<double> backupMainsCapacity() const;
      bool setBackupMainsCapacity(double backupMainsCapacity);

      boost::optional<std::string> waterThermalMode() const;
      bool setWaterThermalMode(const std::string& waterThermalMode);
      std::vector<std::string> waterThermalModeValues() const;

      boost::optional<std::string> ambientTemperatureIndicator() const;
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);
      std::vector<std::string> ambientTemperatureIndicatorValues() const;

      boost::optional<double> tankSurfaceArea() const;
      bool setTankSurfaceArea(double tankSurfaceArea);

      boost::optional<double> tankUValue() const;
      bool setTankUValue(double tankUValue);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
