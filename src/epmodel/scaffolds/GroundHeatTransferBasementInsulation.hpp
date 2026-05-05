/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTINSULATION_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTINSULATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementInsulation_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementInsulation : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementInsulation(const Model& model);

    virtual ~GroundHeatTransferBasementInsulation() override = default;
    GroundHeatTransferBasementInsulation(const GroundHeatTransferBasementInsulation& other) = default;
    GroundHeatTransferBasementInsulation(GroundHeatTransferBasementInsulation&& other) = default;
    GroundHeatTransferBasementInsulation& operator=(const GroundHeatTransferBasementInsulation&) = default;
    GroundHeatTransferBasementInsulation& operator=(GroundHeatTransferBasementInsulation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:Insulation fields
    //   REXT: R Value of any exterior insulation and INSFULL: Flag: Is the wall fully insulated?.
    // - TODO(parity): Add relationship APIs only if future schema revisions introduce linked fields.
    boost::optional<double> rEXTRValueofanyexteriorinsulation() const;
    bool setREXTRValueofanyexteriorinsulation(double rEXTRValueofanyexteriorinsulation);
    void resetREXTRValueofanyexteriorinsulation();

    bool iNSFULLFlagIsthewallfullyinsulated() const;
    bool setINSFULLFlagIsthewallfullyinsulated(bool iNSFULLFlagIsthewallfullyinsulated);

   protected:
    using ImplType = detail::GroundHeatTransferBasementInsulation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementInsulation(std::shared_ptr<detail::GroundHeatTransferBasementInsulation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
