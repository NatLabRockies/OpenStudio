/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITESOLARANDVISIBLESPECTRUM_IMPL_HPP
#define EPMODEL_SITESOLARANDVISIBLESPECTRUM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteSolarAndVisibleSpectrum_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteSolarAndVisibleSpectrum_Impl() override = default;

      std::vector<std::string> spectrumDataMethodValues() const;

      std::string spectrumDataMethod() const;
      bool isSpectrumDataMethodDefaulted() const;
      bool setSpectrumDataMethod(const std::string& spectrumDataMethod);
      void resetSpectrumDataMethod();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
