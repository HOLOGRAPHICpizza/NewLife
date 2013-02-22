package org.peak15.newlife.test;

import static org.junit.Assert.*;

import java.io.IOException;
import java.io.StringReader;
import org.junit.Test;
import org.peak15.newlife.Tokenizer;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.Type;

public class TokenizerTest {
	
	private static final String TEST_STRING = "PROGRAM test IS\n"
			+ "\tINSTRUCTION blarg IS\n"
			+ "\t\tIF random THEN turnright END IF\n"
			+ "!!&^%%%\n"
			+ "# comment\n"
			+ "\tEND blarg\n"
			+ "BEGIN"
			+ "\tblarg"
			+ "END test";
	private static final int TOKEN_COUNT = 20;
	
	@Test
	public void testNextToken() throws IOException {
		Tokenizer tokenizer = new Tokenizer(new StringReader(TEST_STRING));
		
		Token[] tokens = new Token[TOKEN_COUNT];
		for(int i=0; i < tokens.length; i++) {
			tokens[i] = tokenizer.nextToken();
		}
		
		assertEquals("1:", Type.KEYWORD, tokens[0].type());
		assertEquals("2:", Type.IDENTIFIER, tokens[1].type());
		assertEquals("3:", Type.KEYWORD, tokens[2].type());
		assertEquals("4 type:", Type.KEYWORD, tokens[3].type());
		assertEquals("4 text:", "INSTRUCTION", tokens[3].text());
		assertEquals("8:", Type.CONDITION, tokens[7].type());
		assertEquals("13:", Type.ERROR, tokens[12].type());
		assertEquals("14:", Type.COMMENT, tokens[13].type());
		assertEquals("EOF:", Type.EOF_TOKEN, tokens[TOKEN_COUNT - 1].type());
	}
	
	@Test
	public void testPeekNextToken() throws IOException {
		Tokenizer tokenizer = new Tokenizer(new StringReader(TEST_STRING));
		
		assertEquals("1:", Type.KEYWORD, tokenizer.nextToken().type());
		assertEquals("2 peek:", Type.IDENTIFIER, tokenizer.peekNextToken().type());
		assertEquals("2 peek2:", Type.IDENTIFIER, tokenizer.peekNextToken().type());
		assertEquals("2:", Type.IDENTIFIER, tokenizer.nextToken().type());
		assertEquals("3:", Type.KEYWORD, tokenizer.nextToken().type());
	}

}
