/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITESPECTRUMDATA_HPP
#define EPMODEL_SITESPECTRUMDATA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteSpectrumData_Impl;
  }

  class EPMODEL_API SiteSpectrumData : public ModelObject
  {
   public:
    explicit SiteSpectrumData(const Model& model);

    virtual ~SiteSpectrumData() override = default;
    SiteSpectrumData(const SiteSpectrumData& other) = default;
    SiteSpectrumData(SiteSpectrumData&& other) = default;
    SiteSpectrumData& operator=(const SiteSpectrumData&) = default;
    SiteSpectrumData& operator=(SiteSpectrumData&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> spectrumDataTypeValues();

    /** Schema Alignment Notes:
   * - API: This no-counterpart type uses IDD-derived class/accessor naming.
   * - Field Mapping: Scalar API maps directly to EnergyPlus Site:SpectrumData Spectrum Data Type.
   * - Field Mapping: Extensible [Wavelength, Spectrum] groups are excluded in this scalar-only scaffold.
   * - TODO(parity): Add typed helpers for extensible spectrum data pairs in a dedicated non-scalar parity pass.
   */
    //@{
    std::string spectrumDataType() const;
    bool setSpectrumDataType(const std::string& spectrumDataType);
    //@}

   protected:
    using ImplType = detail::SiteSpectrumData_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteSpectrumData(std::shared_ptr<detail::SiteSpectrumData_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
