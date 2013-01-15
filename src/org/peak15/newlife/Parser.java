package org.peak15.newlife;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import org.peak15.newlife.types.Statement;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.TokenType;

/**
 * Parses tokens into abstract statements and programs.
 */
public class Parser {
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
		Statement s = null;
		
		if(first.getType() == TokenType.IDENTIFIER) {
			// CALL
			s = new Statement(first.getText());
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
	 * Parse a BLOCK.
	 * NOTE: Parses one extra token past the end of the block.
	 * 
	 * @param first the first token of the block, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed block
	 * @throws NewLifeParserException upon encountering an error
	 */
	public static Statement parseBlock(Token first, Tokenizer tokenizer) throws NewLifeParserException {
		Statement s;
		
		try {
			Token t = first;
			List<Statement> statements = new LinkedList<Statement>();
			
			while(isPrimitiveStatement(t)) {
				statements.add(parseStatement(t, tokenizer));
				t = tokenizer.nextToken();
			}
			
			s = new Statement(statements);
		} catch(IOException e) {
			throw new NewLifeParserException("Read error while parsing block.", e);
		}
		
		return s;
	}
	
	public static Program parseProgram;
	
	/**
	 * @param t token to test
	 * @return true if the statement represented by the token is
	 *         an instruction call, IF(ELSE), or WHILE statement.
	 */
	private static boolean isPrimitiveStatement(Token t) {
		return t.getType() == TokenType.IDENTIFIER
				|| t.getText().equals("IF")
				|| t.getText().equals("WHILE");
	}
	
	/**
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return parsed IF(ELSE) statement
	 */
	private static Statement parseIf(Token first, Tokenizer tokenizer) {
		return null;
	}
	
	/**
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return parsed WHILE statement
	 */
	private static Statement parseWhile(Token first, Tokenizer tokenizer) {
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
