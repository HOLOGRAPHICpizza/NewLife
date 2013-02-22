package org.peak15.newlife.test.types;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

/**
 * Template for tests on value types.
 * Includes tests for equals, hashCode, and toString.
 * 
 * A and D should construct new objects s.t. A /= B
 * 
 * A and D should not be used by the implementing class.
 * 
 * a-c will be populated from A().
 * d will be populated from D().
 *
 * @param <T> type to test
 */
public abstract class ValueTypeTest<T> {

	protected final T a = A();
	protected final T b = A();
	protected final T c = A();
	protected final T d = D();
	protected final int aHash = a.hashCode();
	protected final boolean ABEqual = a.equals(b);

	abstract protected T A();
	abstract protected T D();

	@Test
	public void consistentHashCode() {
		assertEquals(aHash, a.hashCode());
	}

	@Test
	public void equalHashCode() {
		assertEquals(a.hashCode(), b.hashCode());
	}

	@Test
	public void reflexiveEquals() {
		assertTrue("x.equals(x) == true", a.equals(a));
		assertTrue("x.equals(x) == true", a.equals(b));
	}

	@Test
	public void symmetricEquals() {
		// equal test
		assertEquals("x.equals(y) iff y.equals(x)", a.equals(b), a.equals(b));
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