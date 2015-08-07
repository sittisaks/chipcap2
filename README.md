08/06/2015
This is a simple program to read temperature from chipcap2 through i2c bus.
Program was design to build on Openwrt Environment but can be easily ported
to other platform.

BUILD
=====

1. Create directory under openwrt/package/chipcap2 and copy files to it.
2. Under openwrt directory issue command make menuconfig and select Utilities/chipcap2
3. make package/chipcap2/compile
4. Output file will be at openwrt/build_dir/target-mipsel_24kec+dsp_musl-1.1.10/chipcap2-1.0 

