/*
 * Archive.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Virtual Machine.
 * 
 * Dubbel Virtual Machine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Virtual Machine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include "Dubbel.h"

using namespace std;
using namespace dubbel;

dubbel::Archive::Archive(const String & content) {
	Parse(content);
}

void dubbel::Archive::Parse(const String & content) {
	LSize ms = BuildLSize(content[0], content[1], content[2], content[3]);
	mainName = "";
	LSize i;
	for(i = 4; i < ms+4; ++i)
		mainName += content[i];
	for( ; i < content.size(); ++i) {
		LSize s = BuildLSize(content[i], content[i+1], content[i+2], content[i+3]);
		i += 4;
		String name;
		for(LSize j = 0; j < s; ++j, ++i)
			name += content[i];
		fileNames.push_back(name);
		s = BuildLSize(content[i], content[i+1], content[i+2], content[i+3]);
		i += 4;
		String bin;
		for(LSize j = 0; j < s; ++j, ++i)
			bin += content[i];
		fileContents.push_back(bin);
		--i;
	}
}

String bytesSize(LSize t) {
	String b = "";
	b += (t >> 24) & 0xFF;
	b += (t >> 16) & 0xFF;
	b += (t >> 8) & 0xFF;
	b += t & 0xFF;
	return b;
}


String dubbel::Archive::Build() {
	String build = bytesSize(mainName.size());
	build += mainName;
	for(size_t i = 0; i < fileContents.size(); ++i) {
		build += bytesSize(fileNames[i].size());
		build += fileNames[i];
		build += bytesSize(fileContents[i].size());
		build += fileContents[i];
	}
	return build;
}




