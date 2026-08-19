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

  /** \brief Represents the EnergyPlus InternalMass object.
   *
   * \par EnergyPlus object
   * \epobject{group-thermal-zone-description-geometry.html#internalmass,InternalMass}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::InteriorPartitionSurface</code>. <b>Changed:</b>
   * vertices and explicit surface area collapse onto the required <code>InternalMass</code> Surface Area field; geometry
   * and orientation cannot round-trip.
   *
   * \par Known limitations
   * <code>setVertices()</code> validates and projects a positive area, while <code>resetSurfaceArea()</code> cannot clear the required EnergyPlus field. <code>converttoInternalMass()</code> and vertex-count methods are compatibility shims.
   */
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
