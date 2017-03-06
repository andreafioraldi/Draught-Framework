/*
 * DubbelAssembler.h
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

#pragma once

#include "DubbelBuilder.h"
#include <map>

#ifdef _WIN32
#ifdef DubbelAssembler_EXPORTS
#define DUBBEL_ASSEMBLER_API __declspec(dllexport)
#else
#define DUBBEL_ASSEMBLER_API __declspec(dllimport)
#endif
#else
#define DUBBEL_ASSEMBLER_API
#endif

namespace dubbel {

	/**
	 * Use a buffer to convert a size_t in a string
	 * @param i the number to convert
	 * @return return the converted string 
	 */
	DUBBEL_ASSEMBLER_API String size_tToStr(size_t i);
	
	/**
	 * Use a buffer to convert a decimal string in a 16 bit number (SSize)
	 * @param s the string to convert
	 * @return return the converted number
	 */
	DUBBEL_ASSEMBLER_API SSize StringToSSize(const String & s);
	
	/**
	 * Use a buffer to convert a hexadecimal string in a 16 bit number (SSize)
	 * @param s the string to convert
	 * @return return the converted number
	 */
	SSize HexToSSize(const String & s);
	
	/**
	 * Use a buffer to convert a octal string in a 16 bit number (SSize)
	 * @param s the string to convert
	 * @return return the converted number
	 */
	DUBBEL_ASSEMBLER_API SSize OctToSSize(const String & s);
	
	/**
	 * Use a buffer to convert a decimal string in a 32 bit number (LSize)
	 * @param s the string to convert
	 * @return return the converted number
	 */
	DUBBEL_ASSEMBLER_API LSize StringToLSize(const String & s);

	/**
	 * Enum with the different types of Line
	 */
	enum class LineType : Char {
		Default, /**< default assembly line type */
		Const, /**< an assembly line that represent an instruction related with the constant pool */
		Label /**< a label , is not an instruction */
	};


	/**
	 * This struct represents an assembly line
	 */
	struct DUBBEL_ASSEMBLER_API Line {
		std::vector<String> words; /**< the words of the line*/
		size_t index = 0; /**< the position in the source code */
		LineType type = LineType::Default; /**< the line type */
	};


	/**
	 * Split a string into words by spaces and solve string special characters
	 * @param s the string to split
	 * @return return the words
	 */
	DUBBEL_ASSEMBLER_API std::vector<String> SplitLine(const String & s);


	/**
	 * Get a list of lines from the source code
	 * @param code the source code
	 * @return return a list of lines
	 */
	DUBBEL_ASSEMBLER_API std::vector<Line> ScanLines(const String & code);

	/**
	 * This struct is used to report assembler error in the exception handling
	 */
	struct DUBBEL_ASSEMBLER_API AssemblerErr {
		String err; /**< the description of the error */

		/**
		 * The constructor of AssemblerErr
		 * @param e the error string
		 */
		AssemblerErr(String e) : err("Assembler error : " + e) {}
	};


	/**
	 * This struct translate an assembly source code into usable bytecode for the Dubble VM
	 */
	struct DUBBEL_ASSEMBLER_API Assembler {
		InstrList list; /**< the list of instruction translated from the source code */
		std::map<String , size_t> labels; /**< the labels */
		String fileHead = ""; /**< the head of a file that descibe the main object */
		
		/**
		 * Compile assembly code into instructions
		 * @param code the source code
		 */
		void Compile(const String & code);

		/**
		 * Compile a list of lines into instructions
		 * @param lines the list of lines
		 */
		void Compile(const std::vector<Line> & lines);

		/**
		 * Translate a list of lines into instructions without solving labels
		 * @param lines the list of lines
		 */
		void Translate(const std::vector<Line> & lines);

		/**
		 * Check if a label is declared
		 * @param name the name of the label
		 */
		bool LabelExist(const String & name);

		/**
		 * Substitute all labels in the instruction list with the corrispondent bytecode index
		 */
		void SolveLabels();
		
		/**
		 * Append a block of instructions to the instruction list
		 * @param l the block
		 */
		void AddBlock(const InstrList & l);

		/**
		 * Generate a binary string that contains the bytecode of this instance as main object
		 * @return the binary string that is the content of a .dubbel file
		 */
		String GetBytecode();
	};

}

