/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDREFLECTANCESNOWMODIFIER_HPP
#define EPMODEL_SITEGROUNDREFLECTANCESNOWMODIFIER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundReflectanceSnowModifier_Impl;
  }

  class EPMODEL_API SiteGroundReflectanceSnowModifier : public ModelObject
  {
   public:
    explicit SiteGroundReflectanceSnowModifier(const Model& model);

    virtual ~SiteGroundReflectanceSnowModifier() override = default;
    SiteGroundReflectanceSnowModifier(const SiteGroundReflectanceSnowModifier& other) = default;
    SiteGroundReflectanceSnowModifier(SiteGroundReflectanceSnowModifier&& other) = default;
    SiteGroundReflectanceSnowModifier& operator=(const SiteGroundReflectanceSnowModifier&) = default;
    SiteGroundReflectanceSnowModifier& operator=(SiteGroundReflectanceSnowModifier&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Scalar getters/setters align with the Snow Modifier fields used by Site:GroundReflectance:SnowModifier.
    // - Field Mapping: GroundReflectedSolarModifier and DaylightingGroundReflectedSolarModifier controls the snow-modified
    //   ground reflectance values when calculating ground reflected solar with snow present.
    double groundReflectedSolarModifier() const;
    bool setGroundReflectedSolarModifier(double groundReflectedSolarModifier);
    bool isGroundReflectedSolarModifierDefaulted() const;
    void resetGroundReflectedSolarModifier();

    double daylightingGroundReflectedSolarModifier() const;
    bool setDaylightingGroundReflectedSolarModifier(double daylightingGroundReflectedSolarModifier);
    bool isDaylightingGroundReflectedSolarModifierDefaulted() const;
    void resetDaylightingGroundReflectedSolarModifier();

   protected:
    using ImplType = detail::SiteGroundReflectanceSnowModifier_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundReflectanceSnowModifier(std::shared_ptr<detail::SiteGroundReflectanceSnowModifier_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SITEGROUNDREFLECTANCESNOWMODIFIER_HPP
