package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.TokenType;

public final class TokenTest extends ValueTypeTest<Token> {
	
	@Override
	protected Token A() {
		return new Token(TokenType.COMMENT, "blarg");
	}

	@Override
	protected Token D() {
		return new Token(TokenType.IDENTIFIER, "blarg");
	}
	
	@Test
	public void testGetType() {
		assertEquals(TokenType.COMMENT, a.getType());
	}

	@Test
	public void testGetText() {
		assertEquals(TokenType.COMMENT, a.getType());
	}
}
