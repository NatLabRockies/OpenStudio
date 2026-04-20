/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABBLDGPROPS_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABBLDGPROPS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabBldgProps_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabBldgProps : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabBldgProps(const Model& model);

    virtual ~GroundHeatTransferSlabBldgProps() override = default;
    GroundHeatTransferSlabBldgProps(const GroundHeatTransferSlabBldgProps& other) = default;
    GroundHeatTransferSlabBldgProps(GroundHeatTransferSlabBldgProps&& other) = default;
    GroundHeatTransferSlabBldgProps& operator=(const GroundHeatTransferSlabBldgProps&) = default;
    GroundHeatTransferSlabBldgProps& operator=(GroundHeatTransferSlabBldgProps&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:BldgProps numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    double iyrsNumberofyearstoiterate() const;
    bool isIyrsNumberofyearstoiterateDefaulted() const;
    bool setIyrsNumberofyearstoiterate(double iyrsNumberofyearstoiterate);
    void resetIyrsNumberofyearstoiterate();

    boost::optional<double> shapeSlabshape() const;
    bool setShapeSlabshape(double shapeSlabshape);
    void resetShapeSlabshape();

    boost::optional<double> hbldgBuildingheight() const;
    bool setHbldgBuildingheight(double hbldgBuildingheight);
    void resetHbldgBuildingheight();

    double tin1JanuaryIndoorAverageTemperatureSetpoint() const;
    bool isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin1JanuaryIndoorAverageTemperatureSetpoint(double tin1JanuaryIndoorAverageTemperatureSetpoint);
    void resetTin1JanuaryIndoorAverageTemperatureSetpoint();

    double tin2FebruaryIndoorAverageTemperatureSetpoint() const;
    bool isTin2FebruaryIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin2FebruaryIndoorAverageTemperatureSetpoint(double tin2FebruaryIndoorAverageTemperatureSetpoint);
    void resetTin2FebruaryIndoorAverageTemperatureSetpoint();

    double tin3MarchIndoorAverageTemperatureSetpoint() const;
    bool isTin3MarchIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin3MarchIndoorAverageTemperatureSetpoint(double tin3MarchIndoorAverageTemperatureSetpoint);
    void resetTin3MarchIndoorAverageTemperatureSetpoint();

    double tin4AprilIndoorAverageTemperatureSetpoint() const;
    bool isTin4AprilIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin4AprilIndoorAverageTemperatureSetpoint(double tin4AprilIndoorAverageTemperatureSetpoint);
    void resetTin4AprilIndoorAverageTemperatureSetpoint();

    double tin5MayIndoorAverageTemperatureSetpoint() const;
    bool isTin5MayIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin5MayIndoorAverageTemperatureSetpoint(double tin5MayIndoorAverageTemperatureSetpoint);
    void resetTin5MayIndoorAverageTemperatureSetpoint();

    double tin6JuneIndoorAverageTemperatureSetpoint() const;
    bool isTin6JuneIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin6JuneIndoorAverageTemperatureSetpoint(double tin6JuneIndoorAverageTemperatureSetpoint);
    void resetTin6JuneIndoorAverageTemperatureSetpoint();

    double tin7JulyIndoorAverageTemperatureSetpoint() const;
    bool isTin7JulyIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin7JulyIndoorAverageTemperatureSetpoint(double tin7JulyIndoorAverageTemperatureSetpoint);
    void resetTin7JulyIndoorAverageTemperatureSetpoint();

    double tin8AugustIndoorAverageTemperatureSetpoint() const;
    bool isTin8AugustIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin8AugustIndoorAverageTemperatureSetpoint(double tin8AugustIndoorAverageTemperatureSetpoint);
    void resetTin8AugustIndoorAverageTemperatureSetpoint();

    double tin9SeptemberIndoorAverageTemperatureSetpoint() const;
    bool isTin9SeptemberIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin9SeptemberIndoorAverageTemperatureSetpoint(double tin9SeptemberIndoorAverageTemperatureSetpoint);
    void resetTin9SeptemberIndoorAverageTemperatureSetpoint();

    double tin10OctoberIndoorAverageTemperatureSetpoint() const;
    bool isTin10OctoberIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin10OctoberIndoorAverageTemperatureSetpoint(double tin10OctoberIndoorAverageTemperatureSetpoint);
    void resetTin10OctoberIndoorAverageTemperatureSetpoint();

    double tin11NovemberIndoorAverageTemperatureSetpoint() const;
    bool isTin11NovemberIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin11NovemberIndoorAverageTemperatureSetpoint(double tin11NovemberIndoorAverageTemperatureSetpoint);
    void resetTin11NovemberIndoorAverageTemperatureSetpoint();

    double tin12DecemberIndoorAverageTemperatureSetpoint() const;
    bool isTin12DecemberIndoorAverageTemperatureSetpointDefaulted() const;
    bool setTin12DecemberIndoorAverageTemperatureSetpoint(double tin12DecemberIndoorAverageTemperatureSetpoint);
    void resetTin12DecemberIndoorAverageTemperatureSetpoint();

    double tinAmpDailyIndoorsinewavevariationamplitude() const;
    bool isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted() const;
    bool setTinAmpDailyIndoorsinewavevariationamplitude(double tinAmpDailyIndoorsinewavevariationamplitude);
    void resetTinAmpDailyIndoorsinewavevariationamplitude();

    double convTolConvergenceTolerance() const;
    bool isConvTolConvergenceToleranceDefaulted() const;
    bool setConvTolConvergenceTolerance(double convTolConvergenceTolerance);
    void resetConvTolConvergenceTolerance();

   protected:
    using ImplType = detail::GroundHeatTransferSlabBldgProps_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabBldgProps(std::shared_ptr<detail::GroundHeatTransferSlabBldgProps_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
