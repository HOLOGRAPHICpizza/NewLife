package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.Collections;
import java.util.List;
import java.util.Map;

import org.junit.Test;
import org.peak15.newlife.types.Program;
import org.peak15.newlife.types.BlargStatement;

public class ProgramTest extends ValueTypeTest<Program> {

	private static final Map<String, BlargStatement> context;
	private static final BlargStatement body = BlargStatement.makeBlock(
			Collections.singletonList(BlargStatement.makeCall("explode")));
	
	static {
		List<BlargStatement> explodeBody = Collections.singletonList(BlargStatement.makeCall("turnright"));
		BlargStatement explode = BlargStatement.makeBlock(explodeBody);
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
		BlargStatement body = BlargStatement.makeBlock(
				Collections.singletonList(BlargStatement.makeCall("turnleft")));
		return new Program("totheleft", Collections.<String, BlargStatement>emptyMap(), body);
	}

}
