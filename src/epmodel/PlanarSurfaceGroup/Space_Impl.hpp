/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACE_IMPL_HPP
#define EPMODEL_SPACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {

class Transformation;

namespace epmodel {

  class ThermalZone;
  class DesignSpecificationOutdoorAir;

  namespace detail {

    class EPMODEL_API Space_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Space_Impl() override = default;

      double ceilingHeight() const;
      bool isCeilingHeightDefaulted() const;
      bool isCeilingHeightAutocalculated() const;
      bool setCeilingHeight(double ceilingHeight);
      void autocalculateCeilingHeight();
      void resetCeilingHeight();

      double volume() const;
      bool isVolumeDefaulted() const;
      bool isVolumeAutocalculated() const;
      bool setVolume(double volume);
      void autocalculateVolume();
      void resetVolume();

      double floorArea() const;
      bool isFloorAreaDefaulted() const;
      bool isFloorAreaAutocalculated() const;
      bool setFloorArea(double floorArea);
      void autocalculateFloorArea();
      void resetFloorArea();

      boost::optional<openstudio::epmodel::ThermalZone> thermalZone() const;
      bool setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);
      void resetThermalZone();
      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> designSpecificationOutdoorAir() const;
      bool setDesignSpecificationOutdoorAir(const openstudio::epmodel::DesignSpecificationOutdoorAir& designSpecificationOutdoorAir);

      void doCanonicalize(LoadContext& context) override;

      Transformation transformation() const;

     private:
      REGISTER_LOGGER("openstudio.epmodel.Space");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
