/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GEOMETRYTRANSFORM_HPP
#define EPMODEL_GEOMETRYTRANSFORM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GeometryTransform_Impl;
  }

  class EPMODEL_API GeometryTransform : public ModelObject
  {
   public:
    explicit GeometryTransform(const Model& model);

    virtual ~GeometryTransform() override = default;
    GeometryTransform(const GeometryTransform& other) = default;
    GeometryTransform(GeometryTransform&& other) = default;
    GeometryTransform& operator=(const GeometryTransform&) = default;
    GeometryTransform& operator=(GeometryTransform&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> planeofTransformValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: planeofTransform, currentAspectRatio, and newAspectRatio map directly to
    //   EnergyPlus GeometryTransform scalar fields.
    // - TODO(parity): Keep this object scalar-only in this scaffold pass.
    std::string planeofTransform() const;
    bool setPlaneofTransform(const std::string& planeofTransform);
    bool isPlaneofTransformDefaulted() const;
    void resetPlaneofTransform();

    double currentAspectRatio() const;
    bool setCurrentAspectRatio(double currentAspectRatio);

    double newAspectRatio() const;
    bool setNewAspectRatio(double newAspectRatio);

   protected:
    using ImplType = detail::GeometryTransform_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GeometryTransform(std::shared_ptr<detail::GeometryTransform_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
