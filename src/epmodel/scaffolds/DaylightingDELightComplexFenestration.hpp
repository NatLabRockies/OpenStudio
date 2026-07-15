/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DAYLIGHTINGDELIGHTCOMPLEXFENESTRATION_HPP
#define EPMODEL_DAYLIGHTINGDELIGHTCOMPLEXFENESTRATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DaylightingDELightComplexFenestration_Impl;
  }

  class EPMODEL_API DaylightingDELightComplexFenestration : public ModelObject
  {
   public:
    explicit DaylightingDELightComplexFenestration(const Model& model);

    virtual ~DaylightingDELightComplexFenestration() override = default;
    DaylightingDELightComplexFenestration(const DaylightingDELightComplexFenestration& other) = default;
    DaylightingDELightComplexFenestration(DaylightingDELightComplexFenestration&& other) = default;
    DaylightingDELightComplexFenestration& operator=(const DaylightingDELightComplexFenestration&) = default;
    DaylightingDELightComplexFenestration& operator=(DaylightingDELightComplexFenestration&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: complexFenestrationType and fenestrationRotation map directly to
    //   Daylighting:DELight:ComplexFenestration scalar fields.
    // - Field Mapping: Building Surface Name and Window Name are relationship/link fields and excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    std::string complexFenestrationType() const;
    bool setComplexFenestrationType(const std::string& complexFenestrationType);

    double fenestrationRotation() const;
    bool isFenestrationRotationDefaulted() const;
    bool setFenestrationRotation(double fenestrationRotation);
    void resetFenestrationRotation();

   protected:
    using ImplType = detail::DaylightingDELightComplexFenestration_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DaylightingDELightComplexFenestration(std::shared_ptr<detail::DaylightingDELightComplexFenestration_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
