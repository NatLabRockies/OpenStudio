OpenStudio
==========

OpenStudio is a cross-platform (Windows, Mac, and Linux) collection of software tools to support whole building energy modeling using [EnergyPlus](https://github.com/NREL/EnergyPlus) and advanced daylight analysis using [Radiance](https://github.com/NREL/Radiance/).  OpenStudio is an open source project to facilitate community development, extension, and private sector adoption.

The OpenStudio SDK allows building researchers and software developers to quickly get started through its multiple entry levels, including access through C++, Ruby, Python, and C#.

More information and documentation is available at the [OpenStudio website](https://www.openstudio.net/). User support is available via the community moderated question and answer resource [unmethours.com](https://unmethours.com/questions/).

## Installation Notes (macOS)

For development builds (artifacts downloaded from GitHub Actions), you may encounter a "Damaged" error or "Unidentified Developer" warning on macOS, especially on Apple Silicon (ARM) machines. This is because these builds are not notarized by Apple.

If you encounter these issues, standard `xattr` commands on the DMG may not be sufficient. Please follow these steps:

1.  **Mount the DMG** image.
2.  **Copy** the Installer application (e.g., `OpenStudio-3.11.0...app`) from the mounted volume to a local folder (e.g., your `Downloads` folder). *Do not run it directly from the DMG.*
3.  Open a **Terminal** and run the following commands on the *local copy* of the installer:

    ```bash
    # 1. Remove quarantine attributes
    xattr -cr path/to/local/OpenStudio-Installer.app

    # 2. Ad-hoc sign the application (fixes "Killed" or crashes on startup)
    codesign --force --deep --sign - path/to/local/OpenStudio-Installer.app
    ```

4.  Run the installer. If double-clicking fails, run the executable directly with `sudo`:

    ```bash
    sudo path/to/local/OpenStudio-Installer.app/Contents/MacOS/OpenStudio-3.11.0-<version>-Darwin-<arch>
    ```
