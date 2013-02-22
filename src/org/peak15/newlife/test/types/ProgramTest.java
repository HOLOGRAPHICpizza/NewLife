package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.Collections;
import java.util.Map;
import org.junit.Test;
import org.peak15.newlife.types.Program;
import org.peak15.newlife.types.statement.BlockStatement;
import org.peak15.newlife.types.statement.CallStatement;

public class ProgramTest extends ValueTypeTest<Program> {

	private static final BlockStatement body =
			new BlockStatement.Builder(new CallStatement("explode")).build();
	
	private static final Map<String, BlockStatement> context =
			Collections.singletonMap(
				"explode",
				new BlockStatement.Builder(new CallStatement("turnright")).build());
	
	@Test
	public void testGetName() {
		assertEquals("omgbbq", a.getName());
	}

	@Test
	public void testGetContext() {
		assertEquals(context, a.getContext());
	}

	@Test
	public void testGetBody() {
		assertEquals(body, a.getBody());
	}

	@Override
	protected Program A() {
		return new Program("omgbbq", context, body);
	}

	@Override
	protected Program D() {
		return new Program(
				"totheleft",
				Collections.<String, BlockStatement>emptyMap(),
				new BlockStatement.Builder(new CallStatement("turnleft")).build());
	}

}
