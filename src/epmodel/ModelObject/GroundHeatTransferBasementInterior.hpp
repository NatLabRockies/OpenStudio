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
  double hINDownwardconvectiononlyheattransfercoefficient() const;
  double hINUpwardconvectiononlyheattransfercoefficient() const;
  double hINHorizontalconvectiononlyheattransfercoefficient() const;
  double hINDownwardcombinedconvectionandradiationheattransfercoefficient() const;
  double hINUpwardcombinedconvectionandradiationheattransfercoefficient() const;
  double hINHorizontalcombinedconvectionandradiationheattransfercoefficient() const;

  bool isCONDFlagIsthebasementconditionedDefaulted() const;
  bool isHINDownwardconvectiononlyheattransfercoefficientDefaulted() const;
  bool isHINUpwardconvectiononlyheattransfercoefficientDefaulted() const;
  bool isHINHorizontalconvectiononlyheattransfercoefficientDefaulted() const;
  bool isHINDownwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const;
  bool isHINUpwardcombinedconvectionandradiationheattransfercoefficientDefaulted() const;
  bool isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted() const;

  bool setCONDFlagIsthebasementconditioned(bool cONDFlagIsthebasementconditioned);
  bool setHINDownwardconvectiononlyheattransfercoefficient(double hINDownwardconvectiononlyheattransfercoefficient);
  bool setHINUpwardconvectiononlyheattransfercoefficient(double hINUpwardconvectiononlyheattransfercoefficient);
  bool setHINHorizontalconvectiononlyheattransfercoefficient(double hINHorizontalconvectiononlyheattransfercoefficient);
  bool setHINDownwardcombinedconvectionandradiationheattransfercoefficient(
    double hINDownwardcombinedconvectionandradiationheattransfercoefficient);
  bool setHINUpwardcombinedconvectionandradiationheattransfercoefficient(
    double hINUpwardcombinedconvectionandradiationheattransfercoefficient);
  bool setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(
    double hINHorizontalcombinedconvectionandradiationheattransfercoefficient);

  void resetCONDFlagIsthebasementconditioned();
  void resetHINDownwardconvectiononlyheattransfercoefficient();
  void resetHINUpwardconvectiononlyheattransfercoefficient();
  void resetHINHorizontalconvectiononlyheattransfercoefficient();
  void resetHINDownwardcombinedconvectionandradiationheattransfercoefficient();
  void resetHINUpwardcombinedconvectionandradiationheattransfercoefficient();
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
