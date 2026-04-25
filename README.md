# WPA Supplicant

This is derived from the code at [https://w1.fi/wpa_supplicant/](https://w1.fi/wpa_supplicant/).

As of when this was created, it was version 2.11, using openssl-3.6.2 and npcap-sdk-1.16.

Your mileage may vary on its use. The only goal here was to update the builds, fix some warnings, and make it compile for windows again.

# Building
## Pre-Requisites
### NPCap
You will need NPCap SDK downloaded. You can find it [here](https://npcap.com/).

Put the extracted copy of the zip into the root of this repository. Assuming you cloned to `C:\wpa_supplicant`, you'll want to put the SDK in `C:\wpa_supplicant\npcap-sdk-1.1.6`. You've done it right if inside the NPCap folder you have the lib and includes folders.

In order to use the application on your machine, you'll need to download and install NPCap itself as well. Make sure to install it in **legacy** mode when you do. Otherwise you'll need to grab the DLLs and drop them into the folder with this application as they are not installed on the path or in typical locations.

### OpenSSL
You'll also need to get OpenSSL, specifically 3.6.2 was used here. You'll want to put it in the root of this folder named `openssl-3.6.2`. If you've extracted it right, you'll find `x86` and `x64` directories in there.

## Running the build
To build it, simply open up the `visual_studio/wpa_supplicant.slnx` file in Visual Studio (2026 was used here), and run the build. Your outputs will be placed in the `visual_studio\Debug` folder.

If you wanted to try a newer version, you should be able to just copy the visual\_studio folder to a newer version of wpa\_supplicant and build again. You will likely need to adjust the build files, and fix some warnings/errors that MSVC likes to generate.
