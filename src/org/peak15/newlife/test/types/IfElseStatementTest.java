package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import org.junit.Test;
import org.peak15.newlife.types.statement.IfElseStatement;
import org.peak15.newlife.types.statement.Statement.Condition;

public class IfElseStatementTest extends ValueTypeTest<IfElseStatement> {
	
	@Override
	protected IfElseStatement A() {
		return new IfElseStatement(
				Condition.RANDOM,
				BlockStatementTest.EXPLODE_BLOCK,
				BlockStatementTest.INFECT_BLOCK);
	}

	@Override
	protected IfElseStatement D() {
		return new IfElseStatement(Condition.TRUE, BlockStatementTest.compoundBlock());
	}
	
	@Test
	public void testGetCondition() {
		assertEquals(Condition.RANDOM, a.getCondition());
	}
	
	@Test
	public void testGetBody() {
		assertEquals(BlockStatementTest.compoundBlock(), d.getBody());
	}
	
	@Test
	public void testGetElseBody() {
		assertEquals(BlockStatementTest.INFECT_BLOCK, a.getElseBody());
	}
}
