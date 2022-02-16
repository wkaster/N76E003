## N76E003 and MS51xx Bootloader

### Install the Bootloader

After compiled use the Nuvoton's ICP programming tool to install the bootloader in the LDROM portion of the flash memory as shown in the image below.

![NuMicro ICP Programming Tool](./images/icp_programming_tool.png)

Press the "Setting" button and modify the boot option and LDROM size accordingly

![Chip Settings](./images/chip_settings.png)

## N76flash utility

This is the command line used to program the chip from now own, the only mandatory option is the file that should be in **binary** format

Under Development - Use with caution
