package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.Type;

public final class TokenTest extends ValueTypeTest<Token> {
	
	@Override
	protected Token A() {
		return new Token(Type.COMMENT, "blarg");
	}

	@Override
	protected Token D() {
		return new Token(Type.IDENTIFIER, "blarg");
	}
	
	@Test
	public void testGetType() {
		assertEquals(Type.COMMENT, a.getType());
	}

	@Test
	public void testGetText() {
		assertEquals(Type.COMMENT, a.getType());
	}
}
