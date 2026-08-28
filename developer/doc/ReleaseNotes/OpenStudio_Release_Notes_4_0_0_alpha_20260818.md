# OpenStudio Version 4.0.0-alpha

_Release Notes_ - 2026-08-18

These release notes describe OpenStudio SDK 4.0.0-alpha, developed by the
National Laboratory of the Rockies (NLR), Building Technologies and Sciences
Center, Building Performance Modeling Group, and associated collaborators.

This is an alpha release intended for evaluation, API feedback, and early
integration testing. APIs and behavior may change before the final OpenStudio
4.0 release.

The notes are organized into the following sections:

- Overview
- Trying EPModel
- Compatibility and migration
- Installation notes
- Changelog

# Overview

OpenStudio 4.0 begins a major architectural transition from the legacy
`openstudio::model::Model` representation to EPModel
(`openstudio::epmodel::Model`). EPModel is the EnergyPlus-backed implementation
of the OpenStudio Model API, allowing applications and measures to work
directly with the model that EnergyPlus simulates.

During this transition, the new implementation is exposed as
`openstudio::epmodel::Model` so it can coexist with the legacy
`openstudio::model::Model` while compatibility work is underway. That namespace
split is a development boundary, not the intended final API. The objective is
for the EnergyPlus-backed implementation to become a drop-in replacement at
`openstudio::model::Model`, after which users should not need to select or
reference a separate `openstudio::epmodel` model API. OpenStudio 4.0.0-alpha
has not yet reached that endpoint.

## What EPModel changes

- **EnergyPlus is the native model representation.** EPModel loads and saves
  IDF rather than OSM.
- **The API target is the OpenStudio Model API.** EPModel is implementing that
  API directly over EnergyPlus objects rather than defining a parallel,
  EPModel-specific API.
- **Measures operate directly on EPModel.** Python and Ruby measures can create
  and edit EnergyPlus models without a separate OpenStudio model as the
  persistent source of truth.
- **Existing OSMs have an ingress path.** A workflow can begin with an older
  OSM. OpenStudio version-translates that OSM, forward-translates it to IDF,
  and loads the result as an EPModel before measures run.

This planned namespace convergence is about API compatibility, not OSM
persistence. OpenStudio 4.0 does not introduce a 4.0 OpenStudio IDD or a new
4.0 OSM format. The legacy OpenStudio IDD remains at version 3.11.0 to support
existing-model conversion; the replacement model remains EnergyPlus-backed
and IDF-native.

EPModel is still under active development. This alpha does not yet provide
complete API parity with `openstudio::model::Model`, and existing measures and
applications should be tested before being used with EPModel.

# Trying EPModel

The installed SDK includes example workflows under
`<openstudio-install>/Examples/epmodel`. The examples cover three starting
points:

- Create a new EPModel building from scratch.
- Load an EnergyPlus reference building and replace its HVAC system.
- Begin with an OpenStudio 1.11.5 OSM, convert it to EPModel, and either
  simulate it unchanged or replace its HVAC system.

The existing-OSM examples provide a direct demonstration of the migration
path:

```console
<openstudio-install>/bin/openstudio run \
  --output-directory <writable-directory>/existing-osm-as-is \
  -w <openstudio-install>/Examples/epmodel/epmodel_existing_osm_as_is.osw

<openstudio-install>/bin/openstudio run \
  --output-directory <writable-directory>/existing-osm-replace-hvac \
  -w <openstudio-install>/Examples/epmodel/epmodel_existing_osm_replace_hvac.osw
```

The installed example guide is located at
`<openstudio-install>/Examples/epmodel/README.md`.

# Compatibility and migration

## Existing OSM files

Existing OSM files are inputs to a conversion workflow. Internally, OpenStudio
uses the legacy VersionTranslator and ForwardTranslator before constructing an
EPModel. The resulting workflow model and simulation input are IDF-based.

Keep a copy of the original OSM when evaluating this alpha. Review the
translated model and EnergyPlus warnings before adopting the result in a
production workflow.

## Existing measures and applications

Code written for `openstudio::model::Model` may use objects or methods that are
not yet implemented by EPModel. Measure authors should test their measures
against `openstudio::epmodel::Model` and consult the EPModel API documentation
for current coverage.

## Expected alpha changes

The following may change during the alpha and beta cycle:

- EPModel API coverage and method behavior
- Measure compatibility
- Translation behavior
- Workflow output and diagnostics
- Packaging and examples

# Where to find OpenStudio SDK documentation

- OpenStudio SDK documentation and tutorials are available at
  [openstudio.net](https://www.openstudio.net/).
- C++ API documentation is available at
  [OpenStudio SDK Documentation](https://openstudio-sdk-documentation.s3.amazonaws.com/index.html).
- Measure development documentation is available in the
  [OpenStudio Measure Writer's Reference Guide](http://natlabrockies.github.io/OpenStudio-user-documentation/reference/measure_writing_guide/).

# Installation notes

OpenStudio SDK 4.0.0-alpha bundles EnergyPlus 26.1.0. A separate EnergyPlus
installation is not required, and other EnergyPlus builds are not supported by
this OpenStudio SDK release.

The SDK installer includes:

- EnergyPlus 26.1.0
- OpenStudio command-line interface
- Radiance 5.0.a.12
- Ruby API
- Python API
- C++ SDK
- EPModel example workflows

TBD before release:

- Confirm supported operating systems and architectures.
- Confirm supported Python and Ruby versions.
- Add installation-specific alpha caveats, if any.

# OpenStudio SDK changelog

## EPModel

- Introduces EPModel as the model architecture for OpenStudio 4.0.
- Implements the OpenStudio Model API directly over EnergyPlus objects, with
  coverage continuing to expand during the alpha phase.
- Adds Python and Ruby bindings for available EPModel APIs.
- Adds workflow support for IDF and existing-OSM starting points.
- Adds examples for new buildings, EnergyPlus reference buildings, and
  conversion of an older OSM.

## Legacy OpenStudio model compatibility

- Keeps the legacy OpenStudio IDD at version 3.11.0 for version translation and
  OSM conversion.
- Corrects the development-only IDD designation that had incorrectly marked
  the legacy OpenStudio schema as version 4.0.0.
- Does not define a 4.0 OSM schema.

## Workflow and command-line interface

- Adds an output-directory option for OpenStudio workflows.
- Adds end-to-end EPModel workflow tests and installed examples.

## New features, major fixes, and API-breaking changes

TBD: Add selected pull requests and migration notes.

## Minor changes and bug fixes

TBD: Link the 4.0.0-alpha GitHub release changelog.

**Full changelog**: TBD (`v3.11.0...v4.0.0-alpha`)

**New contributors**: TBD

---
# This YAML header controls the pandoc (via TeX) to PDF settings
# To convert the Markdown to PDF, run:
# pandoc OpenStudio_Release_Notes_4_0_0_alpha_20260818.md -o OpenStudio_Release_Notes_4_0_0_alpha_20260818.pdf
title: 'OpenStudio Release Notes - 4.0.0-alpha'
author:
- National Laboratory of the Rockies
colorlinks: true
linkcolor: blue
urlcolor: Mahogany
toccolor: gray
geometry:
- margin=1in
---
