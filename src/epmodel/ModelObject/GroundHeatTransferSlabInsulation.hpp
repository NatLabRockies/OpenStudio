/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABINSULATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabInsulation_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabInsulation : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabInsulation(const Model& model);

    virtual ~GroundHeatTransferSlabInsulation() override = default;
    GroundHeatTransferSlabInsulation(const GroundHeatTransferSlabInsulation& other) = default;
    GroundHeatTransferSlabInsulation(GroundHeatTransferSlabInsulation&& other) = default;
    GroundHeatTransferSlabInsulation& operator=(const GroundHeatTransferSlabInsulation&) = default;
    GroundHeatTransferSlabInsulation& operator=(GroundHeatTransferSlabInsulation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> iVINSFlagIsthereverticalinsulationValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:Insulation fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    double rINSRvalueofunderslabinsulation() const;
    bool isRINSRvalueofunderslabinsulationDefaulted() const;
    bool setRINSRvalueofunderslabinsulation(double rINSRvalueofunderslabinsulation);
    void resetRINSRvalueofunderslabinsulation();

    double dINSWidthofstripofunderslabinsulation() const;
    bool isDINSWidthofstripofunderslabinsulationDefaulted() const;
    bool setDINSWidthofstripofunderslabinsulation(double dINSWidthofstripofunderslabinsulation);
    void resetDINSWidthofstripofunderslabinsulation();

    double rVINSRvalueofverticalinsulation() const;
    bool isRVINSRvalueofverticalinsulationDefaulted() const;
    bool setRVINSRvalueofverticalinsulation(double rVINSRvalueofverticalinsulation);
    void resetRVINSRvalueofverticalinsulation();

    double zVINSDepthofverticalinsulation() const;
    bool isZVINSDepthofverticalinsulationDefaulted() const;
    bool setZVINSDepthofverticalinsulation(double zVINSDepthofverticalinsulation);
    void resetZVINSDepthofverticalinsulation();

    std::string iVINSFlagIsthereverticalinsulation() const;
    bool isIVINSFlagIsthereverticalinsulationDefaulted() const;
    bool setIVINSFlagIsthereverticalinsulation(const std::string& iVINSFlagIsthereverticalinsulation);
    void resetIVINSFlagIsthereverticalinsulation();

   protected:
    using ImplType = detail::GroundHeatTransferSlabInsulation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabInsulation(std::shared_ptr<detail::GroundHeatTransferSlabInsulation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
