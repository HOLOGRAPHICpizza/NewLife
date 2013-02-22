package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.List;

import org.junit.Test;
import org.peak15.newlife.types.BlockStatement;
import org.peak15.newlife.types.CallStatement;
import org.peak15.newlife.types.Statement;

public class BlockStatementTest extends ValueTypeTest<BlockStatement> {
	
	private static final BlockStatement explodeBlock =
			new BlockStatement.Builder(new CallStatement("explode")).build();
	
	private static final BlockStatement emptyBlock =
			new BlockStatement.Builder().build();
	
	@Test
	public void testGetStatements() {
		List<Statement> list = a.getStatements();
		assertEquals(2, list.size());
		assertEquals(explodeBlock, list.get(0));
		assertEquals(emptyBlock, list.get(1));
	}
	
	@Test
	public void testSize() {
		assertEquals(2, a.size());
	}
	
	@Override
	protected BlockStatement A() {
		return new BlockStatement.Builder()
				.append(explodeBlock)
				.append(emptyBlock)
				.build();
	}

	@Override
	protected BlockStatement D() {
		return new BlockStatement.Builder()
				.append(new CallStatement("blarg"))
				.append(new CallStatement("explode"))
				.build();
	}
}
