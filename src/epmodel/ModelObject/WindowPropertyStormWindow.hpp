/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWPROPERTYSTORMWINDOW_HPP
#define EPMODEL_WINDOWPROPERTYSTORMWINDOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WindowPropertyStormWindow_Impl;
  }

  class EPMODEL_API WindowPropertyStormWindow : public ModelObject
  {
   public:
    explicit WindowPropertyStormWindow(const Model& model);

    virtual ~WindowPropertyStormWindow() override = default;
    WindowPropertyStormWindow(const WindowPropertyStormWindow& other) = default;
    WindowPropertyStormWindow(WindowPropertyStormWindow&& other) = default;
    WindowPropertyStormWindow& operator=(const WindowPropertyStormWindow&) = default;
    WindowPropertyStormWindow& operator=(WindowPropertyStormWindow&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type follows the IDD-derived WindowPropertyStormWindow naming/field scope.
    // - Field Mapping: distanceBetweenStormGlassLayerandAdjacentGlass maps to WindowProperty:StormWindow field
    //   "Distance Between Storm Glass Layer and Adjacent Glass".
    // - Field Mapping: monththatStormGlassLayerisPutOn/dayofMonththatStormGlassLayerisPutOn/monththatStormGlassLayerisTakenOff/
    //   dayofMonththatStormGlassLayerisTakenOff map directly to their EnergyPlus counterparts.
    // - Field Mapping: Window Name and Storm Glass Layer Name are relationship/object-list fields and remain excluded from scalar APIs.
    // - TODO(parity): Add relationship helpers once non-scalar coverage becomes necessary.
    double distanceBetweenStormGlassLayerandAdjacentGlass() const;
    bool isDistanceBetweenStormGlassLayerandAdjacentGlassDefaulted() const;
    bool setDistanceBetweenStormGlassLayerandAdjacentGlass(double distanceBetweenStormGlassLayerandAdjacentGlass);
    void resetDistanceBetweenStormGlassLayerandAdjacentGlass();

    int monththatStormGlassLayerisPutOn() const;
    bool setMonththatStormGlassLayerisPutOn(int monththatStormGlassLayerisPutOn);

    int dayofMonththatStormGlassLayerisPutOn() const;
    bool setDayofMonththatStormGlassLayerisPutOn(int dayofMonththatStormGlassLayerisPutOn);

    int monththatStormGlassLayerisTakenOff() const;
    bool setMonththatStormGlassLayerisTakenOff(int monththatStormGlassLayerisTakenOff);

    int dayofMonththatStormGlassLayerisTakenOff() const;
    bool setDayofMonththatStormGlassLayerisTakenOff(int dayofMonththatStormGlassLayerisTakenOff);

   protected:
    using ImplType = detail::WindowPropertyStormWindow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WindowPropertyStormWindow(std::shared_ptr<detail::WindowPropertyStormWindow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
