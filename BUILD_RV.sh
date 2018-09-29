#!/bin/bash
#
# RAGHU VARMA Build Script 
# Coded by BlackMesa @2018
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
clear
# Init Fields
RV_V_MAJOR=2
RV_V_MINOR=0
RV_VERSION=v$RV_V_MAJOR.$RV_V_MINOR
RV_BUILD=RVA7
RV_DATE=$(date +%Y%m%d)
RV_TOOLCHAIN=/home/ubuntu/arm-eabi-4.9/bin/arm-eabi-
RV_JOBS=`grep processor /proc/cpuinfo|wc -l`
RV_DIR=$(pwd)
# Init Methods
CLEAN_SOURCE()
{
	make clean
	make mrproper
	rm -r -f $RV_DIR/output
}
BUILD_ZIMAGE()
{
	echo "----------------------------------------------"
	echo "Building zImage for $RV_VARIANT..."
	echo " "
	export ARCH=arm
	export CROSS_COMPILE=$RV_TOOLCHAIN
	export LOCALVERSION=-RV_Kernel-$RV_VERSION-$RV_VARIANT-$RV_DATE
	mkdir output
	make -C $RV_DIR -j$RV_JOBS O=output msm8916_sec_defconfig VARIANT_DEFCONFIG=$RV_DEFCON SELINUX_DEFCONFIG=selinux_defconfig
	make -C $RV_DIR -j$RV_JOBS O=output
	echo " "
}
BUILD_DTB()
{
	echo "----------------------------------------------"
	echo "Building dtb for $RV_VARIANT..."
	echo " "
	$RV_DIR/tools/dtbTool -o $RV_DIR/RV/dtb.img $RV_DIR/output/arch/arm/boot/dts/
	echo " "
}
PACK_COMMON_IMG()
{
	echo "----------------------------------------------"
	echo "Packing boot.img for $RV_VARIANT..."
	echo " "
	mkdir -p $RV_DIR/RV/tools/aik/ramdisk
	mkdir -p $RV_DIR/RV/tools/aik/split_img
	cp -rf $RV_DIR/RV/ramdisk/common/ramdisk/* $RV_DIR/RV/tools/aik/ramdisk
	cp -rf $RV_DIR/RV/ramdisk/common/split_img/* $RV_DIR/RV/tools/aik/split_img
	mv $RV_DIR/output/arch/arm/boot/zImage $RV_DIR/RV/tools/aik/split_img/boot.img-zImage
	mv $RV_DIR/RV/dtb.img $RV_DIR/	RV/tools/aik/split_img/boot.img-dtb
	$RV_DIR/RV/tools/aik/repackimg.sh
	mv $RV_DIR/RV/tools/aik/image-new.img $RV_DIR/RV/build/boot-$RV_VARIANT-$RV_DATE.img
	$RV_DIR/RV/tools/aik/cleanup.sh
}
PACK_VARIANT_IMG()
{
	echo "----------------------------------------------"
	echo "Packing boot.img for $RV_VARIANT..."
	echo " "
	mkdir -p $RV_DIR/RV/tools/aik/ramdisk
	mkdir -p $RV_DIR/RV/tools/aik/split_img
	cp -rf $RV_DIR/RV/ramdisk/common/ramdisk/* $RV_DIR/RV/tools/aik/ramdisk
	cp -rf $RV_DIR/RV/ramdisk/common/split_img/* $RV_DIR/RV/tools/aik/split_img
	cp -rf $RV_DIR/RV/ramdisk/$RV_VARIANT/ramdisk/* $RV_DIR/RV/tools/aik/ramdisk
	mv $RV_DIR/output/arch/arm/boot/zImage $RV_DIR/RV/tools/aik/split_img/boot.img-zImage
	mv $RV_DIR/RV/dtb.img $RV_DIR/RV/tools/aik/split_img/boot.img-dtb
	$RV_DIR/RV/tools/aik/repackimg.sh
	mv $RV_DIR/RV/tools/aik/image-new.img $RV_DIR/RV/build/boot-$RV_VARIANT-$RV_DATE.img
	$RV_DIR/RV/tools/aik/cleanup.sh
}
PACK_ON7_ZIP()
{
	echo "----------------------------------------------"
	echo "Packing flashable zip for ON7 2015 kernels..."
	echo " "
	mkdir -p $RV_DIR/RV/work
	mkdir -p $RV_DIR/RV/work/META-INF/com/google/android
	mkdir -p $RV_DIR/RV/work/RV/o7lte
	cp -f $RV_DIR/RV/tools/flashable/binary $RV_DIR/RV/work/META-INF/com/google/android/update-binary
	cp -f $RV_DIR/RV/tools/flashable/ON7 $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	sed -i s'/RVVER/v2.0/'g $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	cp -f $RV_DIR/RV/tools/flashable/pronto $RV_DIR/RV/work/RV/pronto
	cp -f $RV_DIR/RV/tools/flashable/wpsw $RV_DIR/RV/work/RV/wpsw
	mv $RV_DIR/RV/build/boot-o7lte-$RV_DATE.img $RV_DIR/RV/work/RV/o7lte/boot.img
	cd $RV_DIR/RV/work
        $RV_DIR/RV/tools/flashable/zip -r -9 - * > $RV_DIR/RV/build/RV_Kernel-$RV_VERSION-$RV_BUILD-ON7_SM-G600FY.zip
	cd $RV_DIR
	rm -r -f $RV_DIR/RV/work
}
PACK_ON7PRO_ZIP()
{
	echo "----------------------------------------------"
	echo "Packing flashable zip for ON7PRO 2015 kernels..."
	echo " "
	mkdir -p $RV_DIR/RV/work
	mkdir -p $RV_DIR/RV/work/META-INF/com/google/android
	mkdir -p $RV_DIR/RV/work/RV/o7prolte
	cp -f $RV_DIR/RV/tools/flashable/binary $RV_DIR/RV/work/META-INF/com/google/android/update-binary
	cp -f $RV_DIR/RV/tools/flashable/ON7PRO $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	sed -i s'/RVVER/v2.0/'g $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	cp -f $RV_DIR/RV/tools/flashable/pronto $RV_DIR/RV/work/RV/pronto
	cp -f $RV_DIR/RV/tools/flashable/wpsw $RV_DIR/RV/work/RV/wpsw
	mv $RV_DIR/RV/build/boot-o7prolte-$RV_DATE.img $RV_DIR/RV/work/RV/o7prolte/boot.img
	cd $RV_DIR/RV/work
	$RV_DIR/RV/tools/flashable/zip -r -9 - * > $RV_DIR/RV/build/RV_Kernel-$RV_VERSION-$RV_BUILD-ON7PRO_SM-G600FY.zip
	cd $RV_DIR
	rm -r -f $RV_DIR/RV/work
}
PACK_J5LTE_ZIP()
{
	echo "----------------------------------------------"
	echo "Packing flashable zip for J5LTE 2015 kernels..."
	echo " "
	mkdir -p $RV_DIR/RV/work
	mkdir -p $RV_DIR/RV/work/META-INF/com/google/android
	mkdir -p $RV_DIR/RV/work/RV/j5lte
	cp -f $RV_DIR/RV/tools/flashable/binary $RV_DIR/RV/work/META-INF/com/google/android/update-binary
	cp -f $RV_DIR/RV/tools/flashable/J5LTE $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	sed -i s'/RVVER/v2.0/'g $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	cp -f $RV_DIR/RV/tools/flashable/pronto $RV_DIR/RV/work/RV/pronto
	cp -f $RV_DIR/RV/tools/flashable/wpsw $RV_DIR/RV/work/RV/wpsw
	mv $RV_DIR/RV/build/boot-j5lte-$RV_DATE.img $RV_DIR/RV/work/RV/j5lte/boot.img
	cd $RV_DIR/RV/work
	$RV_DIR/RV/tools/flashable/zip -r -9 - * > $RV_DIR/RV/build/RV_Kernel-$RV_VERSION-$RV_BUILD-J5LTE_J500F.zip
	cd $RV_DIR
	rm -r -f $RV_DIR/RV/work
}
PACK_J5XLTE_ZIP()
{
	echo "----------------------------------------------"
	echo "Packing flashable zip for J5XLTE 2016 kernels..."
	echo " "
	mkdir -p $RV_DIR/RV/work
	mkdir -p $RV_DIR/RV/work/META-INF/com/google/android
	mkdir -p $RV_DIR/RV/work/RV/j5xlte
	cp -f $RV_DIR/RV/tools/flashable/binary $RV_DIR/RV/work/META-INF/com/google/android/update-binary
	cp -f $RV_DIR/RV/tools/flashable/J5XLTE $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	sed -i s'/RVVER/v2.0/'g $RV_DIR/RV/work/META-INF/com/google/android/updater-script
	cp -f $RV_DIR/RV/tools/flashable/pronto $RV_DIR/RV/work/RV/pronto
	cp -f $RV_DIR/RV/tools/flashable/wpsw $RV_DIR/RV/work/RV/wpsw
	mv $RV_DIR/RV/build/boot-j5xlte-$RV_DATE.img $RV_DIR/RV/work/RV/j5xlte/boot.img
	cd $RV_DIR/RV/work
	$RV_DIR/RV/tools/flashable/zip -r -9 - * > $RV_DIR/RV/build/RV_Kernel-$RV_VERSION-$RV_BUILD-J5XLTE_J510.zip
	cd $RV_DIR
	rm -r -f $RV_DIR/RV/work
}

# Main Menu
clear
echo "----------------------------------------------"
echo "RAGHUVARMA $RV_VERSION Build Script"
echo "Coded by RAGHU_VARMA"
echo "----------------------------------------------"
PS3='Please select your option (1-4): '
menuvar=("ON7 2015" "ON7PRO 2015" "J5 2015" "J5 2016" "Exit")
select menuvar in "${menuvar[@]}"
do
    case $menuvar in
        "ON7 2015")
            clear
            echo "----------------------------------------------"
            echo "Starting build for all the ON7 2015 variant."
            echo "Please be patient..."
            # o7lte
            echo "----------------------------------------------"
            echo "Cleaning up source..."
            echo " "
            CLEAN_SOURCE
            echo " "
            echo "----------------------------------------------"
            echo "Starting o7lte kernel build..."
            RV_VARIANT=o7lte
            RV_DEFCON=msm8916_sec_o7lte_defconfig
            BUILD_ZIMAGE
            BUILD_DTB
            PACK_VARIANT_IMG
            echo " "
            echo "----------------------------------------------"
            echo "o7lte kernel build finished."
            PACK_ON7_ZIP
            echo " "
            echo "----------------------------------------------"
            echo "ON7 2015 kernels build finished."
            echo "Flashable zip is located into RV/build."
            echo "Press any key for end the script."
            echo "----------------------------------------------"
            read -n1 -r key
            break
            ;;
	"ON7PRO 2015")
            clear
            echo "----------------------------------------------"
            echo "Starting build for all the ON7PRO 2015 variant."
            echo "Please be patient..."
            # o7prolte
            echo "----------------------------------------------"
            echo "Cleaning up source..."
            echo " "
            CLEAN_SOURCE
            echo " "
            echo "----------------------------------------------"
            echo "Starting o7prolte kernel build..."
            RV_VARIANT=o7prolte
            RV_DEFCON=msm8916_sec_o7lte_defconfig
            BUILD_ZIMAGE
            BUILD_DTB
            PACK_VARIANT_IMG
            echo " "
            echo "----------------------------------------------"
            echo "o7prolte kernel build finished."
            PACK_ON7PRO_ZIP
            echo " "
            echo "----------------------------------------------"
            echo "ON7PRO 2015 kernels build finished."
            echo "Flashable zip is located into RV/build."
            echo "Press any key for end the script."
            echo "----------------------------------------------"
            read -n1 -r key
            break
            ;;
	"J5 2015")
            clear
            echo "----------------------------------------------"
            echo "Starting build for all the J5 2015 variant."
            echo "Please be patient..."
            # j5lte
            echo "----------------------------------------------"
            echo "Cleaning up source..."
            echo " "
            CLEAN_SOURCE
            echo " "
            echo "----------------------------------------------"
            echo "Starting j5lte kernel build..."
            RV_VARIANT=j5lte
            RV_DEFCON=msm8916_sec_j5lte_defconfig
            BUILD_ZIMAGE
            BUILD_DTB
            PACK_VARIANT_IMG
            echo " "
            echo "----------------------------------------------"
            echo "j5lte kernel build finished."
            PACK_J5LTE_ZIP
            echo " "
            echo "----------------------------------------------"
            echo "J5 2015 kernels build finished."
            echo "Flashable zip is located into RV/build."
            echo "Press any key for end the script."
            echo "----------------------------------------------"
            read -n1 -r key
            break
            ;;
	"J5 2016")
            clear
            echo "----------------------------------------------"
            echo "Starting build for all the J5 2016 variant."
            echo "Please be patient..."
            # j5xlte
            echo "----------------------------------------------"
            echo "Cleaning up source..."
            echo " "
            CLEAN_SOURCE
            echo " "
            echo "----------------------------------------------"
            echo "Starting j5xlte kernel build..."
            RV_VARIANT=j5xlte
            RV_DEFCON=msm8916_sec_j5xlte_defconfig
            BUILD_ZIMAGE
            BUILD_DTB
            PACK_VARIANT_IMG
            echo " "
            echo "----------------------------------------------"
            echo "j5xlte kernel build finished."
            PACK_J5XLTE_ZIP
            echo " "
            echo "----------------------------------------------"
            echo "J5 2016 kernels build finished."
            echo "Flashable zip is located into RV/build."
            echo "Press any key for end the script."
            echo "----------------------------------------------"
            read -n1 -r key
            break
            ;;
        "Exit")
            break
            ;;
        *) echo Invalid option.;;
    esac
done


