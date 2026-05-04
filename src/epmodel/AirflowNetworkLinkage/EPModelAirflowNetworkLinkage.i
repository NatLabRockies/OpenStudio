#ifndef EPMODEL_AirflowNetworkLinkage_I
#define EPMODEL_AirflowNetworkLinkage_I

#ifdef SWIGPYTHON
  %module openstudioepmodelairflownetworklinkage
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(AirflowNetworkDistributionLinkage, <epmodel/AirflowNetworkLinkage/AirflowNetworkDistributionLinkage.hpp>, 0, 1)

#endif
