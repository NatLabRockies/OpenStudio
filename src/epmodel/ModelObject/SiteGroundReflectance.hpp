/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDREFLECTANCE_HPP
#define EPMODEL_SITEGROUNDREFLECTANCE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundReflectance_Impl;
  }

  class EPMODEL_API SiteGroundReflectance : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~SiteGroundReflectance() override = default;
    SiteGroundReflectance(const SiteGroundReflectance& other) = default;
    SiteGroundReflectance(SiteGroundReflectance&& other) = default;
    SiteGroundReflectance& operator=(const SiteGroundReflectance&) = default;
    SiteGroundReflectance& operator=(SiteGroundReflectance&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors the openstudio::model SiteGroundReflectance scalar accessor names/signatures for each month.
    // - Field Mapping: Monthly ground reflectance values delegate directly to Site:GroundReflectance month enums with 0.2 defaults.
    double januaryGroundReflectance() const;
    bool isJanuaryGroundReflectanceDefaulted() const;
    bool setJanuaryGroundReflectance(double januaryGroundReflectance);
    void resetJanuaryGroundReflectance();

    double februaryGroundReflectance() const;
    bool isFebruaryGroundReflectanceDefaulted() const;
    bool setFebruaryGroundReflectance(double februaryGroundReflectance);
    void resetFebruaryGroundReflectance();

    double marchGroundReflectance() const;
    bool isMarchGroundReflectanceDefaulted() const;
    bool setMarchGroundReflectance(double marchGroundReflectance);
    void resetMarchGroundReflectance();

    double aprilGroundReflectance() const;
    bool isAprilGroundReflectanceDefaulted() const;
    bool setAprilGroundReflectance(double aprilGroundReflectance);
    void resetAprilGroundReflectance();

    double mayGroundReflectance() const;
    bool isMayGroundReflectanceDefaulted() const;
    bool setMayGroundReflectance(double mayGroundReflectance);
    void resetMayGroundReflectance();

    double juneGroundReflectance() const;
    bool isJuneGroundReflectanceDefaulted() const;
    bool setJuneGroundReflectance(double juneGroundReflectance);
    void resetJuneGroundReflectance();

    double julyGroundReflectance() const;
    bool isJulyGroundReflectanceDefaulted() const;
    bool setJulyGroundReflectance(double julyGroundReflectance);
    void resetJulyGroundReflectance();

    double augustGroundReflectance() const;
    bool isAugustGroundReflectanceDefaulted() const;
    bool setAugustGroundReflectance(double augustGroundReflectance);
    void resetAugustGroundReflectance();

    double septemberGroundReflectance() const;
    bool isSeptemberGroundReflectanceDefaulted() const;
    bool setSeptemberGroundReflectance(double septemberGroundReflectance);
    void resetSeptemberGroundReflectance();

    double octoberGroundReflectance() const;
    bool isOctoberGroundReflectanceDefaulted() const;
    bool setOctoberGroundReflectance(double octoberGroundReflectance);
    void resetOctoberGroundReflectance();

    double novemberGroundReflectance() const;
    bool isNovemberGroundReflectanceDefaulted() const;
    bool setNovemberGroundReflectance(double novemberGroundReflectance);
    void resetNovemberGroundReflectance();

    double decemberGroundReflectance() const;
    bool isDecemberGroundReflectanceDefaulted() const;
    bool setDecemberGroundReflectance(double decemberGroundReflectance);
    void resetDecemberGroundReflectance();

   protected:
    explicit SiteGroundReflectance(const Model& model);

    using ImplType = detail::SiteGroundReflectance_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundReflectance(std::shared_ptr<detail::SiteGroundReflectance_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SITEGROUNDREFLECTANCE_HPP
