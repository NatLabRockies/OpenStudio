/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICALSIZINGRECTANGLE_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICALSIZINGRECTANGLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatExchangerVerticalSizingRectangle_Impl;
  }

  class EPMODEL_API GroundHeatExchangerVerticalSizingRectangle : public ModelObject
  {
   public:
    explicit GroundHeatExchangerVerticalSizingRectangle(const Model& model);

    virtual ~GroundHeatExchangerVerticalSizingRectangle() override = default;
    GroundHeatExchangerVerticalSizingRectangle(const GroundHeatExchangerVerticalSizingRectangle& other) = default;
    GroundHeatExchangerVerticalSizingRectangle(GroundHeatExchangerVerticalSizingRectangle&& other) = default;
    GroundHeatExchangerVerticalSizingRectangle& operator=(const GroundHeatExchangerVerticalSizingRectangle&) = default;
    GroundHeatExchangerVerticalSizingRectangle& operator=(GroundHeatExchangerVerticalSizingRectangle&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatExchanger:Vertical:Sizing:Rectangle numeric fields.
    // - Field Mapping: SizingPeriod:WeatherFileDays Name is an object-list relationship field and is excluded.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
    double designFlowRatePerBorehole() const;
    bool isDesignFlowRatePerBoreholeDefaulted() const;
    bool setDesignFlowRatePerBorehole(double designFlowRatePerBorehole);
    void resetDesignFlowRatePerBorehole();

    double availableBoreholeFieldLength() const;
    bool setAvailableBoreholeFieldLength(double availableBoreholeFieldLength);

    double availableBoreholeFieldWidth() const;
    bool setAvailableBoreholeFieldWidth(double availableBoreholeFieldWidth);

    double maximumNumberofBoreholes() const;
    bool setMaximumNumberofBoreholes(double maximumNumberofBoreholes);

    double minimumBoreholeSpacing() const;
    bool isMinimumBoreholeSpacingDefaulted() const;
    bool setMinimumBoreholeSpacing(double minimumBoreholeSpacing);
    void resetMinimumBoreholeSpacing();

    double maximumBoreholeSpacing() const;
    bool isMaximumBoreholeSpacingDefaulted() const;
    bool setMaximumBoreholeSpacing(double maximumBoreholeSpacing);
    void resetMaximumBoreholeSpacing();

    double minimumBoreholeVerticalLength() const;
    bool isMinimumBoreholeVerticalLengthDefaulted() const;
    bool setMinimumBoreholeVerticalLength(double minimumBoreholeVerticalLength);
    void resetMinimumBoreholeVerticalLength();

    double maximumBoreholeVerticalLength() const;
    bool isMaximumBoreholeVerticalLengthDefaulted() const;
    bool setMaximumBoreholeVerticalLength(double maximumBoreholeVerticalLength);
    void resetMaximumBoreholeVerticalLength();

    double minimumExitingFluidTemperatureforSizing() const;
    bool isMinimumExitingFluidTemperatureforSizingDefaulted() const;
    bool setMinimumExitingFluidTemperatureforSizing(double minimumExitingFluidTemperatureforSizing);
    void resetMinimumExitingFluidTemperatureforSizing();

    double maximumExitingFluidTemperatureforSizing() const;
    bool isMaximumExitingFluidTemperatureforSizingDefaulted() const;
    bool setMaximumExitingFluidTemperatureforSizing(double maximumExitingFluidTemperatureforSizing);
    void resetMaximumExitingFluidTemperatureforSizing();

   protected:
    using ImplType = detail::GroundHeatExchangerVerticalSizingRectangle_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerVerticalSizingRectangle(std::shared_ptr<detail::GroundHeatExchangerVerticalSizingRectangle_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
