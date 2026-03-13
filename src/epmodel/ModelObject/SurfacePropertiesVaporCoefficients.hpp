/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTIESVAPORCOEFFICIENTS_HPP
#define EPMODEL_SURFACEPROPERTIESVAPORCOEFFICIENTS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertiesVaporCoefficients_Impl;
  }

  class EPMODEL_API SurfacePropertiesVaporCoefficients : public ModelObject
  {
   public:
    explicit SurfacePropertiesVaporCoefficients(const Model& model);

    virtual ~SurfacePropertiesVaporCoefficients() override = default;
    SurfacePropertiesVaporCoefficients(const SurfacePropertiesVaporCoefficients& other) = default;
    SurfacePropertiesVaporCoefficients(SurfacePropertiesVaporCoefficients&& other) = default;
    SurfacePropertiesVaporCoefficients& operator=(const SurfacePropertiesVaporCoefficients&) = default;
    SurfacePropertiesVaporCoefficients& operator=(SurfacePropertiesVaporCoefficients&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> constantExternalVaporTransferCoefficientValues();
    static std::vector<std::string> constantInternalvaporTransferCoefficientValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived scalar accessor names.
    // - Field Mapping: Scalar APIs map directly to EnergyPlus SurfaceProperties:VaporCoefficients fields.
    // - Field Mapping: Relationship fields (node/object-list references) are excluded from this scalar-only scaffold.
    // - TODO(parity): Add excluded relationship APIs in a dedicated relationship pass.
    bool constantExternalVaporTransferCoefficient() const;
    bool setConstantExternalVaporTransferCoefficient(bool constantExternalVaporTransferCoefficient);
    void setConstantExternalVaporTransferCoefficientNoFail(bool constantExternalVaporTransferCoefficient);
    bool isConstantExternalVaporTransferCoefficientDefaulted() const;
    void resetConstantExternalVaporTransferCoefficient();

    double externalVaporCoefficientValue() const;
    bool setExternalVaporCoefficientValue(double externalVaporCoefficientValue);
    bool isExternalVaporCoefficientValueDefaulted() const;
    void resetExternalVaporCoefficientValue();

    bool constantInternalvaporTransferCoefficient() const;
    bool setConstantInternalvaporTransferCoefficient(bool constantInternalvaporTransferCoefficient);
    void setConstantInternalvaporTransferCoefficientNoFail(bool constantInternalvaporTransferCoefficient);
    bool isConstantInternalvaporTransferCoefficientDefaulted() const;
    void resetConstantInternalvaporTransferCoefficient();

    double internalVaporCoefficientValue() const;
    bool setInternalVaporCoefficientValue(double internalVaporCoefficientValue);
    bool isInternalVaporCoefficientValueDefaulted() const;
    void resetInternalVaporCoefficientValue();

   protected:
    using ImplType = detail::SurfacePropertiesVaporCoefficients_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertiesVaporCoefficients(std::shared_ptr<detail::SurfacePropertiesVaporCoefficients_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
