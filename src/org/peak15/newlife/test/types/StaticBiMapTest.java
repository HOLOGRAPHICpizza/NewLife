package org.peak15.newlife.test.types;

import static org.junit.Assert.*;

import java.util.HashMap;
import java.util.Map;
import org.junit.Test;
import org.peak15.newlife.types.StaticBiMap;

public class StaticBiMapTest extends ValueTypeTest<StaticBiMap<String, Integer>> {
	
	private static final Map<String, Integer> KVMap;
	private static final Map<Integer, String> VKMap;
	
	static {
		KVMap = new HashMap<>();
		KVMap.put("taco", 1337);
		KVMap.put("burrito", 9001);
		
		VKMap = new HashMap<>();
		VKMap.put(1337, "taco");
		VKMap.put(9001, "burrito");
	}
	
	@Test
	public void testKeyValueMap() {
		assertEquals(KVMap, a.keyValueMap());
	}

	@Test
	public void testValueKeyMap() {
		assertEquals(VKMap, a.valueKeyMap());
	}

	@Test
	public void testKeySet() {
		assertEquals(KVMap.keySet(), a.keySet());
	}

	@Test
	public void testValueSet() {
		assertEquals(VKMap.keySet(), a.valueSet());
	}

	@Test
	public void testContainsKey() {
		assertTrue(a.containsKey("taco"));
	}

	@Test
	public void testContainsValue() {
		assertTrue(a.containsValue(1337));
	}

	@Test
	public void testValueOf() {
		assertEquals(Integer.valueOf(1337), a.valueOf("taco"));
	}

	@Test
	public void testKeyOf() {
		assertEquals("taco", a.keyOf(1337));
	}

	@Override
	protected StaticBiMap<String, Integer> A() {
		return new StaticBiMap.Builder<String, Integer>(KVMap).build();
	}

	@Override
	protected StaticBiMap<String, Integer> D() {
		return new StaticBiMap.Builder<String, Integer>().build();
	}

}
