/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTINTERIOR_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTINTERIOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferBasementInterior_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferBasementInterior_Impl() override = default;

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
  bool setHINUpwardcombinedconvectionandradiationheattransfercoefficient(double hINUpwardcombinedconvectionandradiationheattransfercoefficient);
  bool setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(
    double hINHorizontalcombinedconvectionandradiationheattransfercoefficient);

  void resetCONDFlagIsthebasementconditioned();
  void resetHINDownwardconvectiononlyheattransfercoefficient();
  void resetHINUpwardconvectiononlyheattransfercoefficient();
  void resetHINHorizontalconvectiononlyheattransfercoefficient();
  void resetHINDownwardcombinedconvectionandradiationheattransfercoefficient();
  void resetHINUpwardcombinedconvectionandradiationheattransfercoefficient();
  void resetHINHorizontalcombinedconvectionandradiationheattransfercoefficient();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
