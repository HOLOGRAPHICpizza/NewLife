package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.Collections;
import java.util.List;

import org.junit.Test;
import org.peak15.newlife.types.statement.BlockStatement;
import org.peak15.newlife.types.statement.CallStatement;
import org.peak15.newlife.types.statement.Statement;

public class BlockStatementTest extends ValueTypeTest<BlockStatement> {
	
	// All 3 example blocks are package-private
	
	static final BlockStatement EXPLODE_BLOCK =
			new BlockStatement.Builder(new CallStatement("explode")).build();
	
	static final BlockStatement INFECT_BLOCK =
			new BlockStatement.Builder(new CallStatement("infect")).build();
	
	static BlockStatement compoundBlock() {
		return new BlockStatement.Builder()
				.append(EXPLODE_BLOCK)
				.append(INFECT_BLOCK)
				.build();
	}
	
	@Test
	public void testGetStatements() {
		List<Statement> list = a.statementList();
		assertEquals(2, list.size());
		assertEquals(EXPLODE_BLOCK, list.get(0));
		assertEquals(INFECT_BLOCK, list.get(1));
	}
	
	@Test
	public void testSize() {
		assertEquals(2, a.size());
	}
	
	@Test
	public void testEmptyBlock() {
		assertEquals(0, BlockStatement.emptyBlock().size());
		assertEquals(Collections.<Statement>emptyList(), BlockStatement.emptyBlock().statementList());
	}
	
	@Test
	public void testIterator() {
		List<Statement> list = a.statementList();
		int i = 0;
		for(Statement s : a) {
			assertEquals(list.get(i++), s);
		}
	}
	
	@Override
	protected BlockStatement A() {
		return compoundBlock();
	}

	@Override
	protected BlockStatement D() {
		return new BlockStatement.Builder()
				.append(new CallStatement("blarg"))
				.append(new CallStatement("explode"))
				.build();
	}
}
