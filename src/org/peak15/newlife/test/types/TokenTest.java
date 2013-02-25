package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.Type;

public class TokenTest extends ValueTypeTest<Token> {
	
	@Override
	protected Token A() {
		return new Token(Type.KEYWORD, "DO");
	}

	@Override
	protected Token D() {
		return new Token(Type.IDENTIFIER, "blarg");
	}
	
	@Test
	public void testGetType() {
		assertEquals(Type.KEYWORD, a.type());
	}

	@Test
	public void testGetText() {
		assertEquals("DO", a.text());
	}
}
