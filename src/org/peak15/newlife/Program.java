package org.peak15.newlife;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.peak15.newlife.Token.TokenType;

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
	 * @throws IOException if the tokenizer fails to read
	 */
	public Program(Tokenizer tokenizer) throws NewLifeParserException {
		
		//TODO: figure out the craziniess about what exactly each parser "pops off"
		
		this.context = new HashMap<String, Statement>();
		
		Token t;
		try {
			// PROGRAM
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("PROGRAM"),
					"Expected program to begin with \"PROGRAM\"");
			
			// program name
			t = tokenizer.nextToken();
			assertCode(t.getType() == TokenType.IDENTIFIER,
					"Expected valid identifier for program name.");
			this.name = t.getText();
			
			// IS
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("IS"),
					"Expected \"IS\" to follow program name.");
			
			// parse instructions (if any)
			t = tokenizer.nextToken(); // this could be BEGIN
			
			// go until we reach BEGIN
			while(!t.getText().equals("BEGIN")) {
				assertCode(t.getText().equals("INSTRUCTION"), "Malformed instruction definition.");
				
				Map.Entry<String, Statement> pair = parseInstruction(tokenizer);
				this.context.put(pair.getKey(), pair.getValue());
				
				// get next token (next instruction or BEGIN)
				t = tokenizer.nextToken();
			}
			
			// BEGIN
			assertCode(t.getText().equals("BEGIN"),
					"Expected \"BEGIN\" after possible instruction definitions.");
			
			// get the next token for parseBlock
			t = tokenizer.nextToken();
			// parse body and add to program
			body = new Statement(tokenizer, true);
			
			// END already pulled out in parseBlock
			
			
		} catch(IOException e) {
			throw new NewLifeParserException(e);
		}
		
	}
	
	/**
	 * Parses an instruction from the tokenizer into a BLOCK statement.
	 * 
	 * @param tokenizer to parse from
	 * @return pair of the name and the block of the parsed instruction
	 */
	private static Map.Entry<String, Statement> parseInstruction(Tokenizer tokenizer) {
		// TODO Auto-generated method stub
		return null;
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
	
	/**
	 * Checks the specified condition, and throws an exception if it is false.
	 * 
	 * @param expectedTrueCond condition expected to be true
	 * @param failMsg Message to print if the condition is false.
	 * @throws NewLifeParserException If the condition is false.
	 */
	private static void assertCode(boolean expectedTrueCond, String failMsg)
			throws NewLifeParserException {
		if(!expectedTrueCond)
			throw new NewLifeParserException(failMsg);
	}
}
