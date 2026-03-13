/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNON_HPP
#define EPMODEL_AVAILABILITYMANAGERHIGHTEMPERATURETURNON_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerHighTemperatureTurnOn_Impl;
  }

  class EPMODEL_API AvailabilityManagerHighTemperatureTurnOn : public ModelObject
  {
   public:
    explicit AvailabilityManagerHighTemperatureTurnOn(const Model& model);

    virtual ~AvailabilityManagerHighTemperatureTurnOn() override = default;
    AvailabilityManagerHighTemperatureTurnOn(const AvailabilityManagerHighTemperatureTurnOn& other) = default;
    AvailabilityManagerHighTemperatureTurnOn(AvailabilityManagerHighTemperatureTurnOn&& other) = default;
    AvailabilityManagerHighTemperatureTurnOn& operator=(const AvailabilityManagerHighTemperatureTurnOn&) = default;
    AvailabilityManagerHighTemperatureTurnOn& operator=(AvailabilityManagerHighTemperatureTurnOn&&) = default;

    static IddObjectType iddObjectType();

    /** @name Temperature Accessors */
    //@{
    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor name/signature for this model-counterpart class.
    // - Field Mapping: temperature maps to E+ AvailabilityManager:HighTemperatureTurnOn Temperature.
    // - TODO(parity): Keep relationship field sensorNode out of this scalar-only scaffold pass.
    double temperature() const;
    bool setTemperature(double temperature);
    //@}

   protected:
    using ImplType = detail::AvailabilityManagerHighTemperatureTurnOn_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerHighTemperatureTurnOn(std::shared_ptr<detail::AvailabilityManagerHighTemperatureTurnOn_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
