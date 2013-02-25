package org.peak15.newlife;

import org.peak15.newlife.types.StaticBiMap;

public enum Condition {
	NEXT_IS_EMPTY,
	NEXT_IS_NOT_EMPTY,
	NEXT_IS_WALL,
	NEXT_IS_NOT_WALL,
	NEXT_IS_FRIEND,
	NEXT_IS_NOT_FRIEND,
	NEXT_IS_ENEMY,
	NEXT_IS_NOT_ENEMY,
	RANDOM,
	TRUE;
	
	private static StaticBiMap<Condition, String> map = new StaticBiMap.Builder<Condition, String>()
			.append(NEXT_IS_EMPTY, "next-is-empty")
			.append(NEXT_IS_NOT_EMPTY, "next-is-not-empty")
			.append(NEXT_IS_WALL, "next-is-wall")
			.append(NEXT_IS_NOT_WALL, "next-is-not-wall")
			.append(NEXT_IS_FRIEND, "next-is-friend")
			.append(NEXT_IS_NOT_FRIEND, "next-is-not-friend")
			.append(NEXT_IS_ENEMY, "next-is-enemy")
			.append(NEXT_IS_NOT_ENEMY, "next-is-not-enemy")
			.append(RANDOM, "random")
			.append(TRUE, "true")
			.build();
	
	public static boolean isConditionString(String conditionString) {
		return map.containsValue(conditionString);
	}
	
	/**
	 * @param conditionString a condition string as defined by the language grammar.
	 * @return the Condition representing the string.
	 * @throws IllegalArgumentException if no Condition represents conditionString.
	 */
	public static Condition parseConditionString(String conditionString) {
		return map.keyOf(conditionString);
	}
	
	/**
	 * @return the condition string from the language grammar represented by this Condition.
	 */
	public String toConditionString() {
		return map.valueOf(this);
	}
}