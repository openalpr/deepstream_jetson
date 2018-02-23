################################################################################
# Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
#
# NVIDIA Corporation and its licensors retain all intellectual property
# and proprietary rights in and to this software, related documentation
# and any modifications thereto.  Any use, reproduction, disclosure or
# distribution of this software and related documentation without an express
# license agreement from NVIDIA Corporation is strictly prohibited.
#
################################################################################

all:
	gcc -c -o dsopenalpr_lib.o -fPIC dsopenalpr_lib.c `pkg-config --cflags glib-2.0`
	ar rcs libdsopenalpr.a dsopenalpr_lib.o
