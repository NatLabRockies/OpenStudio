/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSURFACESLIST_HPP
#define EPMODEL_OUTPUTSURFACESLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputSurfacesList_Impl;
  }

  class EPMODEL_API OutputSurfacesList : public ModelObject
  {
   public:
    explicit OutputSurfacesList(const Model& model);

    virtual ~OutputSurfacesList() override = default;
    OutputSurfacesList(const OutputSurfacesList& other) = default;
    OutputSurfacesList(OutputSurfacesList&& other) = default;
    OutputSurfacesList& operator=(const OutputSurfacesList&) = default;
    OutputSurfacesList& operator=(OutputSurfacesList&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> reportTypeValues();
    static std::vector<std::string> reportSpecificationsValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: reportType/reportSpecifications map directly to E+ Output:Surfaces:List Report Type/Report Specifications.
    // - TODO(parity): Keep scalar-only API stable while extending any non-scalar reporting behaviors in later passes.
    std::string reportType() const;
    bool setReportType(const std::string& reportType);

    boost::optional<std::string> reportSpecifications() const;
    bool setReportSpecifications(const std::string& reportSpecifications);
    void resetReportSpecifications();

   protected:
    using ImplType = detail::OutputSurfacesList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputSurfacesList(std::shared_ptr<detail::OutputSurfacesList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
