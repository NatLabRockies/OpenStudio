/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BUILDING_HPP
#define EPMODEL_BUILDING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Building_Impl;
  }

  class EPMODEL_API Building : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~Building() override = default;
    Building(const Building& other) = default;
    Building(Building&& other) = default;
    Building& operator=(const Building&) = default;
    Building& operator=(Building&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::Building scalar API naming/signatures for this model-counterpart class.
    // - Field Mapping: northAxis maps directly to EnergyPlus Building/North Axis.
    // - Field Mapping: Terrain and warmup/convergence/solar-distribution fields are represented by model::Site and
    //   model::SimulationControl in ForwardTranslator flow and intentionally excluded from this class's scalar API.
    // - TODO(parity): Add cross-object parity wiring for Site/SimulationControl-derived Building fields after scalar saturation.
    double northAxis() const;
    bool setNorthAxis(double northAxis);
    bool isNorthAxisDefaulted() const;
    void resetNorthAxis();

   protected:
    explicit Building(const Model& model);

    using ImplType = detail::Building_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Building(std::shared_ptr<detail::Building_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
