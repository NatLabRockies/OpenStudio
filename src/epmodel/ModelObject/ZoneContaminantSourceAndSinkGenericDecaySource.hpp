/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDECAYSOURCE_HPP
#define EPMODEL_ZONECONTAMINANTSOURCEANDSINKGENERICDECAYSOURCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
struct IddObjectType;

namespace epmodel {

  class Model;

  namespace detail {
    class ZoneContaminantSourceAndSinkGenericDecaySource_Impl;
  }

  class EPMODEL_API ZoneContaminantSourceAndSinkGenericDecaySource : public ModelObject
  {
   public:
    explicit ZoneContaminantSourceAndSinkGenericDecaySource(const Model& model);

    virtual ~ZoneContaminantSourceAndSinkGenericDecaySource() override = default;
    ZoneContaminantSourceAndSinkGenericDecaySource(const ZoneContaminantSourceAndSinkGenericDecaySource& other) = default;
    ZoneContaminantSourceAndSinkGenericDecaySource(ZoneContaminantSourceAndSinkGenericDecaySource&& other) = default;
    ZoneContaminantSourceAndSinkGenericDecaySource& operator=(const ZoneContaminantSourceAndSinkGenericDecaySource&) = default;
    ZoneContaminantSourceAndSinkGenericDecaySource& operator=(ZoneContaminantSourceAndSinkGenericDecaySource&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps the IDD-derived ZoneContaminantSourceAndSink:Generic:DecaySource naming.
    // - Field Mapping: initialEmissionRate tracks EnergyPlus's Initial Emission Rate field.
    // - Field Mapping: delayTimeConstant tracks EnergyPlus's Delay Time Constant field.
    // - Field Mapping: Zone Name and Schedule Name remain object-list relationships and are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship helpers once scalar saturation completes without complicating this scalar API.
    boost::optional<double> initialEmissionRate() const;
    bool setInitialEmissionRate(double initialEmissionRate);
    void resetInitialEmissionRate();

    boost::optional<double> delayTimeConstant() const;
    bool setDelayTimeConstant(double delayTimeConstant);
    void resetDelayTimeConstant();

   protected:
    using ImplType = detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneContaminantSourceAndSinkGenericDecaySource(std::shared_ptr<detail::ZoneContaminantSourceAndSinkGenericDecaySource_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
