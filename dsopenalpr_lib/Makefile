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
	
PKGS = glib-2.0 
LIBS = -lopenalpr -lalprstream -lvehicleclassifier -lalpropencvgpu
SOURCES = dsopenalpr_lib.c openalprimpl.cpp

OBJECTS_TMP=$(SOURCES:.cpp=.o)
OBJECTS=$(OBJECTS_TMP:.c=.o)
	
CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_LIBDIR) pkg-config --cflags $(PKGS)) -Wall -fPIC  -I/usr/include/alpropencvgpu/
CXXFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_LIBDIR) pkg-config --cflags $(PKGS)) -fPIC -I/usr/include/alpropencvgpu/
LDFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_LIBDIR) pkg-config --libs $(PKGS))


all:	print_vars libdsopenalpr.a

print_vars:
	# echo "CXXFlags: " $(CXXFLAGS) 
	# echo "LIBS: " $(LIBS) 
	# echo "LDFLAGS: " $(LDFLAGS) 

libdsopenalpr.a: $(OBJECTS)

	ar rcs libdsopenalpr.a $(OBJECTS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(LIBS) $(LDFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS)  $(LDFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) *.o *.a core
