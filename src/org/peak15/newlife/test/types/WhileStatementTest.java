package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.Statement.Condition;
import org.peak15.newlife.types.WhileStatement;

public class WhileStatementTest extends ValueTypeTest<WhileStatement> {
	
	@Override
	protected WhileStatement A() {
		return new WhileStatement(Condition.RANDOM, BlockStatementTest.COMPOUND_BLOCK());
	}

	@Override
	protected WhileStatement D() {
		return new WhileStatement(Condition.TRUE, BlockStatementTest.EXPLODE_BLOCK);
	}
	
	@Test
	public void testGetCondition() {
		assertEquals(Condition.TRUE, d.getCondition());
	}
	
	@Test
	public void testGetBody() {
		assertEquals(BlockStatementTest.COMPOUND_BLOCK(), a.getBody());
	}
}
