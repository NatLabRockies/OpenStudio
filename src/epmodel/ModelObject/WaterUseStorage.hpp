/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSESTORAGE_HPP
#define EPMODEL_WATERUSESTORAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WaterUseStorage_Impl;
  }

  class EPMODEL_API WaterUseStorage : public ModelObject
  {
   public:
    explicit WaterUseStorage(const Model& model);

    virtual ~WaterUseStorage() override = default;
    WaterUseStorage(const WaterUseStorage& other) = default;
    WaterUseStorage(WaterUseStorage&& other) = default;
    WaterUseStorage& operator=(const WaterUseStorage&) = default;
    WaterUseStorage& operator=(WaterUseStorage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> typeOfSupplyControlledByFloatValveValues();
    static std::vector<std::string> waterThermalModeValues();
    static std::vector<std::string> ambientTemperatureIndicatorValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so WaterUseStorage retains IDD-derived WaterUse:Storage naming.
    // - Field Mapping: Scalars map directly to WaterUse:Storage via WaterUse_StorageFields (Water Quality Subcategory, Maximum Capacity, Initial Volume, Design In Flow Rate, Design Out Flow Rate, Type of Supply Controlled by Float Valve, Float Valve On/Off/Backup Mains Capacities, Water Thermal Mode, Ambient Temperature Indicator, Tank Surface Area, Tank U Value).
    // - Field Mapping: Name is handled by ModelObject base APIs and object-list/reference fields (Overflow Destination, Other Tank Name, Water Temperature Schedule Name, Ambient Temperature Schedule Name, Zone Name, Tank Outside Surface Material Name) remain excluded relationship helpers per the contract.

    /** @name Field accessors
     *  Getter/setter pairs are grouped per field for clarity.
     */
    //@{

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

    boost::optional<double> floatValveOnCapacity() const;
    bool setFloatValveOnCapacity(double floatValveOnCapacity);

    boost::optional<double> floatValveOffCapacity() const;
    bool setFloatValveOffCapacity(double floatValveOffCapacity);

    boost::optional<double> backupMainsCapacity() const;
    bool setBackupMainsCapacity(double backupMainsCapacity);

    boost::optional<std::string> waterThermalMode() const;
    bool setWaterThermalMode(const std::string& waterThermalMode);

    boost::optional<std::string> ambientTemperatureIndicator() const;
    bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

    boost::optional<double> tankSurfaceArea() const;
    bool setTankSurfaceArea(double tankSurfaceArea);

    boost::optional<double> tankUValue() const;
    bool setTankUValue(double tankUValue);

    //@}

   protected:
    using ImplType = detail::WaterUseStorage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterUseStorage(std::shared_ptr<detail::WaterUseStorage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
