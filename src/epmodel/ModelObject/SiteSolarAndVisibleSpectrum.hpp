/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITESOLARANDVISIBLESPECTRUM_HPP
#define EPMODEL_SITESOLARANDVISIBLESPECTRUM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteSolarAndVisibleSpectrum_Impl;
  }

  class EPMODEL_API SiteSolarAndVisibleSpectrum : public ModelObject
  {
   public:
    explicit SiteSolarAndVisibleSpectrum(const Model& model);

    virtual ~SiteSolarAndVisibleSpectrum() override = default;
    SiteSolarAndVisibleSpectrum(const SiteSolarAndVisibleSpectrum& other) = default;
    SiteSolarAndVisibleSpectrum(SiteSolarAndVisibleSpectrum&& other) = default;
    SiteSolarAndVisibleSpectrum& operator=(const SiteSolarAndVisibleSpectrum&) = default;
    SiteSolarAndVisibleSpectrum& operator=(SiteSolarAndVisibleSpectrum&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> spectrumDataMethodValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar API maps directly to EnergyPlus Site:SolarAndVisibleSpectrum Spectrum Data Method.
    // - Field Mapping: SolarSpectrumDataObjectName and VisibleSpectrumDataObjectName are excluded in this scalar-only scaffold because they are object-list relationship fields.
    // - TODO(parity): Add relationship helpers for spectrum data object linkage in a dedicated non-scalar parity pass.

    /** @name Getters */
    //@{
    std::string spectrumDataMethod() const;
    bool isSpectrumDataMethodDefaulted() const;
    //@}

    /** @name Setters */
    //@{
    bool setSpectrumDataMethod(const std::string& spectrumDataMethod);
    void resetSpectrumDataMethod();
    //@}

   protected:
    using ImplType = detail::SiteSolarAndVisibleSpectrum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteSolarAndVisibleSpectrum(std::shared_ptr<detail::SiteSolarAndVisibleSpectrum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
