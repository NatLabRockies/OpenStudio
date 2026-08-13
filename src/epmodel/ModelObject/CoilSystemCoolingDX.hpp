/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDX_HPP
#define EPMODEL_COILSYSTEMCOOLINGDX_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class Node;

  namespace detail {
    class CoilSystemCoolingDX_Impl;
  }

  class EPMODEL_API CoilSystemCoolingDX : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingDX(const Model& model);

    virtual ~CoilSystemCoolingDX() override = default;
    CoilSystemCoolingDX(const CoilSystemCoolingDX& other) = default;
    CoilSystemCoolingDX(CoilSystemCoolingDX&& other) = default;
    CoilSystemCoolingDX& operator=(const CoilSystemCoolingDX&) = default;
    CoilSystemCoolingDX& operator=(CoilSystemCoolingDX&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> coolingCoilObjectTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. This EnergyPlus storage adapter preserves scalar fields and the bounded curve-fit and two-speed DX branch
    //   lifecycles without becoming the public component reported by AirLoopHVAC traversal.
    // - Canonical Counterpart: None. `openstudio::model` creates this EnergyPlus object during translation rather than exposing a same-name class.
    // - Implemented Parity: For exactly `CoilCoolingDX` and `CoilCoolingDXTwoSpeed`, the adapter keeps its inlet, outlet, sensor, child-coil, and
    //   availability-schedule relationships aligned during direct supply-branch placement, movement, detachment, restoration, and reload.
    //   Whole-AirLoopHVAC teardown removes the persisted adapter and referenced coil together for every loaded coil family so it cannot leave an
    //   invalid orphan without air nodes.
    // - Documented Delta: Public AirLoopHVAC traversal projects the linked cooling coil, while Branch and concrete-object access retain the
    //   persisted `CoilSystem:Cooling:DX` record. Topology mutation belongs to the linked coil rather than this adapter's public API.
    // - Field/Storage Mapping: Scalars map directly to `CoilSystem:Cooling:DX`; inlet/outlet use StraightComponent ports, and sensor and cooling
    //   coil are read-only public relationships.
    // - Evidence: `src/epmodel/test/CoilCoolingDX_GTest.cpp`, `src/epmodel/test/CoilCoolingDXTwoSpeed_GTest.cpp`,
    //   `src/epmodel/test/CoilSystemCoolingDX_GTest.cpp`, and the `resources/Examples/compact_osw/measures/EpModelDualDuct` workflow.
    // - Remaining Parity Work: Characterize outdoor-air/DOAS placement and other EnergyPlus-supported child coil families before widening the
    //   adapter's topology contract beyond `CoilCoolingDX` and `CoilCoolingDXTwoSpeed`.
    boost::optional<Node> sensorNode() const;
    boost::optional<ModelObject> coolingCoil() const;
    std::string coolingCoilObjectType() const;
    bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

    std::string dehumidificationControlType() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    bool isDehumidificationControlTypeDefaulted() const;
    void resetDehumidificationControlType();

    bool runonSensibleLoad() const;
    bool setRunonSensibleLoad(bool runonSensibleLoad);
    bool isRunonSensibleLoadDefaulted() const;
    void resetRunonSensibleLoad();

    bool runonLatentLoad() const;
    bool setRunonLatentLoad(bool runonLatentLoad);
    bool isRunonLatentLoadDefaulted() const;
    void resetRunonLatentLoad();

    bool useOutdoorAirDXCoolingCoil() const;
    bool setUseOutdoorAirDXCoolingCoil(bool useOutdoorAirDXCoolingCoil);
    bool isUseOutdoorAirDXCoolingCoilDefaulted() const;
    void resetUseOutdoorAirDXCoolingCoil();

    double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature() const;
    bool setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
    bool isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const;
    void resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature();

   protected:
    using ImplType = detail::CoilSystemCoolingDX_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilSystemCoolingDX(std::shared_ptr<detail::CoilSystemCoolingDX_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
