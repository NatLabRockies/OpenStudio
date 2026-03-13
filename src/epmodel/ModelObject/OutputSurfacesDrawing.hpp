/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSURFACESDRAWING_HPP
#define EPMODEL_OUTPUTSURFACESDRAWING_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class OutputSurfacesDrawing_Impl;
  }

  class EPMODEL_API OutputSurfacesDrawing : public ModelObject
  {
   public:
    explicit OutputSurfacesDrawing(const Model& model);

    virtual ~OutputSurfacesDrawing() override = default;
    OutputSurfacesDrawing(const OutputSurfacesDrawing& other) = default;
    OutputSurfacesDrawing(OutputSurfacesDrawing&& other) = default;
    OutputSurfacesDrawing& operator=(const OutputSurfacesDrawing&) = default;
    OutputSurfacesDrawing& operator=(OutputSurfacesDrawing&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> reportTypeValues();
    static std::vector<std::string> reportSpecifications1Values();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: reportType/reportSpecifications1 map directly to E+ Output:Surfaces:Drawing Report Type/Report Specifications 1.
    // - Field Mapping: Output:Surfaces:Drawing Report Specifications 2 is an object-list relationship field and is intentionally excluded in scalar-only scaffold scope.
    // - TODO(parity): Add relationship API for Report Specifications 2 (ColorSchemes) in a later non-scalar pass.
    std::string reportType() const;
    bool setReportType(const std::string& reportType);

    std::string reportSpecifications1() const;
    bool isReportSpecifications1Defaulted() const;
    bool setReportSpecifications1(const std::string& reportSpecifications1);
    void resetReportSpecifications1();

   protected:
    using ImplType = detail::OutputSurfacesDrawing_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OutputSurfacesDrawing(std::shared_ptr<detail::OutputSurfacesDrawing_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
