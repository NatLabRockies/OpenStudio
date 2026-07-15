/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONDENSERLOOP_HPP
#define EPMODEL_CONDENSERLOOP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CondenserLoop_Impl;
  }

  class EPMODEL_API CondenserLoop : public ModelObject
  {
   public:
    explicit CondenserLoop(const Model& model);

    virtual ~CondenserLoop() override = default;
    CondenserLoop(const CondenserLoop& other) = default;
    CondenserLoop(CondenserLoop&& other) = default;
    CondenserLoop& operator=(const CondenserLoop&) = default;
    CondenserLoop& operator=(CondenserLoop&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fluidTypeValues();
    static std::vector<std::string> loadDistributionSchemeValues();
    static std::vector<std::string> pressureSimulationTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus CondenserLoop scalar fields.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: CondenserEquipmentOperationSchemeName, CondenserLoopTemperatureSetpointNodeName,
    //   CondenserSide* node/branch/connector fields, and DemandSide* node/branch/connector fields are
    //   relationship-like and intentionally excluded from scalar accessor scaffolding.
    // - TODO(parity): Add typed relationship APIs after scalar saturation without changing scalar signatures.
    std::string fluidType() const;
    bool isFluidTypeDefaulted() const;
    bool setFluidType(const std::string& fluidType);
    void resetFluidType();

    double maximumLoopTemperature() const;
    bool setMaximumLoopTemperature(double maximumLoopTemperature);

    double minimumLoopTemperature() const;
    bool setMinimumLoopTemperature(double minimumLoopTemperature);

    boost::optional<double> maximumLoopFlowRate() const;
    bool setMaximumLoopFlowRate(double maximumLoopFlowRate);
    bool isMaximumLoopFlowRateAutosized() const;
    void autosizeMaximumLoopFlowRate();

    double minimumLoopFlowRate() const;
    bool isMinimumLoopFlowRateDefaulted() const;
    bool setMinimumLoopFlowRate(double minimumLoopFlowRate);
    void resetMinimumLoopFlowRate();

    boost::optional<double> condenserLoopVolume() const;
    bool setCondenserLoopVolume(double condenserLoopVolume);
    bool isCondenserLoopVolumeAutocalculated() const;
    void autocalculateCondenserLoopVolume();
    void resetCondenserLoopVolume();

    std::string loadDistributionScheme() const;
    bool isLoadDistributionSchemeDefaulted() const;
    bool setLoadDistributionScheme(const std::string& loadDistributionScheme);
    void resetLoadDistributionScheme();

    std::string pressureSimulationType() const;
    bool isPressureSimulationTypeDefaulted() const;
    bool setPressureSimulationType(const std::string& pressureSimulationType);
    void resetPressureSimulationType();

    double loopCirculationTime() const;
    bool isLoopCirculationTimeDefaulted() const;
    bool setLoopCirculationTime(double loopCirculationTime);
    void resetLoopCirculationTime();

   protected:
    using ImplType = detail::CondenserLoop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CondenserLoop(std::shared_ptr<detail::CondenserLoop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
