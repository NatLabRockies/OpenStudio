#!/bin/bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <dmg_file>"
    exit 1
fi

DMG_FILE="$1"
MOUNT_POINT="mount_point_$(date +%s)"
TEMP_RW="temp_rw_$(date +%s).dmg"

echo "-------------------------------------------------------"
echo "Target DMG: $DMG_FILE"
echo "-------------------------------------------------------"

# 1. Convert to Read-Write
echo "Converting to Read-Write..."
rm -f "$TEMP_RW"
hdiutil convert "$DMG_FILE" -format UDRW -o "$TEMP_RW" -quiet

# 2. Resize DMG
# Ad-hoc signatures add metadata. We resize to 2GB to be absolutely sure there's space.
# For DMGs with partition maps (like CPack's GUID images), standard resize works.
# For flat images, -imageonly might be needed.
echo "Resizing DMG..."
if hdiutil resize -size 2g "$TEMP_RW" 2>/dev/null; then
    echo "  Standard resize to 2GB succeeded."
elif hdiutil resize -size 2g -imageonly "$TEMP_RW" 2>/dev/null; then
    echo "  Image-only resize to 2GB succeeded."
else
    echo "Warning: Resize failed, proceeding anyway. This may cause 'internal error' in codesign if space is tight."
fi

# 3. Mount
echo "Mounting..."
mkdir -p "$MOUNT_POINT"
hdiutil attach "$TEMP_RW" -mountpoint "$MOUNT_POINT" -nobrowse -noverify -quiet

# 4. Sign
echo "Applying ad-hoc signature..."
export CODESIGN_ALLOCATE=$(xcrun -find codesign_allocate)

# Find all .app bundles in the mount point
find "$MOUNT_POINT" -maxdepth 1 -name "*.app" -print0 | while IFS= read -r -d '' app_path; do
    echo "Processing app bundle: $app_path"
    
    # Ensure everything is writable
    echo "Ensuring app bundle is writable..."
    chmod -R u+w "$app_path" || true

    # 1. Clear extended attributes
    echo "Clearing extended attributes..."
    xattr -cr "$app_path" || echo "Warning: Some extended attributes could not be cleared."

    # 2. Sign nested components
    echo "Signing nested components..."
    # Sign in depth-first order so that inner items are signed before their containers
    find "$app_path" -depth -print0 \( \
        \( -type d -name "*.framework" \) -o \
        \( -type d -name "*.bundle" \) -o \
        \( -type d -name "*.plugin" \) -o \
        \( -type f -name "*.dylib" \) -o \
        \( -type f -perm -111 \) \
    \) | while IFS= read -r -d '' item; do
        if [ "$item" != "$app_path" ]; then
            # Double check it's actually signable (directory bundle or Mach-O file)
            if [ -d "$item" ]; then
                 echo "  Signing nested bundle: $item"
                 codesign --force --verify --verbose --sign - --timestamp=none --generate-entitlement-der "$item" || true
            elif [ -f "$item" ]; then
                if file "$item" | grep -qE "Mach-O|current ar archive"; then
                    echo "  Signing nested binary: $item"
                    # Try to remove signature first if it fails with internal error
                    codesign --force --verify --verbose --sign - --timestamp=none --generate-entitlement-der "$item" || {
                        echo "  Failed to sign $item, attempting signature removal first..."
                        codesign --remove-signature "$item" || true
                        codesign --force --verify --verbose --sign - --timestamp=none --generate-entitlement-der "$item"
                    }
                fi
            fi
        fi
    done

    echo "Signing top-level app..."
    codesign --force --verify --verbose --sign - --timestamp=none --generate-entitlement-der "$app_path"
done

# 5. Cleanup and Convert Back
echo "Detaching..."
hdiutil detach "$MOUNT_POINT" -force
rmdir "$MOUNT_POINT"

echo "Converting back to compressed DMG..."
FINAL_DMG="signed_repacked.dmg"
hdiutil convert "$TEMP_RW" -format UDZO -o "$FINAL_DMG" -quiet
mv "$FINAL_DMG" "$DMG_FILE"
rm "$TEMP_RW"

echo "Success: $DMG_FILE updated."
