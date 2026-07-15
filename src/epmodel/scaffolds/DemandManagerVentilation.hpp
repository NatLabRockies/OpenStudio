/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERVENTILATION_HPP
#define EPMODEL_DEMANDMANAGERVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class DemandManagerVentilation_Impl;
  }

  class EPMODEL_API DemandManagerVentilation : public ModelObject
  {
   public:
    explicit DemandManagerVentilation(const Model& model);

    virtual ~DemandManagerVentilation() override = default;
    DemandManagerVentilation(const DemandManagerVentilation& other) = default;
    DemandManagerVentilation(DemandManagerVentilation&& other) = default;
    DemandManagerVentilation& operator=(const DemandManagerVentilation&) = default;
    DemandManagerVentilation& operator=(DemandManagerVentilation&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> limitControlValues();
    static std::vector<std::string> selectionControlValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived class/API naming.
    // - Field Mapping: Scalar APIs map directly to DemandManager:Ventilation scalar fields.
    // - Field Mapping: Availability Schedule Name and extensible Controller Outdoor Air Name references remain excluded
    //   as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
    std::string limitControl() const;
    bool setLimitControl(const std::string& limitControl);

    boost::optional<int> minimumLimitDuration() const;
    bool setMinimumLimitDuration(int minimumLimitDuration);
    void resetMinimumLimitDuration();

    boost::optional<double> fixedRate() const;
    bool setFixedRate(double fixedRate);
    void resetFixedRate();

    boost::optional<double> reductionRatio() const;
    bool setReductionRatio(double reductionRatio);
    void resetReductionRatio();

    boost::optional<double> limitStepChange() const;
    bool setLimitStepChange(double limitStepChange);
    void resetLimitStepChange();

    std::string selectionControl() const;
    bool isSelectionControlDefaulted() const;
    bool setSelectionControl(const std::string& selectionControl);
    void resetSelectionControl();

    boost::optional<int> rotationDuration() const;
    bool setRotationDuration(int rotationDuration);
    void resetRotationDuration();

   protected:
    using ImplType = detail::DemandManagerVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit DemandManagerVentilation(std::shared_ptr<detail::DemandManagerVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
