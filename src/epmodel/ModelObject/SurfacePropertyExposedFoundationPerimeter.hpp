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

  /** \brief SurfacePropertyExposedFoundationPerimeter.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#surfaceproperty-exposedfoundationperimeter,SurfaceProperty:ExposedFoundationPerimeter}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SurfacePropertyExposedFoundationPerimeter</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code> and adds <code>exposedPerimeterCalculationMethodValues()</code>; Model construction requires a surface and perimeter inputs. The exposed-perimeter fields are available; <code>surface()</code> and extensible segment entries are not.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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

    /** @name Field accessors */
    //@{

    std::string exposedPerimeterCalculationMethod() const;
    bool setExposedPerimeterCalculationMethod(const std::string& exposedPerimeterCalculationMethod);

    boost::optional<double> totalExposedPerimeter() const;
    bool setTotalExposedPerimeter(double totalExposedPerimeter);

    double exposedPerimeterFraction() const;
    bool isExposedPerimeterFractionDefaulted() const;
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
