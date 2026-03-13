/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementManualGrid.hpp"
#include "GroundHeatTransferBasementManualGrid_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_ManualGrid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementManualGrid::GroundHeatTransferBasementManualGrid(const Model& model)
    : ModelObject(GroundHeatTransferBasementManualGrid::iddObjectType(), model) {}

  GroundHeatTransferBasementManualGrid::GroundHeatTransferBasementManualGrid(std::shared_ptr<detail::GroundHeatTransferBasementManualGrid_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementManualGrid::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_ManualGrid;
  }

  int GroundHeatTransferBasementManualGrid::nXNumberofcellsintheXdirection20() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->nXNumberofcellsintheXdirection20();
  }

  bool GroundHeatTransferBasementManualGrid::setNXNumberofcellsintheXdirection20(int nXNumberofcellsintheXdirection20) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setNXNumberofcellsintheXdirection20(nXNumberofcellsintheXdirection20);
  }

  int GroundHeatTransferBasementManualGrid::nYNumberofcellsintheYdirection20() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->nYNumberofcellsintheYdirection20();
  }

  bool GroundHeatTransferBasementManualGrid::setNYNumberofcellsintheYdirection20(int nYNumberofcellsintheYdirection20) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setNYNumberofcellsintheYdirection20(nYNumberofcellsintheYdirection20);
  }

  int GroundHeatTransferBasementManualGrid::nZAGNumberofcellsintheZdirectionabovegrade4Always() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->nZAGNumberofcellsintheZdirectionabovegrade4Always();
  }

  bool GroundHeatTransferBasementManualGrid::setNZAGNumberofcellsintheZdirectionabovegrade4Always(
    int nZAGNumberofcellsintheZdirectionabovegrade4Always) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setNZAGNumberofcellsintheZdirectionabovegrade4Always(
      nZAGNumberofcellsintheZdirectionabovegrade4Always);
  }

  int GroundHeatTransferBasementManualGrid::nZBGNumberofcellsinZdirectionbelowgrade1035() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->nZBGNumberofcellsinZdirectionbelowgrade1035();
  }

  bool GroundHeatTransferBasementManualGrid::setNZBGNumberofcellsinZdirectionbelowgrade1035(int nZBGNumberofcellsinZdirectionbelowgrade1035) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setNZBGNumberofcellsinZdirectionbelowgrade1035(
      nZBGNumberofcellsinZdirectionbelowgrade1035);
  }

  int GroundHeatTransferBasementManualGrid::iBASEXdirectioncellindicatorofslabedge520() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->iBASEXdirectioncellindicatorofslabedge520();
  }

  bool GroundHeatTransferBasementManualGrid::setIBASEXdirectioncellindicatorofslabedge520(int iBASEXdirectioncellindicatorofslabedge520) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setIBASEXdirectioncellindicatorofslabedge520(
      iBASEXdirectioncellindicatorofslabedge520);
  }

  int GroundHeatTransferBasementManualGrid::jBASEYdirectioncellindicatorofslabedge520() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->jBASEYdirectioncellindicatorofslabedge520();
  }

  bool GroundHeatTransferBasementManualGrid::setJBASEYdirectioncellindicatorofslabedge520(int jBASEYdirectioncellindicatorofslabedge520) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setJBASEYdirectioncellindicatorofslabedge520(
      jBASEYdirectioncellindicatorofslabedge520);
  }

  int GroundHeatTransferBasementManualGrid::kBASEZdirectioncellindicatorofthetopofthefloorslab520() const {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->kBASEZdirectioncellindicatorofthetopofthefloorslab520();
  }

  bool GroundHeatTransferBasementManualGrid::setKBASEZdirectioncellindicatorofthetopofthefloorslab520(
    int kBASEZdirectioncellindicatorofthetopofthefloorslab520) {
    return getImpl<detail::GroundHeatTransferBasementManualGrid_Impl>()->setKBASEZdirectioncellindicatorofthetopofthefloorslab520(
      kBASEZdirectioncellindicatorofthetopofthefloorslab520);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int GroundHeatTransferBasementManualGrid_Impl::nXNumberofcellsintheXdirection20() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NX_NumberofcellsintheXdirection_20, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setNXNumberofcellsintheXdirection20(int nXNumberofcellsintheXdirection20) {
      return setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NX_NumberofcellsintheXdirection_20, nXNumberofcellsintheXdirection20);
    }

    int GroundHeatTransferBasementManualGrid_Impl::nYNumberofcellsintheYdirection20() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NY_NumberofcellsintheYdirection_20, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setNYNumberofcellsintheYdirection20(int nYNumberofcellsintheYdirection20) {
      return setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NY_NumberofcellsintheYdirection_20, nYNumberofcellsintheYdirection20);
    }

    int GroundHeatTransferBasementManualGrid_Impl::nZAGNumberofcellsintheZdirectionabovegrade4Always() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NZAG_NumberofcellsintheZdirectionabovegrade_4Always, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setNZAGNumberofcellsintheZdirectionabovegrade4Always(
      int nZAGNumberofcellsintheZdirectionabovegrade4Always) {
      return setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NZAG_NumberofcellsintheZdirectionabovegrade_4Always,
                    nZAGNumberofcellsintheZdirectionabovegrade4Always);
    }

    int GroundHeatTransferBasementManualGrid_Impl::nZBGNumberofcellsinZdirectionbelowgrade1035() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NZBG_NumberofcellsinZdirectionbelowgrade_1035, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setNZBGNumberofcellsinZdirectionbelowgrade1035(int nZBGNumberofcellsinZdirectionbelowgrade1035) {
      return setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::NZBG_NumberofcellsinZdirectionbelowgrade_1035,
                    nZBGNumberofcellsinZdirectionbelowgrade1035);
    }

    int GroundHeatTransferBasementManualGrid_Impl::iBASEXdirectioncellindicatorofslabedge520() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::IBASE_Xdirectioncellindicatorofslabedge_520, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setIBASEXdirectioncellindicatorofslabedge520(int iBASEXdirectioncellindicatorofslabedge520) {
      const bool result = setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::IBASE_Xdirectioncellindicatorofslabedge_520,
                                 iBASEXdirectioncellindicatorofslabedge520);
      OS_ASSERT(result);
      return result;
    }

    int GroundHeatTransferBasementManualGrid_Impl::jBASEYdirectioncellindicatorofslabedge520() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::JBASE_Ydirectioncellindicatorofslabedge_520, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setJBASEYdirectioncellindicatorofslabedge520(int jBASEYdirectioncellindicatorofslabedge520) {
      const bool result = setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::JBASE_Ydirectioncellindicatorofslabedge_520,
                                 jBASEYdirectioncellindicatorofslabedge520);
      OS_ASSERT(result);
      return result;
    }

    int GroundHeatTransferBasementManualGrid_Impl::kBASEZdirectioncellindicatorofthetopofthefloorslab520() const {
      const auto value =
        getInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::KBASE_Zdirectioncellindicatorofthetopofthefloorslab_520, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementManualGrid_Impl::setKBASEZdirectioncellindicatorofthetopofthefloorslab520(
      int kBASEZdirectioncellindicatorofthetopofthefloorslab520) {
      const bool result = setInt(openstudio::GroundHeatTransfer_Basement_ManualGridFields::KBASE_Zdirectioncellindicatorofthetopofthefloorslab_520,
                                 kBASEZdirectioncellindicatorofthetopofthefloorslab520);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
