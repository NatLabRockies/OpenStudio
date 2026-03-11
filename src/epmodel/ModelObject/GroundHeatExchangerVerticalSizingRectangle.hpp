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
  double availableBoreholeFieldLength() const;
  double availableBoreholeFieldWidth() const;
  double maximumNumberofBoreholes() const;
  double minimumBoreholeSpacing() const;
  double maximumBoreholeSpacing() const;
  double minimumBoreholeVerticalLength() const;
  double maximumBoreholeVerticalLength() const;
  double minimumExitingFluidTemperatureforSizing() const;
  double maximumExitingFluidTemperatureforSizing() const;

  bool isDesignFlowRatePerBoreholeDefaulted() const;
  bool isMinimumBoreholeSpacingDefaulted() const;
  bool isMaximumBoreholeSpacingDefaulted() const;
  bool isMinimumBoreholeVerticalLengthDefaulted() const;
  bool isMaximumBoreholeVerticalLengthDefaulted() const;
  bool isMinimumExitingFluidTemperatureforSizingDefaulted() const;
  bool isMaximumExitingFluidTemperatureforSizingDefaulted() const;

  bool setDesignFlowRatePerBorehole(double designFlowRatePerBorehole);
  bool setAvailableBoreholeFieldLength(double availableBoreholeFieldLength);
  bool setAvailableBoreholeFieldWidth(double availableBoreholeFieldWidth);
  bool setMaximumNumberofBoreholes(double maximumNumberofBoreholes);
  bool setMinimumBoreholeSpacing(double minimumBoreholeSpacing);
  bool setMaximumBoreholeSpacing(double maximumBoreholeSpacing);
  bool setMinimumBoreholeVerticalLength(double minimumBoreholeVerticalLength);
  bool setMaximumBoreholeVerticalLength(double maximumBoreholeVerticalLength);
  bool setMinimumExitingFluidTemperatureforSizing(double minimumExitingFluidTemperatureforSizing);
  bool setMaximumExitingFluidTemperatureforSizing(double maximumExitingFluidTemperatureforSizing);

  void resetDesignFlowRatePerBorehole();
  void resetMinimumBoreholeSpacing();
  void resetMaximumBoreholeSpacing();
  void resetMinimumBoreholeVerticalLength();
  void resetMaximumBoreholeVerticalLength();
  void resetMinimumExitingFluidTemperatureforSizing();
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
