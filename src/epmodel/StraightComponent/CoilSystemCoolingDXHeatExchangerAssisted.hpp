/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_HPP
#define EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class AirToAirComponent;

  namespace detail {
    class CoilSystemCoolingDXHeatExchangerAssisted_Impl;
  }

  /** \brief Represents a DX cooling coil system assisted by an air-to-air heat exchanger.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilsystemcoolingdxheatexchangerassisted,CoilSystem:Cooling:DX:HeatExchangerAssisted}.
   *
   * \par Important behavior
   * Referenced child coils and the supported contained air path are stored through the EnergyPlus object-list fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilSystemCoolingDXHeatExchangerAssisted</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code> and explicit child object-type accessors. <b>Not yet available:</b> broader containing-component, clone/remove, and higher-level air-node convenience methods.
   * \par Known limitations
   * Use the supported compound-parent workflows for loop placement.
   */
  class EPMODEL_API CoilSystemCoolingDXHeatExchangerAssisted : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingDXHeatExchangerAssisted(const Model& model);
    explicit CoilSystemCoolingDXHeatExchangerAssisted(const Model& model, const AirToAirComponent& heatExchanger);

    virtual ~CoilSystemCoolingDXHeatExchangerAssisted() override = default;
    CoilSystemCoolingDXHeatExchangerAssisted(const CoilSystemCoolingDXHeatExchangerAssisted& other) = default;
    CoilSystemCoolingDXHeatExchangerAssisted(CoilSystemCoolingDXHeatExchangerAssisted&& other) = default;
    CoilSystemCoolingDXHeatExchangerAssisted& operator=(const CoilSystemCoolingDXHeatExchangerAssisted&) = default;
    CoilSystemCoolingDXHeatExchangerAssisted& operator=(CoilSystemCoolingDXHeatExchangerAssisted&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();

    AirToAirComponent heatExchanger() const;
    bool setHeatExchanger(const AirToAirComponent& heatExchanger);

    StraightComponent coolingCoil() const;
    bool setCoolingCoil(const StraightComponent& coolingCoil);

    bool addToNode(Node& node);

    // Heat exchanger object-type accessors
    std::string heatExchangerObjectType() const;
    bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);

    // Cooling coil object-type accessors
    std::string coolingCoilObjectType() const;
    bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

   protected:
    using ImplType = detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilSystemCoolingDXHeatExchangerAssisted(std::shared_ptr<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
