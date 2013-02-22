package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.CallStatement;

public class CallStatementTest extends ValueTypeTest<CallStatement> {
	
	@Test
	public void testGetCall() {
		assertEquals("explode", a.getCall());
	}
	
	@Override
	protected CallStatement A() {
		return new CallStatement("explode");
	}

	@Override
	protected CallStatement D() {
		return new CallStatement("infect");
	}
}
