/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_THERMOSTAT_HPP
#define EPMODEL_THERMOSTAT_THERMOSTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

namespace openstudio {
namespace epmodel {

  class Model;
  class ThermalZone;

  namespace detail {
    class Thermostat_Impl;
  }

  class EPMODEL_API Thermostat : public ModelObject
  {
   public:
    virtual ~Thermostat() override = default;
    Thermostat(const Thermostat& other) = default;
    Thermostat(Thermostat&& other) = default;
    Thermostat& operator=(const Thermostat&) = default;
    Thermostat& operator=(Thermostat&&) = default;

    boost::optional<ThermalZone> thermalZone() const;

   protected:
    Thermostat(IddObjectType type, const Model& model);

    using ImplType = detail::Thermostat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit Thermostat(std::shared_ptr<ImplType> impl);
  };

  using OptionalThermostat = boost::optional<Thermostat>;

}  // namespace epmodel
}  // namespace openstudio

#endif
