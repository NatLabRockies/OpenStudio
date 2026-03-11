/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWPROPERTYAIRFLOWCONTROL_HPP
#define EPMODEL_WINDOWPROPERTYAIRFLOWCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowPropertyAirflowControl_Impl;
  }

  class EPMODEL_API WindowPropertyAirflowControl : public ModelObject
  {
   public:
    explicit WindowPropertyAirflowControl(const Model& model);

    virtual ~WindowPropertyAirflowControl() override = default;
    WindowPropertyAirflowControl(const WindowPropertyAirflowControl& other) = default;
    WindowPropertyAirflowControl(WindowPropertyAirflowControl&& other) = default;
    WindowPropertyAirflowControl& operator=(const WindowPropertyAirflowControl&) = default;
    WindowPropertyAirflowControl& operator=(WindowPropertyAirflowControl&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> airflowSourceValues();
    static std::vector<std::string> airflowDestinationValues();
    static std::vector<std::string> airflowControlTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses the IDD-derived WindowPropertyAirflowControl names/scope.
    // - Field Mapping: Scalar APIs map to WindowProperty:AirflowControl fields (Airflow Source, Airflow Destination, Maximum Flow Rate,
    //   Airflow Control Type, Airflow Is Scheduled).
    // - Field Mapping: Relationship-oriented fields (Name/SubSurface link, Airflow Multiplier Schedule Name, Airflow Return Air Node Name)
    //   remain excluded to preserve existing ModelObject behavior.
    // - TODO(parity): Implement the relationship helpers once non-scalar coverage is required without changing scalar signatures.
    std::string airflowSource() const;
    bool isAirflowSourceDefaulted() const;
    bool setAirflowSource(const std::string& airflowSource);
    void resetAirflowSource();

    std::string airflowDestination() const;
    bool isAirflowDestinationDefaulted() const;
    bool setAirflowDestination(const std::string& airflowDestination);
    void resetAirflowDestination();

    double maximumFlowRate() const;
    bool isMaximumFlowRateDefaulted() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();

    std::string airflowControlType() const;
    bool isAirflowControlTypeDefaulted() const;
    bool setAirflowControlType(const std::string& airflowControlType);
    void resetAirflowControlType();

    bool airflowIsScheduled() const;
    bool isAirflowIsScheduledDefaulted() const;
    bool setAirflowIsScheduled(bool airflowIsScheduled);
    void resetAirflowIsScheduled();

   protected:
    using ImplType = detail::WindowPropertyAirflowControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowPropertyAirflowControl(std::shared_ptr<detail::WindowPropertyAirflowControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
