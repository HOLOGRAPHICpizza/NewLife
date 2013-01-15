package org.peak15.newlife;

import org.peak15.newlife.types.Program;

/**
 * Turns Programs into compiled binaries.
 */
public class Compiler {
	public static final byte MOVE = 0x00;
	public static final byte TURNLEFT = 0x01;
	public static final byte TURNRIGHT = 0x02;
	public static final byte INFECT = 0x03;
	public static final byte SKIP = 0x04;
	public static final byte HALT = 0x05;
	public static final byte JUMP = 0x06;
	public static final byte JUMP_IF_NOT_NEXT_IS_EMPTY = 0x07;
	public static final byte JUMP_IF_NOT_NEXT_IS_NOT_EMPTY = 0x08;
	public static final byte JUMP_IF_NOT_NEXT_IS_WALL = 0x09;
	public static final byte JUMP_IF_NOT_NEXT_IS_NOT_WALL = 0x0A;
	public static final byte JUMP_IF_NOT_NEXT_IS_FRIEND = 0x0B;
	public static final byte JUMP_IF_NOT_NEXT_IS_NOT_FRIEND = 0x0C;
	public static final byte JUMP_IF_NOT_NEXT_IS_ENEMY = 0x0D;
	public static final byte JUMP_IF_NOT_NEXT_IS_NOT_ENEMY = 0x0E;
	public static final byte JUMP_IF_NOT_RANDOM = 0x0F;
	public static final byte JUMP_IF_NOT_TRUE = 0x10;
	
	/**
	 * @param program to compile
	 * @return the compiled byte array
	 */
	public static byte[] compile(Program program) {
		//TODO: Implement.
		return null;
	}
}
