/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_HEATPUMPAIRTOWATERCOOLING_IMPL_HPP
#define MODEL_HEATPUMPAIRTOWATERCOOLING_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace model {

  class Curve;
  class HeatPumpAirToWater;
  class HeatPumpAirToWaterCoolingSpeedData;
  class ModelObjectList;
  class Node;
  class Schedule;

  namespace detail {

    /** HeatPumpAirToWaterCooling_Impl is a StraightComponent_Impl that is the implementation class for HeatPumpAirToWaterCooling.*/
    class MODEL_API HeatPumpAirToWaterCooling_Impl : public StraightComponent_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      HeatPumpAirToWaterCooling_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      HeatPumpAirToWaterCooling_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      HeatPumpAirToWaterCooling_Impl(const HeatPumpAirToWaterCooling_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~HeatPumpAirToWaterCooling_Impl() = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

      virtual ModelObject clone(Model model) const override;

      virtual std::vector<ModelObject> children() const override;
      // virtual std::vector<IddObjectType> allowableChildTypes() const override;

      virtual std::vector<IdfObject> remove() override;

      // Overrides from StraightComponent
      virtual unsigned inletPort() const override;
      virtual unsigned outletPort() const override;

      virtual bool addToNode(Node& node) override;

      virtual boost::optional<HVACComponent> containingHVACComponent() const override;
      // virtual boost::optional<Mixer> containingZoneHVACComponent() const override;
      // virtual boost::optional<SetpointManager> containingStraightComponent() const override;

      virtual void autosize() override;

      virtual void applySizingValues() override;

      virtual ComponentType componentType() const override;
      virtual std::vector<FuelType> coolingFuelTypes() const override;
      virtual std::vector<FuelType> heatingFuelTypes() const override;
      virtual std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

      //@}
      /** @name Getters */
      //@{

      Schedule availabilitySchedule() const;

      double ratedInletAirTemperature() const;

      boost::optional<double> ratedAirFlowRate() const;

      bool isRatedAirFlowRateAutosized() const;

      double ratedLeavingWaterTemperature() const;

      boost::optional<double> ratedWaterFlowRate() const;

      bool isRatedWaterFlowRateAutosized() const;

      double minimumOutdoorAirTemperature() const;

      double maximumOutdoorAirTemperature() const;

      boost::optional<Curve> minimumLeavingWaterTemperatureCurve() const;

      boost::optional<Curve> maximumLeavingWaterTemperatureCurve() const;

      double sizingFactor() const;

      boost::optional<HeatPumpAirToWaterCoolingSpeedData> boosterModeOnSpeed() const;

      //@}
      /** @name Setters */
      //@{

      bool setAvailabilitySchedule(Schedule& availabilitySchedule);

      bool setRatedInletAirTemperature(double ratedInletAirTemperature);

      bool setRatedAirFlowRate(double ratedAirFlowRate);

      void autosizeRatedAirFlowRate();

      bool setRatedLeavingWaterTemperature(double ratedLeavingWaterTemperature);

      bool setRatedWaterFlowRate(double ratedWaterFlowRate);

      void autosizeRatedWaterFlowRate();

      bool setMinimumOutdoorAirTemperature(double minimumOutdoorAirTemperature);

      bool setMaximumOutdoorAirTemperature(double maximumOutdoorAirTemperature);

      bool setMinimumLeavingWaterTemperatureCurve(const Curve& minimumLeavingWaterTemperatureCurve);

      void resetMinimumLeavingWaterTemperatureCurve();

      bool setMaximumLeavingWaterTemperatureCurve(const Curve& maximumLeavingWaterTemperatureCurve);

      void resetMaximumLeavingWaterTemperatureCurve();

      bool setSizingFactor(double sizingFactor);

      bool setBoosterModeOnSpeed(const HeatPumpAirToWaterCoolingSpeedData& boosterModeOnSpeed);

      void resetBoosterModeOnSpeed();

      //@}
      /** @name Other */
      //@{

      bool setSpeedDataList(const ModelObjectList& speedDataList);
      void resetSpeedDataList();
      ModelObjectList speedDataList() const;

      std::vector<HeatPumpAirToWaterCoolingSpeedData> speeds() const;
      unsigned numberOfSpeeds() const;
      boost::optional<unsigned> speedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed) const;

      bool addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed);
      bool addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index);
      bool setSpeedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index);
      bool setSpeeds(const std::vector<HeatPumpAirToWaterCoolingSpeedData>& speeds);
      bool removeSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed);
      bool removeSpeed(unsigned index);
      void removeAllSpeeds();

      // Convenience function to return the HeatPumpAirToWater object that reference this cooling coil if any
      boost::optional<HeatPumpAirToWater> heatPumpAirToWater() const;

      // Autosize methods

      boost::optional<double> autosizedRatedAirFlowRate() const;
      boost::optional<double> autosizedRatedWaterFlowRate() const;
      boost::optional<double> autosizedRatedCoolingCapacity() const;  // Convenience method

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.HeatPumpAirToWaterCooling");

      // TODO: Check the return types of these methods.
      // Optional getters for use by methods like children() so can remove() if the constructor fails.
      // There are other ways for the public versions of these getters to fail--perhaps all required
      // objects should be returned as boost::optionals
      boost::optional<Schedule> optionalAvailabilitySchedule() const;
      boost::optional<ModelObjectList> optionalSpeedDataList() const;
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HEATPUMPAIRTOWATERCOOLING_IMPL_HPP
