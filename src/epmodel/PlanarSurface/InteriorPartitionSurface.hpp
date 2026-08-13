/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INTERIORPARTITIONSURFACE_HPP
#define EPMODEL_INTERIORPARTITIONSURFACE_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurface.hpp"

#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class InteriorPartitionSurface_Impl;
  }

  class EPMODEL_API InteriorPartitionSurface : public PlanarSurface
  {
   public:
    explicit InteriorPartitionSurface(const std::vector<Point3d>& vertices, const Model& model);

    virtual ~InteriorPartitionSurface() override = default;
    InteriorPartitionSurface(const InteriorPartitionSurface& other) = default;
    InteriorPartitionSurface(InteriorPartitionSurface&& other) = default;
    InteriorPartitionSurface& operator=(const InteriorPartitionSurface&) = default;
    InteriorPartitionSurface& operator=(InteriorPartitionSurface&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::InteriorPartitionSurface.
    // - Implemented Parity: Preserves the canonical vertex constructor and scalar accessor names. Constructor and
    //   `setVertices()` input is validated and projected to the persisted `InternalMass` surface area.
    // - Documented Delta: EnergyPlus `InternalMass` does not persist vertices or distinguish geometry-derived gross
    //   area from the canonical optional surface-area override. Epmodel therefore collapses constructor/setter vertex
    //   input and explicit surface-area input onto the one required persisted Surface Area field. `resetSurfaceArea()`
    //   is a no-op and `setSurfaceArea(none)` returns false so the EnergyPlus object cannot be left without its required
    //   positive area. Exact vertex geometry and derived orientation queries cannot round-trip. `converttoInternalMass`
    //   and `numberofVertices` remain compatibility shims.
    // - Field/Storage Mapping: `surfaceArea()` and `grossArea()` both read the EnergyPlus `InternalMass` Surface Area
    //   field. Construction Name, Zone or ZoneList Name, and Space or SpaceList Name are relationship fields.
    // - Evidence: `src/model/InteriorPartitionSurface.cpp` and
    //   `src/energyplus/ForwardTranslator/ForwardTranslateInteriorPartitionSurface.cpp`.
    // - Remaining Parity Work: Revisit geometry-dependent APIs only if epmodel adopts explicit non-persisted geometry state.
    bool converttoInternalMass() const;
    bool isConverttoInternalMassDefaulted() const;
    bool setConverttoInternalMass(bool converttoInternalMass);
    void resetConverttoInternalMass();

    boost::optional<double> surfaceArea() const;
    bool setSurfaceArea(boost::optional<double> surfaceArea);
    bool setSurfaceArea(double surfaceArea);
    void resetSurfaceArea();

    boost::optional<double> numberofVertices() const;
    bool isNumberofVerticesDefaulted() const;
    bool isNumberofVerticesAutocalculated() const;
    bool setNumberofVertices(boost::optional<double> numberofVertices);
    bool setNumberofVertices(double numberofVertices);
    void resetNumberofVertices();
    void autocalculateNumberofVertices();

   protected:
    using ImplType = detail::InteriorPartitionSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit InteriorPartitionSurface(std::shared_ptr<detail::InteriorPartitionSurface_Impl> impl);

   private:
    REGISTER_LOGGER("openstudio.epmodel.InteriorPartitionSurface");
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
