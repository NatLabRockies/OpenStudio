/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DESIGNSPECIFICATIONAIRTERMINALSIZING_HPP
#define EPMODEL_DESIGNSPECIFICATIONAIRTERMINALSIZING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DesignSpecificationAirTerminalSizing_Impl;
  }

  class EPMODEL_API DesignSpecificationAirTerminalSizing : public ModelObject
  {
   public:
    explicit DesignSpecificationAirTerminalSizing(const Model& model);

    virtual ~DesignSpecificationAirTerminalSizing() override = default;
    DesignSpecificationAirTerminalSizing(const DesignSpecificationAirTerminalSizing& other) = default;
    DesignSpecificationAirTerminalSizing(DesignSpecificationAirTerminalSizing&& other) = default;
    DesignSpecificationAirTerminalSizing& operator=(const DesignSpecificationAirTerminalSizing&) = default;
    DesignSpecificationAirTerminalSizing& operator=(DesignSpecificationAirTerminalSizing&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type keeps IDD-derived class and accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus DesignSpecification:AirTerminal:Sizing fields.
    // - Field Mapping: This object has no relationship-like scalar fields; all non-name non-extensible fields are included.
    // - TODO(parity): Revisit naming if a model-counterpart parity layer is introduced.
    /** @name Field Accessors */
    //@{
    double fractionofDesignCoolingLoad() const;
    bool isFractionofDesignCoolingLoadDefaulted() const;
    bool setFractionofDesignCoolingLoad(double fractionofDesignCoolingLoad);
    void resetFractionofDesignCoolingLoad();

    double coolingDesignSupplyAirTemperatureDifferenceRatio() const;
    bool isCoolingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const;
    bool setCoolingDesignSupplyAirTemperatureDifferenceRatio(double coolingDesignSupplyAirTemperatureDifferenceRatio);
    void resetCoolingDesignSupplyAirTemperatureDifferenceRatio();

    double fractionofDesignHeatingLoad() const;
    bool isFractionofDesignHeatingLoadDefaulted() const;
    bool setFractionofDesignHeatingLoad(double fractionofDesignHeatingLoad);
    void resetFractionofDesignHeatingLoad();

    double heatingDesignSupplyAirTemperatureDifferenceRatio() const;
    bool isHeatingDesignSupplyAirTemperatureDifferenceRatioDefaulted() const;
    bool setHeatingDesignSupplyAirTemperatureDifferenceRatio(double heatingDesignSupplyAirTemperatureDifferenceRatio);
    void resetHeatingDesignSupplyAirTemperatureDifferenceRatio();

    double fractionofMinimumOutdoorAirFlow() const;
    bool isFractionofMinimumOutdoorAirFlowDefaulted() const;
    bool setFractionofMinimumOutdoorAirFlow(double fractionofMinimumOutdoorAirFlow);
    void resetFractionofMinimumOutdoorAirFlow();
    //@}

   protected:
    using ImplType = detail::DesignSpecificationAirTerminalSizing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DesignSpecificationAirTerminalSizing(std::shared_ptr<detail::DesignSpecificationAirTerminalSizing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
