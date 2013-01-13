package org.peak15.newlife.test;

import static org.junit.Assert.*;

import java.io.IOException;
import java.io.StringReader;
import org.junit.Test;
import org.peak15.newlife.Token;
import org.peak15.newlife.Tokenizer;
import org.peak15.newlife.Token.TokenType;

public class TokenizerTest {
	
	private static final String TEST_STRING = "blarg blarg\ntaco";
	
	private final Tokenizer tokenizer = new Tokenizer(new StringReader(TEST_STRING));
	
	@Test
	public void testNextToken() throws IOException {
		Token[] tokens = new Token[4];
		for(int i=0; i < tokens.length; i++) {
			tokens[i] = tokenizer.nextToken();
		}
		
		assertEquals("1:", "blarg", tokens[0].getText());
		assertEquals("2:", "blarg", tokens[1].getText());
		assertEquals("3:", "taco", tokens[2].getText());
		assertEquals("EOF:", TokenType.EOF_TOKEN, tokens[3].getType());
	}

}
