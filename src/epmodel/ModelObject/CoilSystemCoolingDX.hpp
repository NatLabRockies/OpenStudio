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

  /** \brief Represents the EnergyPlus virtual container for a DX cooling coil and its controls.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilsystemcoolingdx,CoilSystem:Cooling:DX}
   *
   * \par Important behavior
   * Before topology operations, the linked cooling coil, availability schedule,
   * and node fields must be coherent. When the wrapper is added to an air-loop
   * supply branch or a dedicated outdoor-air stream, EPModel synchronizes the
   * supported child coil's inlet and outlet nodes with the container and uses
   * the outlet as the sensor node. The public navigation methods expose the
   * linked cooling coil and sensor node; the linked coil may be a
   * <code>Coil:Cooling:DX</code> or <code>Coil:Cooling:DX:TwoSpeed</code> object.
   *
   * \par OpenStudio Model API
   * OpenStudio Model has no public wrapper for
   * <code>CoilSystem:Cooling:DX</code>. This wrapper is new to the EPModel API.
   *
   * \par Known limitations
   * Topology operations currently support only linked
   * <code>Coil:Cooling:DX</code> and <code>Coil:Cooling:DX:TwoSpeed</code>
   * objects. Other child-coil types allowed by the EnergyPlus schema may be
   * stored and inspected, but they are not yet integrated into this wrapper's
   * topology operations.
   */
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
