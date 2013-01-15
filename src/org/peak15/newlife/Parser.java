package org.peak15.newlife;

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
	 * 
	 * @param first the first token of the statement, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed statement
	 * @throws NewLifeParserException upon encountering a syntax error
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
	 * 
	 * @param first the first token of the block, already pulled out.
	 * @param tokenizer to parse from
	 * @return the parsed block
	 * @throws NewLifeParserException upon encountering a syntax error
	 */
	public static Statement parseBlock(Token first, Tokenizer tokenizer) throws NewLifeParserException {
		Token t = first;
		
		while(t.getType() == TokenType.IDENTIFIER
				|| t.getText().equals("IF")
				|| t.getText().equals("WHILE")) {
			
			//
		}
		
		return null;
	}
	
	/**
	 * @param t token to test
	 * @return true if the statement represented by the token is
	 *         an instruction call, IF(ELSE), or WHILE statement.
	 */
	private static boolean isPrimitiveStatement(Token t) {
		return ;
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
