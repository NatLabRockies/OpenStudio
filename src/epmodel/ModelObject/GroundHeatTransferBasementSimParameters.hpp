/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTSIMPARAMETERS_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTSIMPARAMETERS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferBasementSimParameters_Impl;
}

class EPMODEL_API GroundHeatTransferBasementSimParameters : public ModelObject
{
 public:
  explicit GroundHeatTransferBasementSimParameters(const Model& model);

  virtual ~GroundHeatTransferBasementSimParameters() override = default;
  GroundHeatTransferBasementSimParameters(const GroundHeatTransferBasementSimParameters& other) = default;
  GroundHeatTransferBasementSimParameters(GroundHeatTransferBasementSimParameters&& other) = default;
  GroundHeatTransferBasementSimParameters& operator=(const GroundHeatTransferBasementSimParameters&) = default;
  GroundHeatTransferBasementSimParameters& operator=(GroundHeatTransferBasementSimParameters&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:SimParameters fields
  //   F: Multiplier for the ADI solution and IYRS: Maximum number of yearly iterations:.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
  boost::optional<double> fMultiplierfortheADIsolution() const;
  bool setFMultiplierfortheADIsolution(double fMultiplierfortheADIsolution);
  void resetFMultiplierfortheADIsolution();

  int iYRSMaximumnumberofyearlyiterations() const;
  bool isIYRSMaximumnumberofyearlyiterationsDefaulted() const;
  bool setIYRSMaximumnumberofyearlyiterations(int iYRSMaximumnumberofyearlyiterations);
  void resetIYRSMaximumnumberofyearlyiterations();

 protected:
  using ImplType = detail::GroundHeatTransferBasementSimParameters_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferBasementSimParameters(std::shared_ptr<detail::GroundHeatTransferBasementSimParameters_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
