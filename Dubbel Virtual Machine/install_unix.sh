#!/bin/sh

# install_unix.sh
# 
# Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
# 
# This file is part of Dubbel Virtual Machine.
# 
# Dubbel Virtual Machine is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# Dubbel Virtual Machine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.


if test -e /etc/environment; then
	cat /etc/environment > /etc/environment.bak
	sed -n '/DUBBEL_LIBPATH=/!p' /etc/environment > /etc/environment.new
	mv /etc/environment.new /etc/environment
	echo "DUBBEL_LIBPATH=\"$1/lib\"" >> /etc/environment
	echo ' *** DUBBEL_LIBPATH added to /etc/environment, relogin to update the environment. ***'
elif test -d /etc/profile.d; then
	echo "export DUBBEL_LIBPATH=\"$1/lib\"" > /etc/profile.d/dubbel_libpath.sh
elif test -e /etc/profile; then
	cat /etc/profile > /etc/profile.bak
	sed -n '/export DUBBEL_LIBPATH=/!p' /etc/profile > /etc/profile.new
	mv /etc/profile.new /etc/profile
	echo "export DUBBEL_LIBPATH=\"$1/lib\"" >> /etc/profile
elif test -e /etc/bash.bashrc; then
	cat /etc/bash.bashrc > /etc/bash.bashrc.bak
	sed -n '/export DUBBEL_LIBPATH=/!p' /etc/bash.bashrc
	sed -n '/export DUBBEL_LIBPATH=/!p' /etc/bash.bashrc > /etc/bash.bashrc.new
	mv /etc/bash.bashrc.new /etc/bash.bashrc
	echo "export DUBBEL_LIBPATH=\"$1/lib\"" >> /etc/bash.bashrc
	echo ' !!! WARNING: DUBBEL_LIBPATH added to /etc/bash.bashrc, so now only the bash shell provides full support to dubbel. Consider to add manually `export DUBBEL_LIBPATH=\"$1/lib\"` to /etc/profile. !!!'
else
	echo ' !!! WARNING: export DUBBEL_LIBPATH=\"$1/lib\" failed, do it manually. !!!'
fi


