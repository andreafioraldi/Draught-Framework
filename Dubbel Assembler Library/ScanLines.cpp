/*
 * ScanLines.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Assembler Library.
 * 
 * Dubbel Assembler Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Assembler Library is distributed in the hope that it will be useful,
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
 
 #include "DubbelAssembler.h"

using namespace std;
using namespace dubbel;

vector<String> dubbel::SplitLine(const String & s) {
	vector<String> v;
	String tmp = "";
	bool inString = false;
	bool inComment = false;
	for(size_t i = 0; i < s.size(); ++i) {
		if(s[i] != ' ' && s[i] != '\t' && !inString && !inComment) {
			if(s[i] == '\"') {
				inString = true;
			}
			else if(s[i] == '[') {
				inComment = true;
			}
			else if(s[i] == '/' && i < s.size() -1 && s[i+1] == '/') {
				break;
			}
			else tmp += s[i];
		}
		else if(inString) {
			if(s[i-1] == '\\' && s[i] == '\\');
			else if(s[i-1] == '\\' && s[i] == '\"') tmp[tmp.size()-1] = '\"';
			else if(s[i-1] == '\\' && s[i] == 'n') tmp[tmp.size()-1] = '\n';
			else if(s[i-1] == '\\' && s[i] == 't') tmp[tmp.size()-1] = '\t';
			else if(s[i-1] == '\\' && s[i] == 'b') tmp[tmp.size()-1] = '\b';
			else if(s[i-1] == '\\' && s[i] == 'r') tmp[tmp.size()-1] = '\r';
			else if(s[i-1] == '\\' && s[i] == 'v') tmp[tmp.size()-1] = '\v';
			else if(s[i-1] == '\\' && s[i] == 'd') {
				if(i < s.size()-3) {
					String n;
					n += s[i+1];
					n += s[i+2];
					n += s[i+3];
					tmp[tmp.size()-1] = (Char)StringToSSize(n);
					i += 3;
				}
			}
			else if(s[i-1] == '\\' && s[i] == 'x') {
				if(i < s.size()-2) {
					String n;
					n += s[i+1];
					n += s[i+2];
					tmp[tmp.size()-1] = (Char)HexToSSize(n);
					i += 2;
				}
			}
			else if(s[i-1] == '\\' && s[i] >= '0' && s[i] <= '9') {
				if(i < s.size()-1) {
					String n;
					n += s[i];
					n += s[i+1];
					tmp[tmp.size()-1] = (Char)OctToSSize(n);
					i += 1;
				}
			}
			else if(s[i] == '\"') {
				inString = false;
				if(tmp == "")
					v.push_back("");
				continue;
			}
			else tmp += s[i];
		}
		else if(inComment) {
			if(s[i] == ']') {
				inComment = false;
				continue;
			}
		}
		else {
			if(tmp == "")
				continue;
			v.push_back(tmp);
			tmp = "";
		}

	}
	if(tmp != "")
		v.push_back(tmp);
	return v;
}


vector<Line> dubbel::ScanLines(const String & code) {
	vector<Line> lines;
	String tmp = "";
	for(size_t i = 0; i < code.size(); ++i) {
		if(code[i] != '\n') {
			tmp += code[i];
		}
		else {
			if(tmp == "")
				continue;
			Line l;
			l.words = SplitLine(tmp);
			if(l.words.size() != 0) {
				l.index = lines.size()+1;
				if(l.words[0][0] == ':')
					l.type = LineType::Label;
				else if(l.words[0][0] == '$')
					l.type = LineType::Const;
				if(l.type != LineType::Label) {
					for(size_t j = 0; j < l.words[0].size(); ++j)
						l.words[0][j] = toupper(l.words[0][j]);
				}
				lines.push_back(l);
			}
			tmp = "";
		}
	}
	if(tmp != "") {
		Line l;
		l.words = SplitLine(tmp);
		if(l.words.size() != 0) {
			l.index = lines.size()+1;
			if(l.words[0][0] == ':')
				l.type = LineType::Label;
			else if(l.words[0][0] == '$')
				l.type = LineType::Const;
			if(l.type != LineType::Label) {
				for(size_t j = 0; j < l.words[0].size(); ++j)
					l.words[0][j] = toupper(l.words[0][j]);
			}
			lines.push_back(l);
		}
	}
	return lines;
}




