/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTINTERIOR_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTINTERIOR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementInterior_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementInterior : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementInterior(const Model& model);

    virtual ~GroundHeatTransferBasementInterior() override = default;
    GroundHeatTransferBasementInterior(const GroundHeatTransferBasementInterior& other) = default;
    GroundHeatTransferBasementInterior(GroundHeatTransferBasementInterior&& other) = default;
    GroundHeatTransferBasementInterior& operator=(const GroundHeatTransferBasementInterior&) = default;
    GroundHeatTransferBasementInterior& operator=(GroundHeatTransferBasementInterior&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:Interior fields COND and HIN variants.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    bool cONDFlagIsthebasementconditioned() const;
    bool isCONDFlagIsthebasementconditionedDefaulted() const;
    bool setCONDFlagIsthebasementconditioned(bool cONDFlagIsthebasementconditioned);
    void resetCONDFlagIsthebasementconditioned();

    double hINDownwardconvectiononlyheattransfercoefficient() const;
    bool isHINDownwardconvectiononlyheattransfercoefficientDefaulted() const;
    bool setHINDownwardconvectiononlyheattransfercoefficient(double hINDownwardconvectiononlyheattransfercoefficient);
    void resetHINDownwardconvectiononlyheattransfercoefficient();

    double hINUpwardconvectiononlyheattransfercoefficient() const;
    bool isHINUpwardconvectiononlyheattransfercoefficientDefaulted() const;
    bool setHINUpwardconvectiononlyheattransfercoefficient(double hINUpwardconvectiononlyheattransfercoefficient);
    void resetHINUpwardconvectiononlyheattransfercoefficient();

    double hINHorizontalconvectiononlyheattransfercoefficient() const;
    bool isHINHorizontalconvectiononlyheattransfercoefficientDefaulted() const;
    bool setHINHorizontalconvectiononlyheattransfercoefficient(double hINHorizontalconvectiononlyheattransfercoefficient);
    void resetHINHorizontalconvectiononlyheattransfercoefficient();

    double hINDownwardcombinedconvectionandradiationheattransfercoefficient() const;
    bool isHINDownwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const;
    bool setHINDownwardcombinedconvectionandradiationheattransfercoefficient(double hINDownwardcombinedconvectionandradiationheattransfercoefficient);
    void resetHINDownwardcombinedconvectionandradiationheattransfercoefficient();

    double hINUpwardcombinedconvectionandradiationheattransfercoefficient() const;
    bool isHINUpwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const;
    bool setHINUpwardcombinedconvectionandradiationheattransfercoefficient(double hINUpwardcombinedconvectionandradiationheattransfercoefficient);
    void resetHINUpwardcombinedconvectionandradiationheattransfercoefficient();

    double hINHorizontalcombinedconvectionandradiationheattransfercoefficient() const;
    bool isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted() const;
    bool setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(
      double hINHorizontalcombinedconvectionandradiationheattransfercoefficient);
    void resetHINHorizontalcombinedconvectionandradiationheattransfercoefficient();

   protected:
    using ImplType = detail::GroundHeatTransferBasementInterior_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementInterior(std::shared_ptr<detail::GroundHeatTransferBasementInterior_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
