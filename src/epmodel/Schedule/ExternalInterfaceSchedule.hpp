/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACESCHEDULE_HPP
#define EPMODEL_EXTERNALINTERFACESCHEDULE_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ExternalInterfaceSchedule_Impl;
  }

  /** \brief Provides a schedule value supplied by an external interface.
   *
   * \par EnergyPlus object
   * \epobject{group-externalinterface.html#externalinterfaceschedule,ExternalInterface:Schedule}
   *
   * \par Important behavior
   * The initial value is used during warm-up and system sizing.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ExternalInterfaceSchedule</code>.
   *
   * - <b>Not yet available:</b> <code>exportToBCVTB()</code>,
   *   <code>isExportToBCVTBDefaulted()</code>,
   *   <code>setExportToBCVTB(...)</code>, and
   *   <code>resetExportToBCVTB()</code>. These methods expose the
   *   OpenStudio-only <code>OS:ExternalInterface:Schedule</code> field.
   *
   * \par Known limitations
   * EnergyPlus <code>ExternalInterface:Schedule</code> has no ExportToBCVTB
   * field, so that OpenStudio Model setting cannot be stored in this wrapper.
   */
  class EPMODEL_API ExternalInterfaceSchedule : public Schedule
  {
   public:
    explicit ExternalInterfaceSchedule(const Model& model, double initialValue);
    explicit ExternalInterfaceSchedule(const Model& model);

    virtual ~ExternalInterfaceSchedule() override = default;
    ExternalInterfaceSchedule(const ExternalInterfaceSchedule& other) = default;
    ExternalInterfaceSchedule(ExternalInterfaceSchedule&& other) = default;
    ExternalInterfaceSchedule& operator=(const ExternalInterfaceSchedule&) = default;
    ExternalInterfaceSchedule& operator=(ExternalInterfaceSchedule&&) = default;

    static IddObjectType iddObjectType();

    // Initial Value accessors
    double initialValue() const;
    bool setInitialValue(double initialValue);

   protected:
    using ImplType = detail::ExternalInterfaceSchedule_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ExternalInterfaceSchedule(std::shared_ptr<detail::ExternalInterfaceSchedule_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
