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
      bool
        setHINDownwardcombinedconvectionandradiationheattransfercoefficient(double hINDownwardcombinedconvectionandradiationheattransfercoefficient);
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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
