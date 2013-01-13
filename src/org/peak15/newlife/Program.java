package org.peak15.newlife;

import java.util.HashMap;
import java.util.Map;

/**
 * One abstract program.
 * 
 * Immutable.
 */
public final class Program {
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
	
	private final String name;
	private final Map<String, Statement> context;
	private final Statement body;
	
	private byte[] compiledBytes = null;
	
	public Program(String name, Map<String, Statement> context, Statement body) {
		this.name = name;
		this.context = new HashMap<String, Statement>(context);
		this.body = body;
	}
	
	/**
	 * Parse a program from a tokenizer.
	 * 
	 * @param tokenizer to parse from.
	 */
	public Program(Tokenizer tokenizer) {
		//TODO: Implement.
		this.name = null;
		this.context = null;
		this.body = null;
	}
	
	/**
	 * Compiles the program and returns the compiled byte array.
	 * 
	 * @return the compiled byte array.
	 */
	public byte[] getCompiledBytes() {
		//TODO: Implement.
		return null;
	}
}
