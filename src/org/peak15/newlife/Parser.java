package org.peak15.newlife;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import org.peak15.newlife.types.BlockStatement;
import org.peak15.newlife.types.CallStatement;
import org.peak15.newlife.types.IfElseStatement;
import org.peak15.newlife.types.Program;
import org.peak15.newlife.types.Statement;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.TokenType;
import org.peak15.newlife.types.WhileStatement;

/**
 * Parses tokens into abstract statements and programs.
 */
public final class Parser {
	/**
	 * Parse an instruction call, IF(ELSE), or WHILE statement.
	 * Can not parse blocks.
	 * Parses precisely the tokens which form the statement, and no more.
	 * 
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed statement
	 * @throws NewLifeParserException upon encountering an error
	 */
	public static Statement parseStatement(Token first, Tokenizer tokenizer) throws NewLifeParserException {
		if(first == null || tokenizer == null) {
			throw new NullPointerException("No paramenters may be null.");
		}
		
		Statement s = null;
		
		if(first.getType() == TokenType.IDENTIFIER) {
			// CALL
			s = new CallStatement(first.getText());
		}
		else if(first.getText().equals("IF")) {
			// IF(ELSE)
			s = parseIf(first, tokenizer);
		}
		else if(first.getText().equals("WHILE")) {
			// WHILE
			s = parseWhile(first, tokenizer);
		}
		else {
			assertCode(false, "Expected instruction call, IF, or WHILE.");
		}
		
		return s;
	}
	
	/**
	 * Parse a block.
	 * Parses precisely the tokens which form the block, and no more.
	 * 
	 * @param first the first token of the block, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed block
	 * @throws NewLifeParserException upon encountering an error
	 */
	public static BlockStatement parseBlock(Token first, Tokenizer tokenizer) throws NewLifeParserException {
		if(first == null || tokenizer == null) {
			throw new NullPointerException("No paramenters may be null.");
		}
		
		BlockStatement s;
		
		try {
			Token t = first;
			BlockStatement.Builder bb = new BlockStatement.Builder();
			
			while(isPrimitiveStatement(t)) {
				bb.append(parseStatement(t, tokenizer));
				
				// if the next token is part of the block, pull it out
				if(isPrimitiveStatement(tokenizer.peekNextToken())) {
					t = tokenizer.nextToken();
				}
				else {
					t = tokenizer.peekNextToken();
				}
			}
			
			s = bb.build();
		} catch(IOException e) {
			throw new NewLifeParserException("Read error while parsing block.", e);
		}
		
		return s;
	}
	
	/**
	 * Parse a program.
	 * Parses precisely the tokens which form the program, and no more.
	 * 
	 * @param first the first token of the program, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed program
	 * @throws NewLifeParserException upon encountering an error
	 */
	public static Program parseProgram(Token first, Tokenizer tokenizer) throws NewLifeParserException {
		String name;
		Map<String, BlockStatement> context = new HashMap<>();
		BlockStatement body;
		Token t = first;
		
		try {
			// PROGRAM
			assertCode(t.getText().equals("PROGRAM"),
					"Expected program to begin with \"PROGRAM\"");
			
			// program name
			t = tokenizer.nextToken();
			assertCode(t.getType() == TokenType.IDENTIFIER,
					"Expected valid identifier for program name.");
			name = t.getText();
			
			// IS
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("IS"),
					"Expected \"IS\" to follow program name.");
			
			// parse instructions (if any)
			t = tokenizer.nextToken(); // this could be BEGIN
			
			// go until we reach BEGIN
			while(!t.getText().equals("BEGIN")) {
				assertCode(t.getText().equals("INSTRUCTION"), "Malformed instruction definition.");
				
				NamedBlockStatement pair = parseInstruction(tokenizer, context.keySet());
				context.put(pair.name, pair.statement);
				
				// get next token (next instruction or BEGIN)
				t = tokenizer.nextToken();
			}
			
			// BEGIN
			assertCode(t.getText().equals("BEGIN"),
					"Expected \"BEGIN\" after possible instruction definitions.");
			
			
			// parse body and add to program
			t = tokenizer.nextToken();
			body = parseBlock(t, tokenizer);
			
			// END
			t = tokenizer.nextToken();
			assertCode(t.getText().equals("END"),
					"Expected \"END\" to follow program body.");
			
			// name again
			t = tokenizer.nextToken();
			assertCode(t.getText().equals(name),
					"Expected program name to follow entire program.");
			
		} catch(IOException e) {
			throw new NewLifeParserException("Read error while parsing program.", e);
		}
		
		return new Program(name, context, body);
	}
	
	/**
	 * For use in passing pairs for the context.
	 */
	private final static class NamedBlockStatement {
		public final String name;
		public final BlockStatement statement;
		
		public NamedBlockStatement(String name, BlockStatement statement) {
			this.name = name;
			this.statement = statement;
		}
	}
	
	/**
	 * @param t token to test
	 * @return true if the blargStatement represented by the token is
	 *         an instruction call, IF(ELSE), or WHILE blargStatement.
	 */
	private static boolean isPrimitiveStatement(Token t) {
		return t.getType() == TokenType.IDENTIFIER
				|| t.getText().equals("IF")
				|| t.getText().equals("WHILE");
	}

	/**
	 * Parses an instruction definition into a named block statement.
	 * 
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @param takenNames instruction names that have already been used.
	 * @return pair of the name and the block of the parsed instruction
	 * @throws IOException if the parser fails to read
	 * @throws NewLifeParserException upon encountering a syntax error
	 */
	private static NamedBlockStatement parseInstruction (
			Tokenizer tokenizer,
			Set<String> takenNames)
			throws IOException, NewLifeParserException {
		
		Token t;
		
		// instruction name
		t = tokenizer.nextToken();
		String instName = t.getText();
		assertCode(t.getType() == TokenType.IDENTIFIER,
				"Expected valid identifier for instruction name.");
		assertCode(!takenNames.contains(instName),
				"Expected a unique instruction name (a name was repeated).");
		
		// IS
		t = tokenizer.nextToken();
		assertCode(t.getText().equals("IS"),
				"Expected \"IS\" to follow instruction name.");
		
		// body
		t = tokenizer.nextToken();
		BlockStatement s = parseBlock(t, tokenizer);
		
		// END
		t = tokenizer.nextToken();
		assertCode(t.getText().equals("END"),
				"Expected \"END\" to follow instruction body.");
		
		// name again
		t = tokenizer.nextToken();
		assertCode(t.getText().equals(instName),
				"Expected instruction name to follow instruction definition.");
		
		return new NamedBlockStatement(instName, s);
	}

	/**
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return parsed IF(ELSE) blargStatement
	 */
	private static IfElseStatement parseIf(Token first, Tokenizer tokenizer) {
		return null;
	}
	
	/**
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return parsed WHILE statement
	 */
	private static WhileStatement parseWhile(Token first, Tokenizer tokenizer) {
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
