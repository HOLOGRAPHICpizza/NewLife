package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.junit.Test;
import org.peak15.newlife.types.Sequence;

public class SequenceTest extends ValueTypeTest<Sequence<String>> {
	
	private static final List<String> list
			= Arrays.asList("greetings", "I", "have", "a", "beauger");
	
	@Test
	public void testEmptySequence() {
		assertEquals(Collections.<String>emptyList(), Sequence.<String>emptySequence().asList());
	}

	@Test
	public void testAsList() {
		assertEquals(list, a.asList());
	}

	@Test
	public void testSize() {
		assertEquals(list.size(), a.size());
	}

	@Test
	public void testGet() {
		assertEquals(list.get(4), a.get(4));
	}

	@Test
	public void testIterator() {
		fail("Not yet implemented");
	}

	@Override
	protected Sequence<String> A() {
		return new Sequence.Builder<String>(list).build();
	}

	@Override
	protected Sequence<String> D() {
		return Sequence.<String>emptySequence();
	}

}
