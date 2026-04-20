/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGSTEAM_HPP
#define EPMODEL_COILHEATINGSTEAM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilHeatingSteam_Impl;
  }

  class EPMODEL_API CoilHeatingSteam : public ModelObject
  {
   public:
    explicit CoilHeatingSteam(const Model& model);

    virtual ~CoilHeatingSteam() override = default;
    CoilHeatingSteam(const CoilHeatingSteam& other) = default;
    CoilHeatingSteam(CoilHeatingSteam&& other) = default;
    CoilHeatingSteam& operator=(const CoilHeatingSteam&) = default;
    CoilHeatingSteam& operator=(CoilHeatingSteam&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> coilControlTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to Coil:Heating:Steam scalar fields.
    // - Field Mapping: Availability schedule and all node-name fields are relationship-like and intentionally excluded.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    boost::optional<double> maximumSteamFlowRate() const;
    bool setMaximumSteamFlowRate(double maximumSteamFlowRate);
    void resetMaximumSteamFlowRate();
    void autosizeMaximumSteamFlowRate();
    bool isMaximumSteamFlowRateAutosized() const;

    boost::optional<double> degreeofSubCooling() const;
    bool setDegreeofSubCooling(double degreeofSubCooling);
    void resetDegreeofSubCooling();

    double degreeofLoopSubCooling() const;
    bool setDegreeofLoopSubCooling(double degreeofLoopSubCooling);
    void resetDegreeofLoopSubCooling();
    bool isDegreeofLoopSubCoolingDefaulted() const;

    boost::optional<std::string> coilControlType() const;
    bool setCoilControlType(const std::string& coilControlType);
    void resetCoilControlType();

   protected:
    using ImplType = detail::CoilHeatingSteam_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilHeatingSteam(std::shared_ptr<detail::CoilHeatingSteam_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
