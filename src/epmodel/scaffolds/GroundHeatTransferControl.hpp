/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERCONTROL_HPP
#define EPMODEL_GROUNDHEATTRANSFERCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferControl_Impl;
  }

  class EPMODEL_API GroundHeatTransferControl : public ModelObject
  {
   public:
    explicit GroundHeatTransferControl(const Model& model);

    virtual ~GroundHeatTransferControl() override = default;
    GroundHeatTransferControl(const GroundHeatTransferControl& other) = default;
    GroundHeatTransferControl(GroundHeatTransferControl&& other) = default;
    GroundHeatTransferControl& operator=(const GroundHeatTransferControl&) = default;
    GroundHeatTransferControl& operator=(GroundHeatTransferControl&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Control fields
    //   Run Basement Preprocessor and Run Slab Preprocessor.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    bool runBasementPreprocessor() const;
    bool setRunBasementPreprocessor(bool runBasementPreprocessor);
    bool isRunBasementPreprocessorDefaulted() const;
    void resetRunBasementPreprocessor();

    bool runSlabPreprocessor() const;
    bool setRunSlabPreprocessor(bool runSlabPreprocessor);
    bool isRunSlabPreprocessorDefaulted() const;
    void resetRunSlabPreprocessor();

   protected:
    using ImplType = detail::GroundHeatTransferControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferControl(std::shared_ptr<detail::GroundHeatTransferControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
