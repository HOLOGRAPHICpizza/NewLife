package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.Token;
import org.peak15.newlife.types.Token.TokenType;

public final class TokenTest {

	private final Token a = new Token(TokenType.COMMENT, "blarg");
	private final int aHash = a.hashCode();
	private final Token b = new Token(TokenType.COMMENT, "blarg");
	private final boolean ABEqual = a.equals(b);
	private final Token d = new Token(TokenType.IDENTIFIER, "blarg");
	private final Token c = new Token(TokenType.COMMENT, "blarg");

	@Test
	public void consistentHashCode() {
		assertEquals(aHash, a.hashCode());
	}
	
	@Test
	public void equalHashCode() {
		assertEquals(a.hashCode(), b.hashCode());
	}

	@Test
	public void testGetType() {
		assertEquals(TokenType.COMMENT, a.getType());
	}

	@Test
	public void testGetText() {
		assertEquals(TokenType.COMMENT, a.getType());
	}

	@Test
	public void reflexiveEquals() {
		assertTrue("x.equals(x) == true", a.equals(a));
	}
	
	@Test
	public void symmetricEquals() {
		// equal test
		assertEquals("x.equals(y) iff y.equals(x)", a.equals(b), b.equals(a));
		// unequal test
		assertEquals("x.equals(y) iff y.equals(x)", a.equals(d), d.equals(a));
	}
	
	@Test
	public void transitiveEquals() {
		assertEquals("if x.equals(y) && y.equals(z), then x.equals(z)",
				a.equals(b) && b.equals(c),
				a.equals(c));
	}
	
	@Test
	public void consistentEquals() {
		assertEquals(ABEqual, a.equals(b));
	}
	
	/**
	 * This test always succeeds,
	 * it exists to allow visual inspection of
	 * the non explicitly defined toString() output.
	 */
	@Test
	public void testToString() {
		System.out.println(a.toString());
	}
}
