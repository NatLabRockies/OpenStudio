/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_HEATPUMPAIRTOWATERCOOLINGSPEEDDATA_IMPL_HPP
#define MODEL_HEATPUMPAIRTOWATERCOOLINGSPEEDDATA_IMPL_HPP

#include "ModelAPI.hpp"
#include "ResourceObject_Impl.hpp"

namespace openstudio {
namespace model {

  class Curve;
  class HeatPumpAirToWaterCooling;

  namespace detail {

    /** HeatPumpAirToWaterCoolingSpeedData_Impl is a ResourceObject_Impl that is the implementation class for HeatPumpAirToWaterCoolingSpeedData.*/
    class MODEL_API HeatPumpAirToWaterCoolingSpeedData_Impl : public ResourceObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      HeatPumpAirToWaterCoolingSpeedData_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      HeatPumpAirToWaterCoolingSpeedData_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      HeatPumpAirToWaterCoolingSpeedData_Impl(const HeatPumpAirToWaterCoolingSpeedData_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~HeatPumpAirToWaterCoolingSpeedData_Impl() = default;

      //@}
      /** @name Virtual Methods */
      //@{

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      // Overriding clone and children here because we want to try to remove the Curves (if they aren't used by something else)
      // So we list them as children. But ResourceObject_Impl::clone would also clone them, so we override clone to call ModelObject_Impl::clone
      virtual ModelObject clone(Model model) const override;

      virtual std::vector<ModelObject> children() const override;

      //@}
      /** @name Getters */
      //@{

      boost::optional<double> ratedCoolingCapacity() const;

      bool isRatedCoolingCapacityAutosized() const;

      boost::optional<double> autosizedRatedCoolingCapacity();

      double ratedCOPforCooling() const;

      Curve normalizedCoolingCapacityFunctionofTemperatureCurve() const;

      Curve coolingEnergyInputRatioFunctionofTemperatureCurve() const;

      Curve coolingEnergyInputRatioFunctionofPLRCurve() const;

      //@}
      /** @name Setters */
      //@{

      bool setRatedCoolingCapacity(double ratedCoolingCapacity);

      void autosizeRatedCoolingCapacity();

      bool setRatedCOPforCooling(double ratedCOPforCooling);

      bool setNormalizedCoolingCapacityFunctionofTemperatureCurve(const Curve& bivariateFunctions);

      bool setCoolingEnergyInputRatioFunctionofTemperatureCurve(const Curve& bivariateFunctions);

      bool setCoolingEnergyInputRatioFunctionofPLRCurve(const Curve& univariateFunctions);

      //@}
      /** @name Other */
      //@{

      // convenience function that returns a vector of HeatPumpAirToWaterCooling that use this as their Speed Data (either regular speed or Booster)
      std::vector<HeatPumpAirToWaterCooling> heatPumpAirToWaterCoolings() const;

      void autosize();

      void applySizingValues();

      //@}
     protected:
     private:
      REGISTER_LOGGER("openstudio.model.HeatPumpAirToWaterCoolingSpeedData");

      // Optional getters for use by methods like children() so can remove() if the constructor fails.
      // There are other ways for the public versions of these getters to fail--perhaps all required
      // objects should be returned as boost::optionals
      boost::optional<Curve> optionalNormalizedCoolingCapacityFunctionofTemperatureCurve() const;
      boost::optional<Curve> optionalCoolingEnergyInputRatioFunctionofTemperatureCurve() const;
      boost::optional<Curve> optionalCoolingEnergyInputRatioFunctionofPLRCurve() const;
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HEATPUMPAIRTOWATERCOOLINGSPEEDDATA_IMPL_HPP
