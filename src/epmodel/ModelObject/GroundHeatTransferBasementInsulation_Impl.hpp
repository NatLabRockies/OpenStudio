/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTINSULATION_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTINSULATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferBasementInsulation_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferBasementInsulation_Impl() override = default;

      // Accessors for REXT: R Value of any exterior insulation.
      boost::optional<double> rEXTRValueofanyexteriorinsulation() const;
      bool setREXTRValueofanyexteriorinsulation(double rEXTRValueofanyexteriorinsulation);
      void resetREXTRValueofanyexteriorinsulation();

      // Accessors for INSFULL: Flag indicating the wall is fully insulated.
      bool iNSFULLFlagIsthewallfullyinsulated() const;
      bool setINSFULLFlagIsthewallfullyinsulated(bool iNSFULLFlagIsthewallfullyinsulated);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
