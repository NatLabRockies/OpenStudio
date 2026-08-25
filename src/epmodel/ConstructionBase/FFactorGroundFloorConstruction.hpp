/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_HPP
#define EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ConstructionBase/ConstructionBase.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FFactorGroundFloorConstruction_Impl;
  }

  /** \brief Defines an F-factor ground-floor construction.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#constructionffactorgroundfloor,Construction:FfactorGroundFloor}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::FFactorGroundFloorConstruction</code>. The
   * <code>fFactor()</code>, <code>area()</code>, and
   * <code>perimeterExposed()</code> fields have the same public meaning.
   *
   * \par Known limitations
   * The object exposes only the three EnergyPlus scalar fields.
   */
  class EPMODEL_API FFactorGroundFloorConstruction : public ConstructionBase
  {
   public:
    explicit FFactorGroundFloorConstruction(const Model& model, double fFactor = 0.1, double area = 0.1, double perimeterExposed = 0.1);

    virtual ~FFactorGroundFloorConstruction() override = default;
    FFactorGroundFloorConstruction(const FFactorGroundFloorConstruction& other) = default;
    FFactorGroundFloorConstruction(FFactorGroundFloorConstruction&& other) = default;
    FFactorGroundFloorConstruction& operator=(const FFactorGroundFloorConstruction&) = default;
    FFactorGroundFloorConstruction& operator=(FFactorGroundFloorConstruction&&) = default;

    static IddObjectType iddObjectType();

    double fFactor() const;
    bool setFFactor(double fFactor);

    double area() const;
    bool setArea(double area);

    double perimeterExposed() const;
    bool setPerimeterExposed(double perimeterExposed);

   protected:
    using ImplType = detail::FFactorGroundFloorConstruction_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FFactorGroundFloorConstruction(std::shared_ptr<detail::FFactorGroundFloorConstruction_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
