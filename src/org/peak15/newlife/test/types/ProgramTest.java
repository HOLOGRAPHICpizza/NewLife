package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.Collections;
import java.util.List;
import java.util.Map;

import org.junit.Test;
import org.peak15.newlife.types.Program;
import org.peak15.newlife.types.Statement;

public class ProgramTest extends ValueTypeTest<Program> {

	private static final Map<String, Statement> context;
	private static final Statement body = Statement.makeBlock(
			Collections.singletonList(Statement.makeCall("explode")));
	
	static {
		List<Statement> explodeBody = Collections.singletonList(Statement.makeCall("turnright"));
		Statement explode = Statement.makeBlock(explodeBody);
		context = Collections.singletonMap("explode", explode);
	}
	
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
		Statement body = Statement.makeBlock(
				Collections.singletonList(Statement.makeCall("turnleft")));
		return new Program("totheleft", Collections.<String, Statement>emptyMap(), body);
	}

}
