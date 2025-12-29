OpenStudio
==========

OpenStudio is a cross-platform (Windows, Mac, and Linux) collection of software tools to support whole building energy modeling using [EnergyPlus](https://github.com/NREL/EnergyPlus) and advanced daylight analysis using [Radiance](https://github.com/NREL/Radiance/).  OpenStudio is an open source project to facilitate community development, extension, and private sector adoption.

The OpenStudio SDK allows building researchers and software developers to quickly get started through its multiple entry levels, including access through C++, Ruby, Python, and C#.

More information and documentation is available at the [OpenStudio website](https://www.openstudio.net/). User support is available via the community moderated question and answer resource [unmethours.com](https://unmethours.com/questions/).

## Installation Notes (macOS)

For development builds (artifacts downloaded from GitHub Actions), you may encounter a "Damaged" error or "Unidentified Developer" warning on macOS, especially on Apple Silicon (ARM) machines. This is because these builds are not notarized by Apple.

To run these builds, you may need to remove the quarantine attribute from the downloaded application:

```bash
xattr -cr /Applications/OpenStudio-3.11.0.app
```

Or for the installer DMG before mounting:

```bash
xattr -cr path/to/OpenStudio-installer.dmg
```
