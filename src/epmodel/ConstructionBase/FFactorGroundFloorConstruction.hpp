/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_HPP
#define EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FFactorGroundFloorConstruction_Impl;
  }

  class EPMODEL_API FFactorGroundFloorConstruction : public ModelObject
  {
   public:
    explicit FFactorGroundFloorConstruction(const Model& model, double fFactor = 0.1, double area = 0.1, double perimeterExposed = 0.1);

    virtual ~FFactorGroundFloorConstruction() override = default;
    FFactorGroundFloorConstruction(const FFactorGroundFloorConstruction& other) = default;
    FFactorGroundFloorConstruction(FFactorGroundFloorConstruction&& other) = default;
    FFactorGroundFloorConstruction& operator=(const FFactorGroundFloorConstruction&) = default;
    FFactorGroundFloorConstruction& operator=(FFactorGroundFloorConstruction&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes: Preserve OpenStudio API names/signatures and map to
    // Construction:FfactorGroundFloor scalar fields.
    //   - fFactor -> field F-Factor
    //   - area -> field Area
    //   - perimeterExposed -> field PerimeterExposed
    // ForwardTranslator: ForwardTranslateFFactorGroundFloorConstruction.cpp maps the three OS
    // scalars directly to the EnergyPlus fields.
    // TODO(parity): Add non-scalar/relationship APIs if needed in later parity passes.

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
