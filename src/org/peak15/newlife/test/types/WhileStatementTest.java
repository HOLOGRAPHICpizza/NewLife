package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.statement.WhileStatement;
import org.peak15.newlife.types.statement.Statement.Condition;

public class WhileStatementTest extends ValueTypeTest<WhileStatement> {
	
	@Override
	protected WhileStatement A() {
		return new WhileStatement(Condition.RANDOM, BlockStatementTest.compoundBlock());
	}

	@Override
	protected WhileStatement D() {
		return new WhileStatement(Condition.TRUE, BlockStatementTest.EXPLODE_BLOCK);
	}
	
	@Test
	public void testGetCondition() {
		assertEquals(Condition.TRUE, d.condition());
	}
	
	@Test
	public void testGetBody() {
		assertEquals(BlockStatementTest.compoundBlock(), a.body());
	}
}
