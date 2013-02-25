package org.peak15.newlife.test.types;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

@RunWith(Suite.class)
@SuiteClasses({
		BlockStatementTest.class,
		CallStatementTest.class,
		IfElseStatementTest.class,
		ProgramTest.class,
		StaticBiMapTest.class,
		TokenTest.class,
		WhileStatementTest.class})
public class TypeTests {}
