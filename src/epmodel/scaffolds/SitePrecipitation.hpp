/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEPRECIPITATION_HPP
#define EPMODEL_SITEPRECIPITATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SitePrecipitation_Impl;
}

class EPMODEL_API SitePrecipitation : public ModelObject
{
 public:
  explicit SitePrecipitation(const Model& model);

  virtual ~SitePrecipitation() override = default;
  SitePrecipitation(const SitePrecipitation& other) = default;
  SitePrecipitation(SitePrecipitation&& other) = default;
  SitePrecipitation& operator=(const SitePrecipitation&) = default;
  SitePrecipitation& operator=(SitePrecipitation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> precipitationModelTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Site:Precipitation scalar fields.
  // - Field Mapping: PrecipitationRatesScheduleName is excluded in this scalar-only scaffold because it is an object-list relationship field.
  // - TODO(parity): Add relationship helpers for schedule linkage in a dedicated non-scalar parity pass.
  boost::optional<std::string> precipitationModelType() const;
  bool setPrecipitationModelType(const std::string& precipitationModelType);
  void resetPrecipitationModelType();

  boost::optional<double> designLevelforTotalAnnualPrecipitation() const;
  bool setDesignLevelforTotalAnnualPrecipitation(double designLevelforTotalAnnualPrecipitation);
  void resetDesignLevelforTotalAnnualPrecipitation();

  boost::optional<double> averageTotalAnnualPrecipitation() const;
  bool setAverageTotalAnnualPrecipitation(double averageTotalAnnualPrecipitation);
  void resetAverageTotalAnnualPrecipitation();

 protected:
  using ImplType = detail::SitePrecipitation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SitePrecipitation(std::shared_ptr<detail::SitePrecipitation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
