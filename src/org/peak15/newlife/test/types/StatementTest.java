package org.peak15.newlife.test.types;

import java.util.Collections;
import org.peak15.newlife.types.Statement;
import org.peak15.newlife.types.Statement.Condition;

public class StatementTest extends ValueTypeTest<Statement> {
	
	//TODO: Currently tests only a few of the statement types
	//		with the standard value type tests.
	
	//TODO: Test the various constructors.
	
	@Override
	protected Statement A() {
		Statement body = Statement.makeBlock(
				Collections.singletonList(Statement.makeCall("explode")));
		
		Statement elseBody = Statement.makeBlock(
				Collections.singletonList(Statement.makeCall("explode")));
		
		return Statement.makeIfElse(Condition.RANDOM, body, elseBody);
	}

	@Override
	protected Statement D() {
		return Statement.makeCall("blarg");
	}
}
