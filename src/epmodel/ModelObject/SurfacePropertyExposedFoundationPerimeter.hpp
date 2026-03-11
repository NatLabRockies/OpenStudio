/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYEXPOSEDFOUNDATIONPERIMETER_HPP
#define EPMODEL_SURFACEPROPERTYEXPOSEDFOUNDATIONPERIMETER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyExposedFoundationPerimeter_Impl;
  }

  // Schema Alignment Notes:
  // - API: This has-counterpart type preserves existing openstudio::model accessor names/signatures.
  // - Field Mapping: exposedPerimeterCalculationMethod maps to E+ SurfaceProperty:ExposedFoundationPerimeter, Exposed Perimeter Calculation Method.
  // - Field Mapping: totalExposedPerimeter maps to E+ Total Exposed Perimeter (N1, optional real, min 0).
  // - Field Mapping: exposedPerimeterFraction maps to E+ Exposed Perimeter Fraction (N2, default 1.0, min 0, max 1).
  // - Field Mapping: Surface Name excluded as object-list relationship field.
  // - Field Mapping: Surface Segment Exposed excluded as extensible boolean-choice field.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.

  class EPMODEL_API SurfacePropertyExposedFoundationPerimeter : public ModelObject
  {
   public:
    explicit SurfacePropertyExposedFoundationPerimeter(const Model& model);

    virtual ~SurfacePropertyExposedFoundationPerimeter() override = default;
    SurfacePropertyExposedFoundationPerimeter(const SurfacePropertyExposedFoundationPerimeter& other) = default;
    SurfacePropertyExposedFoundationPerimeter(SurfacePropertyExposedFoundationPerimeter&& other) = default;
    SurfacePropertyExposedFoundationPerimeter& operator=(const SurfacePropertyExposedFoundationPerimeter&) = default;
    SurfacePropertyExposedFoundationPerimeter& operator=(SurfacePropertyExposedFoundationPerimeter&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> exposedPerimeterCalculationMethodValues();

    /** @name Getters */
    //@{

    std::string exposedPerimeterCalculationMethod() const;

    boost::optional<double> totalExposedPerimeter() const;

    double exposedPerimeterFraction() const;

    bool isExposedPerimeterFractionDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    bool setExposedPerimeterCalculationMethod(const std::string& exposedPerimeterCalculationMethod);

    bool setTotalExposedPerimeter(double totalExposedPerimeter);

    bool setExposedPerimeterFraction(double exposedPerimeterFraction);

    void resetExposedPerimeterFraction();

    //@}

   protected:
    using ImplType = detail::SurfacePropertyExposedFoundationPerimeter_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyExposedFoundationPerimeter(std::shared_ptr<detail::SurfacePropertyExposedFoundationPerimeter_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
