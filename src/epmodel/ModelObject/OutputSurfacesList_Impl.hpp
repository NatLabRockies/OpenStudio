/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSURFACESLIST_IMPL_HPP
#define EPMODEL_OUTPUTSURFACESLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputSurfacesList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputSurfacesList_Impl() override = default;

      std::string reportType() const;
      bool setReportType(const std::string& reportType);
      std::vector<std::string> reportTypeValues() const;

      boost::optional<std::string> reportSpecifications() const;
      bool setReportSpecifications(const std::string& reportSpecifications);
      void resetReportSpecifications();
      std::vector<std::string> reportSpecificationsValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
