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

class Transformation;

namespace epmodel {

  class Model;

  namespace detail {
    class Building_Impl;
  }

/** \brief Defines building-level geometry and simulation settings.
 *
 * \par EnergyPlus object
 * \epobject{group-simulation-parameters.html#building,Building}
 *
 * \par Important behavior
 * North-axis, terrain, loads-convergence limits, solar-distribution, maximum warmup days, and geometry fields map directly to the EnergyPlus object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::Building</code>.
 * <b>Not yet available:</b> Model's space/thermal-zone collections, space-load and standards relationships, building-level load helpers, and geometry convenience methods are not exposed by this wrapper.
 *
 * \par Known limitations
 * Relationships represented by other EnergyPlus objects, such as space loads and sizing, are not owned by this wrapper.
 */
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

    double northAxis() const;
    bool setNorthAxis(double northAxis);
    bool isNorthAxisDefaulted() const;
    void resetNorthAxis();

    /// Returns the Transformation from the Building coordinate system to world coordinates.
    Transformation transformation() const;

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
